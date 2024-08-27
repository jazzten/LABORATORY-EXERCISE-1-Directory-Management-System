#include <iostream>
#include <string>  
#include <direct.h> 
#include <dos.h>   


using namespace std;


void list_files(const string& directory, const string& extension = "", const string& pattern = "") {
    _finddata_t file_info; // Structure to store information about a file (platform-specific)
    long handle;         // Handle for file search operations (platform-specific)

    // Construct the search path by combining the directory and wildcard
    string search_path = directory + "\\*";
    if (!extension.empty()) {
        search_path += "." + extension;  // Append extension if provided
    }
    // See the first file matching the search path
    handle = _findfirst(search_path.c_str(), &file_info);
    if (handle == -1) {
        cerr << "Error: No files found in the specified directory." << endl;
        return;
    }
    // use header for the list of files
    cout << "List of Files:\n";
    // Loop through all files in the directory
    do {
    	// replace directories
        if (file_info.attrib & _A_SUBDIR) {
            continue; // Skip directories
        }
        // Skip files that don't match the pattern
        if (!pattern.empty() && !(_strnicmp(file_info.name, pattern.c_str(), pattern.length()) == 0)) {
            continue; 
        }
        // Print the file name
        cout << file_info.name << endl;
    } while (_findnext(handle, &file_info) == 0); //  finding files until no more  found
    // Close the search handle
    _findclose(handle);
}
//  create a new directory
void create_directory(const string& directory) {
    if (_mkdir(directory.c_str()) != 0) {
        cerr << "Error: Failed to create directory: " << directory << endl;
    } else {
        cout << "Directory created successfully." << endl;
    }
}
// change the current working directory
void change_directory(const string& directory) {
    if (_chdir(directory.c_str()) != 0) {
        cerr << "Error: Failed to change directory: " << directory << endl;
    } else {
        cout << "Current directory changed to: " << directory << endl;
    }
}
// function that displays options and interacts with user
void main_menu() {
    int choice;

    while (true) {
        cout << "\nMAIN MENU\n";
        cout << "1. List Files\n";
        cout << "2. Create New Directory\n";
        cout << "3. Change Working Directory\n";
        cout << "4. Exit\n";
        cout << "Enter your number: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int list_choice;
                cout << "\nList File Detail\n";
                cout << "1. List All Files\n";
                cout << "2. List of Extension Files\n";
                cout << "3. List of Name Wise\n";
                cout << "Enter your number: ";
                cin >> list_choice;

                string extension, pattern;

                switch (list_choice) {
                    case 1:
					// list of files with current directory and no filtering 
                        list_files(_getcwd(NULL, 0));
                        break;
                    case 2:
                        cout << "Enter the file extension (e.g., .txt): ";
                        cin >> extension;
                        // list of files with current directory and provided extension
                        list_files(_getcwd(NULL, 0), extension);
                        break;
                    case 3:
                        cout << "Enter the file pattern (e.g., moha*.*): ";
                        cin >> pattern;
                        // list of files with current directory and provided in the  pattern
                        list_files(_getcwd(NULL, 0), "", pattern);
                        break;
                    default:
                        cerr << "Invalid choice.\n";
                        break;
                }
                break;
            }
            case 2: {
                string directory_name;
                cout << "Enter the Directory name: ";
                cin >> directory_name;
                create_directory(directory_name);
                break;
            }
            case 3: {
                int change_choice;
                cout << "\nChange Directory\n";
                cout << "1. Step by Step Backward\n";
                cout << "2. Goto Root Directory\n";
                cout << "3. Forward Directory\n";
                cout << "Enter your number: ";
                cin >> change_choice;

                switch (change_choice) {
                    case 1:
                        change_directory("..");
                        break;
                    case 2:
                        change_directory("/");
                        break;
                    case 3: {
                        string directory_name;
                        cout << "Please enter the Directory Name: ";
                        cin >> directory_name;
                        change_directory(directory_name);
                        break;
                    }
                    default:
                        cerr << "Invalid choice.\n";
                        break;
                }
                break;
            }
            case 4:
                cout << "Exiting...\n";
                return;
            default:
                cerr << "Invalid choice.\n";
                break;
        }
    }
}

int main() {
    main_menu();
    return 0;
}
