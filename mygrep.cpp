#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

bool containsTwoOs(const std::string& str) {
    for (size_t i = 0; i < str.length() - 1; ++i) {
        if (str[i] == 'o' && str[i + 1] == 'o') {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {

    string initialString { };
    string searchString {};
    string arguments { };

    if (argc == 3) {

        ifstream inputFile(argv[2]);

        if (!inputFile) {
            cerr << "Error, cant open the file!" << endl;
            return 1;
        }

        string line { };

        int lineNumber = 1;
        searchString = argv[2];

        while (getline(inputFile, line)) {
            initialString += line + "\n";
            size_t foundPos = line.find(argv[1]);

            if (foundPos != string::npos) {
                if (argc == 3)
                cout << line << endl;

            }
            lineNumber++;
        }     

        inputFile.close();

    }

    else if (argc == 4) {

        ifstream inputFile(argv[3]);
        if (!inputFile) {
            cerr << "Error, cant open the file!" << endl;
            return 1;
        }

        string line { };

        int foundLines { 0 };

        int lineNumber = 1;
        searchString = argv[2];
        arguments = argv[1];
        bool ignoreCases { false };
        bool reverseSearch { false };
        bool showContainingLine { false };
        bool showLineNumbers { false };

        if (containsTwoOs(arguments)) {
            showContainingLine = true;
        }

        if (arguments.find("r") != string::npos) {
            reverseSearch = true;
        }

        if (arguments.find("i") != string::npos) {
            ignoreCases = true;
            for (int i = 0; i < searchString.length(); i++) {
                searchString.at(i) = tolower(searchString.at(i));
            }
        }



        if (arguments.find("l") != string::npos) {
            showLineNumbers = true;
        }


        if (reverseSearch) {
            while (getline(inputFile, line)) {

                initialString += line + "\n";

                if (ignoreCases) {
                    for (int i = 0; i < initialString.length(); i++) {
                        initialString.at(i) = tolower(initialString.at(i));
                    }
                }

                size_t foundPos = line.find(searchString);

                if (foundPos == string::npos) {

                    if (showLineNumbers) {
                        cout << lineNumber << ": " << line << endl;
                    }

                    else if (!showLineNumbers) {
                        cout << line << endl;
                    }
                    else {
                        cout << "unknown arguments..." << endl;
                        cout << "-l Show line numbers" << endl;
                        cout << "-i ignore case sensitivity" << endl;
                        cout << "-o show total containing lines" << endl;
                        cout << "-r reverse searching" << endl;
                        return 1;
                    }
                    foundLines++;
                
                }
                lineNumber++;
            }
             
        }

        if (!reverseSearch) {
            while (getline(inputFile, line)) {

                initialString += line + "\n";

                if (ignoreCases) {
                    for (int i = 0; i < initialString.length(); i++) {
                        initialString.at(i) = tolower(initialString.at(i));
                    }
                }

                size_t foundPos = line.find(searchString);

                if (foundPos != string::npos) {

                    if (showLineNumbers) {
                        cout << lineNumber << ": " << line << endl;
                    }

                    else if (!showLineNumbers) {
                        cout << line << endl;
                    }


                    else {
                        cout << "unknown arguments..." << endl;
                        cout << "-l Show line numbers" << endl;
                        cout << "-i ignore case sensitivity" << endl;
                        cout << "-o show total containing lines" << endl;
                        cout << "-r reverse searching" << endl;
                        return 1;
                    }
                    foundLines++;
                
                }
                lineNumber++;
            }     
        }



        if (showContainingLine) {
            cout << "Occurences of lines containing : " << searchString << " " << foundLines <<endl;
        }

        else if (reverseSearch) {
            cout << "Occurences of lines not containing : " << searchString << " " << foundLines << endl;
        }

        inputFile.close();
    }

    // Binary execution
    else {
        cout << "Give a string from which to search for: ";
        getline(cin, initialString);

        cout << "Give a search string: ";
        getline(cin, searchString);

        size_t foundPos = initialString.find(searchString, 0);

        if (foundPos != string::npos) {
            if (argc == 3) {
                initialString = argv[2];
            }

            cout << "'" << searchString << "' " << "found in position: " << foundPos << "!" << " from " << "'" << initialString << "'" << endl; 
        }

        else {
            cout << "'" << searchString << "' " << "NOT found from initial string!: " << "'" << initialString << "'" << endl;
        }

        system("pause");
    }

    return 0;

}