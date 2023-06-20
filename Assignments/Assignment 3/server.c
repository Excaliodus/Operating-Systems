#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_FILENAME_LEN 100
#define MAX_DATA_LEN 1000
#define SHM_KEY 1234

typedef struct
{
    char command[MAX_FILENAME_LEN + MAX_DATA_LEN + 2];
    sem_t sem;
} shared_mem;

void* handle_request(void* arg)
{
    shared_mem* mem = (shared_mem*) arg;
    char* command = mem->command;
    sem_t* sem = &(mem->sem);
    char* token = strtok(command, " ");
    if (strcmp(token, "read") == 0)
	{
        char filename[MAX_FILENAME_LEN];
        token = strtok(NULL, " ");
        strcpy(filename, token);

        int fd = open(filename, O_RDONLY);
        if (fd < 0)
		{
            perror("Error opening file for reading");
            sem_post(sem);
            return NULL;
        }
		off_t file_size = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);

        int shm_id = shmget(IPC_PRIVATE, file_size, IPC_CREAT | 0666);
        if (shm_id < 0)
		{
            perror("Error creating shared memory segment");
            sem_post(sem);
            return NULL;
        }

        char* shm_addr = (char*) shmat(shm_id, NULL, 0);
        if (shm_addr == (char*) -1)
		{
            perror("Error attaching shared memory segment");
            sem_post(sem);
            return NULL;
        }

        read(fd, shm_addr, file_size);
        close(fd);

        sprintf(command, "%d", shm_id);
        sem_post(sem);
        return NULL;
    }
	else if (strcmp(token, "write") == 0)
	{
        char filename[MAX_FILENAME_LEN];
        token = strtok(NULL, " ");
        strcpy(filename, token);

        char data[MAX_DATA_LEN];
        strcpy(data, strtok(NULL, ""));

        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd < 0)
		{
            perror("Error opening file for writing");
            sem_post(sem);
            return NULL;
        }

        write(fd, data, strlen(data));
        close(fd);

        sem_post(sem);
        return NULL;
    }
	else
	{
        printf("Invalid command\n");
        sem_post(sem);
        return NULL;
    }
}

int main()
{
    int shm_id = shmget(SHM_KEY, sizeof(shared_mem), IPC_CREAT | 0666);
    if (shm_id < 0)
	{
        perror("Error creating shared memory segment");
        exit(EXIT_FAILURE);
    }
    shared_mem* mem = (shared_mem*) shmat(shm_id, NULL, 0);
    if (mem == (shared_mem*) -1) {
        perror("Error attaching shared memory segment");
        exit(EXIT_FAILURE);
    }

    sem_init(&(mem->sem), 1, 1);

    while (1)
	{
        sem_wait(&(mem->sem));
        pthread_t thread_id;
		pthread_create(&thread_id, NULL, handle_request, (void*) mem);
		pthread_detach(thread_id);
		memset(mem->command, 0, MAX_FILENAME_LEN + MAX_DATA_LEN + 2);
	}

	shmdt(mem);
	shmctl(shm_id, IPC_RMID, NULL);

	return 0;
}