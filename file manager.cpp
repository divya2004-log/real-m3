#include <iostream>
#include <fstream>
#include <direct.h> // For mkdir() on Windows
#include <cstdio>   // For remove() and rename()
#include <cstring>
#include <windows.h> // For navigating directories

using namespace std;

// Function to list all files and directories in the current directory
void listDirectory(const string& path) {
    cout << "\nContents of Directory: " << path << "\n\n";
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((path + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "Error: Unable to open directory.\n";
        return;
    }

    do {
        string fileName = findFileData.cFileName;
        if (fileName == "." || fileName == "..") continue;
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            cout << "[Dir]  " << fileName << endl;
        else
            cout << "[File] " << fileName << endl;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

// Function to view a file's contents
void viewFile(const string& filepath) {
    ifstream file(filepath.c_str());
    if (!file) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    cout << "\nContents of File: " << filepath << "\n\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Function to create a directory
void createDirectory(const string& path) {
    if (_mkdir(path.c_str()) == 0) {
        cout << "Directory created: " << path << endl;
    } else {
        cout << "Error: Unable to create directory.\n";
    }
}

// Function to copy a file
void copyFile(const string& source, const string& destination) {
    ifstream src(source, ios::binary);
    ofstream dest(destination, ios::binary);

    if (!src || !dest) {
        cout << "Error: Unable to copy file.\n";
        return;
    }

    dest << src.rdbuf();
    cout << "File copied from " << source << " to " << destination << endl;

    src.close();
    dest.close();
}

// Function to move a file (rename)
void moveFile(const string& source, const string& destination) {
    if (rename(source.c_str(), destination.c_str()) == 0) {
        cout << "File moved from " << source << " to " << destination << endl;
    } else {
        cout << "Error: Unable to move file.\n";
    }
}

int main() {
    string currentPath = ".";
    int choice;

    do {
        cout << "\n=== Basic File Manager ===\n";
        cout << "1. List Directory\n";
        cout << "2. View File\n";
        cout << "3. Create Directory\n";
        cout << "4. Copy File\n";
        cout << "5. Move File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                listDirectory(currentPath);
                break;
            }
            case 2: {
                string filepath;
                cout << "Enter file path to view: ";
                cin >> filepath;
                viewFile(filepath);
                break;
            }
            case 3: {
                string newDir;
                cout << "Enter name of new directory: ";
                cin >> newDir;
                createDirectory(currentPath + "\\" + newDir);
                break;
            }
            case 4: {
                string source, destination;
                cout << "Enter source file path: ";
                cin >> source;
                cout << "Enter destination file path: ";
                cin >> destination;
                copyFile(source, destination);
                break;
            }
            case 5: {
                string source, destination;
                cout << "Enter source file path: ";
                cin >> source;
                cout << "Enter destination file path: ";
                cin >> destination;
                moveFile(source, destination);
                break;
            }
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}


