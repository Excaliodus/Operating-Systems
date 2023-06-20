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

    // Create a unique key using ftok
    key_t key = ftok(SHMFILE, 65);

    // Create a shared memory segment
    int shmid = shmget(key, SHMSIZE, SHMFLAGS);

    // Attach to the shared memory segment
    char* str = shmat(shmid, NULL, 0);

    // Read data from the shared memory segment
    printf("Data read from memory: %s\n", str);

    // Parse the integers from the shared memory object and compute the sum and average
    int num_count = 0;
    int sum = 0;
    char* num_str = strtok(str, DELIM);
    while (num_str != NULL) {
        int num = atoi(num_str);
        sum += num;
        num_count++;
        num_str = strtok(NULL, DELIM);
    }
    double avg = (double) sum / num_count;
    printf("Sum: %d\nAverage: %f\n", sum, avg);

    // Detach from the shared memory segment
    shmdt(str);

    // Destroy the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
