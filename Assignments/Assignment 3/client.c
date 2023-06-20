#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define MAX_FILENAME_LEN 100
#define MAX_DATA_LEN 1000
#define SHM_KEY 1234

typedef struct
{
    char command[MAX_FILENAME_LEN + MAX_DATA_LEN + 2];
    sem_t sem;
} shared_mem;

int main()
{
    int shm_id = shmget(SHM_KEY, sizeof(shared_mem), 0666);
    if (shm_id < 0)
	{
        perror("Error getting shared memory segment");
        exit(EXIT_FAILURE);
    }
    shared_mem* mem = (shared_mem*) shmat(shm_id, NULL, 0);
    if (mem == (shared_mem*) -1) {
        perror("Error attaching shared memory segment");
        exit(EXIT_FAILURE);
    }

    sem_wait(&(mem->sem));
    char command[MAX_FILENAME_LEN + MAX_DATA_LEN + 2];
    fgets(command, sizeof(command), stdin);
    strcpy(mem->command, command);
    sem_post(&(mem->sem));

    char* token = strtok(command, " ");
    if (strcmp(token, "read") == 0) {
        sem_wait(&(mem->sem));
        int shm_id = atoi(mem->command);
        shmdt(mem);
        char* shm_addr = (char*) shmat(shm_id, NULL, 0);
        if (shm_addr == (char*) -1) {
            perror("Error attaching shared memory segment");
            exit(EXIT_FAILURE);
        }

        printf("%s", shm_addr);
        shmdt(shm_addr);
        shmctl(shm_id, IPC_RMID, NULL);
        sem_post(&(mem->sem));
    }
    return 0;
}
