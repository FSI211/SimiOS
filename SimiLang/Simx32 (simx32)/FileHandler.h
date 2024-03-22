// FileHandler.h

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bools.h" // Annahme: Datei bools.h enthält die Definitionen von 'found' und 'endthis'
using namespace std;

void compile() {
    cout << "Can't compile without output in version 0.001.";
}

// Function to open a file with .sim extension
void openFile(const std::string& filename) {
    if (filename.substr(filename.size() - 4) != ".sim") {
        std::cout << "Error: File must have .sim extension." << std::endl;
        return;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Read file contents
    std::string line;
    std::cout << "Contents of " << filename << ":" << std::endl;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

// Function to search for text in a file and output if found
void output(const std::string& filename, const std::string& fileout) {
    std::string fileout_with_extension = fileout;
    std::transform(fileout_with_extension.begin(), fileout_with_extension.end(), fileout_with_extension.begin(), ::tolower);

    if (fileout_with_extension.substr(fileout_with_extension.size() - 7) != ".simx32") {
        std::cout << "Error: Output file must have .simx32 extension." << std::endl;
        return;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::ofstream outfile(fileout);
    if (!outfile.is_open()) {
        std::cout << "Error: Unable to create output file " << fileout << std::endl;
        file.close();
        return;
    }

    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        if (line.find("do") != std::string::npos) {
            found = true;
        } 
        
        else if (line.find("end") != std::string::npos) {
            found = false;
            endthis = true;
        }
 
        if (found) {
            outfile << "call 0x2407:\n";
            outfile << " this:\n";
            outfile << "  doout!();\n";
        }

        else if(endthis) {
            outfile << "call 0x240711:\n";
            outfile << " end!()";
        }

        else if(bin) {
            outfile << "Bins: \n";
            for(int i = 0; i < 1000000; i++) {
                outfile << "01";
            }
        } 

        else {
            cout << "Couldn't compile file, error.";
            break;
        }
    }

    file.close();
    outfile.close();

    std::cout << "Output successfully written to file: " << fileout << std::endl;
}

#endif // FILEHANDLER_H