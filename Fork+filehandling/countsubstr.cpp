#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int count_substring(const string& str, const string& sub) {
    int count = 0;
    string::size_type pos = 0;
    while ((pos = str.find(sub, pos)) != string::npos) {
        ++count;
        pos += sub.length();
    }
    return count;
}

int main(int argc, char* argv[]) {

    const char* filename = argv[1];
    const string& sub = argv[2];
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return 1;
    }
    string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    int count = count_substring(contents, sub);
    cout << "The substring \"" << sub << "\" appears " << count << " times in the file." << endl;
    return 0;
}
