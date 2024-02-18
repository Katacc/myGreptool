#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> // Käytetään windowsissa system() komennon kanssa
using namespace std;

// Tarkistetaan onko argumenteissä kahta 'o' kirjainta
bool containsTwoOs(const std::string& str) {
    for (size_t i = 0; i < str.length() - 1; ++i) {
        if (str[i] == 'o' && str[i + 1] == 'o') {
            return true;
        }
        else if (str[i] == 'o' && str[i + 2] == 'o') {
            return true;
        }
        else if (str[i] == 'o' && str[i + 3] == 'o') {
            return true;
        }
        else if (str[i] == 'o' && str[i + 4] == 'o') {
            return true;
        }
        else if (str[i] == 'o' && str[i + 5] == 'o') {
            return true;
        }
        else if (str[i] == 'o' && str[i + 6] == 'o') {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {

    string initialString { };
    string searchString {};
    string arguments { };

    // Tarkastetaan, onko käytössä ajoasetukset (-o)
    if (argc == 3) {

        ifstream inputFile(argv[2]);

        // Virhe jos tiedostoa ei saada avattua
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

    // Käytössä options (-o)
    else if (argc == 4) {

        ifstream inputFile(argv[3]);

        // Jos tiedostoa ei saada avattua.
        if (!inputFile) {
            cerr << "Error, cant open the file!" << endl;
            return 1;
        }

        string line { };

        int foundLines { 0 };

        int lineNumber = 1;
        searchString = argv[2];
        arguments = argv[1];

        // Options kytkimet
        bool ignoreCases { false };
        bool reverseSearch { false };
        bool showContainingLine { false };
        bool showLineNumbers { false };

        // tarkastetaan o optio
        if (containsTwoOs(arguments)) {
            showContainingLine = true;
        }

        // tarkastetaan r optio
        if (arguments.find("r") != string::npos) {
            reverseSearch = true;
        }

        // tarkastetaan i optio
        if (arguments.find("i") != string::npos) {
            ignoreCases = true;
            // muutetaa muuttuja pieniksi kirjaimiksi
            for (int i = 0; i < searchString.length(); i++) {
                searchString.at(i) = tolower(searchString.at(i));
            }
        }


        // Tarkastetaan l optio
        if (arguments.find("l") != string::npos) {
            showLineNumbers = true;
        }


        // Reversesearch
        if (reverseSearch) {
            while (getline(inputFile, line)) {

                initialString += line + "\n";

                //NOT case sensitive
                if (ignoreCases) {
                    // Muutetaan muuttuja pieniksi kirjaimiksi
                    for (int i = 0; i < initialString.length(); i++) {
                        initialString.at(i) = tolower(initialString.at(i));
                    }
                }

                size_t foundPos = line.find(searchString);

                // merkkijono löytyi
                if (foundPos == string::npos) {

                    // Jos rivinumerokytkin on päällä
                    if (showLineNumbers) {
                        cout << lineNumber << ": " << line << endl;
                    }

                    else if (!showLineNumbers) {
                        cout << line << endl;
                    }

                    // Virhe
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


        // NOT reverseSearch
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



        // o option käyttö
        if (showContainingLine) {
            cout << "Occurences of lines containing : " << "'" <<searchString << "'" << ", " << foundLines <<endl;
        }

        else if (reverseSearch && showContainingLine) {
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


    }

    return 0;

}