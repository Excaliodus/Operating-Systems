#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    const char* SHMFILE = "shmfile";
    const int SHMSIZE = 1024;
    const int SHMFLAGS = IPC_CREAT | 0666;
    const char* DELIM = " ";

    key_t key = ftok(SHMFILE, 65);

    int shmid = shmget(key, SHMSIZE, SHMFLAGS);

    char* str = shmat(shmid, NULL, 0);

    printf("Data read from memory: %s\n", str);

    int smallest;
    int largest;
    int i=0;
    char* num_str = strtok(str, DELIM);
    while (num_str != NULL) {
        int num = atoi(num_str);
	if (i==0)
	{
		smallest=num;
		largest=num;
		i++;
	}
	if (num>largest)
		largest=num;
	if (num<smallest)
		smallest=num;
        num_str = strtok(NULL, DELIM);
    }
    printf("Largest: %d\nSmallest: %d\n", largest, smallest);

    shmdt(str);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
