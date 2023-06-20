#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int count_vowels(string str) {
    int count = 0;

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    string file_name = "question1.txt";

    ifstream file(file_name);

    string str((istreambuf_iterator<char>(file)),
               istreambuf_iterator<char>());

    int p = fork();
    if (p == -1) {
        cout << "Error: Failed to fork the process" << endl;
        return 1;
    }

    if (p == 0) {
        int count = count_vowels(str);
        cout << "Total number of vowels in " << file_name << ": " << count << endl;
        exit(0);
    } else {
        int status=fork(); 
        if(status==0){
        cout << "Program completed" << endl;
        }
    }

    return 0;
}
