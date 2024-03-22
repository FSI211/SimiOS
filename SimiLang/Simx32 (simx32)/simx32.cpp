#include <iostream>
#include "FileHandler.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Check if enough arguments are passed
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <action> [filename.sim]" << endl;
        return 1;
    }

    // The first argument is the action
    string action = argv[1];

    if (action == "-o") {
        // Check if filename and output filename are provided
        if (argc < 4) {
            cout << "Error: Filename or output filename not provided." << endl;
            return 1;
        }
        string filename = argv[2];
        string outputFilename = argv[3];
        output(filename, outputFilename);
    }
    else if(action == "-w") {
        string act = argv[2];
        if(argv[3] == "-h") {
            cout << "This is the writer command of SimCC.\n";
        } 
        else {
            ofstream __file;
            __file.open("writter.sim");
            __file << act;
            __file.close();            
        }

    }
    else if (action == "-open") {
        // Check if filename is provided
        if (argc < 3) {
            cout << "Error: Filename not provided." << endl;
            return 1;
        }
        string filename = argv[2];
        openFile(filename);
    } else if (action == "-compile") {
        compile();
    } else {
        cout << "Unknown action: " << action << endl;
        return 1;
    }

    return 0;
}