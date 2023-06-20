#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 50
#define MAX_WORD_LENGTH 50

char sentence[10000];
char words[MAX_WORDS][MAX_WORD_LENGTH];
int counter[MAX_WORDS];
int word_count=0;
int Total_Word=0;
int N;

void *worker(void *arg) {
    int word_index = *(int*)arg;
    int seg_size=(Total_Word/N)+1;
    int start_idx=word_index*seg_size;
    int end_idx=(word_index+1)*seg_size;
    int curr=-1;
    char* start = sentence;
    char temp[100];
    bool found=false;
    for (int i = 0; sentence[i] != '\0' ; i++) {
        if (sentence[i] == ' ' || sentence[i] == '\n'||sentence[i] == '.') {
            curr++;
            if(curr>=start_idx&&curr<end_idx){
                int length = &sentence[i] - start;
                strncpy(temp, start, length);
                temp[length] = '\0';
                found=true;
            }
            start = &sentence[i+1];
        }
        if(found==true)
        {
            int k=0;
            for(k=0;k<word_count;k++)
            {
                if(strcasecmp(words[k],temp) == 0)
                {
                    counter[k]++;
                    found=false;
                }
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    N=20;
    int fd = open ("input.txt", O_RDONLY, S_IRUSR);
    read(fd, sentence, sizeof (sentence));
    printf("Orignal Sentence read from file: \n\n");
    write(2,sentence,sizeof (sentence));
     // Split sentence into words and remove duplicates
    char* start = sentence;
    for (int i = 0; sentence[i] != '\0' && word_count < MAX_WORDS; i++) {
        if (sentence[i] == ' ' || sentence[i] == '\n'||sentence[i] == '.') {
            // Store word in array
            int length = &sentence[i] - start;
            strncpy(words[word_count], start, length);
            words[word_count][length] = '\0';

            // Check if word already exists
            int duplicate = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcasecmp(words[word_count], words[j]) == 0) {
                    duplicate = 1;
                    break;
                }
            }
            // Add word to array if not a duplicate
            if (!duplicate) {
                word_count++;
            }

            // Set start pointer to next word
            start = &sentence[i+1];
            Total_Word++;
        }
    }
    word_count--;
    printf("\nThe words in the sentence are:%d\n",Total_Word);
    // Print out the number unique words
    printf("\nThe unique words in the sentence are:%d\n",word_count);
    for (int i = 0; i < word_count; i++) {
        counter[i]=0;
    }


    pthread_t threads[N];
    int thread_args[N]; 
    // Create Threads
    for (int i = 0; i < N; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_args[i]);
    }

    // Wait for the threads to complete
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    //print results
    for (int i = 0; i < word_count; i++) {
        printf("%s=%d\n", words[i],counter[i]);
    }
  
    
    return 0;
}
