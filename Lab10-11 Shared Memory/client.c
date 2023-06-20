#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Failed to open file");
        return 1;
    }

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        printf("Failed to create shared memory segment");
        return 1;
    }

    char* str = (char*) shmat(shmid, NULL, 0);
    if (str == (char*) -1) {
        printf("Failed to attach to shared memory segment");
        return 1;
    }

    ssize_t nread = read(fd, str, SHM_SIZE);
    if (nread == -1) {
        printf("Failed to read file");
        return 1;
    }

    printf("Data read from file: %s\n", str);

    if (shmdt(str) == -1) {
        printf("Failed to detach from shared memory segment");
        return 1;
    }

    if (close(fd) == -1) {
        printf("Failed to close file descriptor");
        return 1;
    }

    return 0;
}
