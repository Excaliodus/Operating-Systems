#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 300
#define MAX_WORD_LENGTH 200
#define MAX_para_LENGTH 100000
#define MAX_THREADS 20

char para[MAX_para_LENGTH];
char words[MAX_WORDS][MAX_WORD_LENGTH];
int counter[MAX_WORDS];
int word_count = 0;
int total_word_count = 0;
int num_threads;

void *worker(void *arg) {
    int thread_id = *(int*)arg;
    int segment_size = (total_word_count / num_threads) + 1;
    int start_idx = thread_id * segment_size;
    int end_idx = (thread_id + 1) * segment_size;
    int curr_word_idx = -1;
    char* start = para;
    char curr_word[MAX_WORD_LENGTH];
    bool found_word = false;
    for (int i = 0; para[i] != '\0'; i++) {
        if (para[i] == ' ' || para[i] == '\n' || para[i] == '.') {
            curr_word_idx++;
            if (curr_word_idx >= start_idx && curr_word_idx < end_idx) {
                int length = &para[i] - start;
                strncpy(curr_word, start, length);
                curr_word[length] = '\0';
                found_word = true;
            }
            start = &para[i+1];
        }
        if (found_word) {
            int word_idx;
            for (word_idx = 0; word_idx < word_count; word_idx++) {
                if (strcasecmp(words[word_idx], curr_word) == 0) {
                    counter[word_idx]++;
                    found_word = false;
                }
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    num_threads = MAX_THREADS;

    FILE* file = fopen("inputfile.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }
    if (fgets(para, MAX_para_LENGTH, file) == NULL) {
        perror("Failed to read para");
        return 1;
    }
    fclose(file);
    printf("Original para read from file: \n\n%s\n", para);


    char* start = para;
    for (int i = 0; para[i] != '\0' && word_count < MAX_WORDS; i++) {
        if (para[i] == ' ' || para[i] == '\n' || para[i] == '.') {
         
            int length = &para[i] - start;
            strncpy(words[word_count], start, length);
            words[word_count][length] = '\0';

          
            int is_duplicate = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcasecmp(words[word_count], words[j]) == 0) {
                    is_duplicate = 1;
                    break;
                }
            }
           
            if (!is_duplicate) {
                word_count++;
            }

            
            start = &para[i+1];
            total_word_count++;
        }
    }
    printf("\nThe number of words in the paragraph are: %d\n", total_word_count);

for (int i = 0; i < word_count; i++) {
    counter[i] = 0;
}


pthread_t threads[num_threads];
int thread_ids[num_threads];
for (int i = 0; i < num_threads; i++) {
    thread_ids[i] = i;
    if (pthread_create(&threads[i], NULL, worker, &thread_ids[i])) {
        perror("Failed to create thread");
        return 1;
    }
}


for (int i = 0; i < num_threads; i++) {
    if (pthread_join(threads[i], NULL)) {
        perror("Failed to join thread");
        return 1;
    }
}

// Print results
printf("\nWord count:\n");
for (int i = 0; i < word_count; i++) {
    printf("%s: %d\n", words[i], counter[i]);
}
return 0;
}
