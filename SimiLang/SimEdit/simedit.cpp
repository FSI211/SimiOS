#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename;
    cout << "Please enter the filename (.sim): ";
    cin >> filename;

    // Checking if the file extension is .sim
    if (filename.substr(filename.find_last_of(".") + 1) != "sim") {
        cout << "Invalid file extension. The editor can only open .sim files." << endl;
        return 1;
    }

    // Open the file for reading and writing
    fstream file(filename, ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return 1;
    }

    // Display file content
    cout << "File content:" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    // Allow editing
    cout << "\nStart editing. Press Ctrl+D (on Unix) or Ctrl+Z (on Windows) to save and exit." << endl;
    file.clear(); // Reset end-of-file flag
    file.seekp(0, ios::end); // Move write pointer to the end of the file

    // Prompt for input
    cin.ignore(); // Ignore any leftover newline characters
    while (getline(cin, line)) {
        file << line << endl;
    }

    cout << "Changes saved." << endl;
    file.close();

    return 0;
}