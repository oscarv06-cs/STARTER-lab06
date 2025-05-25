// Winter'24
// Instructor: Diba Mirza
// Student name: Oscar Valeriano
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;
#include "movies.h"
#include "utilities.h"

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[0] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    Movies movies;
    movies.readCSV(argv[1]);

    if (argc == 2) {
        movies.printAll();
        return 0;
    }

    ifstream prefixFile(argv[2]);
    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2] << endl;
        exit(1);
    }

    vector<string> prefixes;
    string line;
    while (getline(prefixFile, line)) {
        line = trim(line);
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    for (const string& prefix : prefixes) {
        vector<Movie> matches = movies.withPrefix(prefix);
        if (matches.empty()) {
            cout << "No movies found with prefix " << prefix << endl;
        } else {
            for (const Movie& m : matches) {
                cout << m.title << ", " << fixed << setprecision(1) << m.rating << endl;
            }
            Movie bestMovie = *max_element(matches.begin(), matches.end(),
                                           [](const Movie& a, const Movie& b) {
                                               return a.rating < b.rating;
                                           });
            cout << "Best movie with prefix " << prefix << " is: " << bestMovie.title
                 << " with rating " << fixed << setprecision(1) << bestMovie.rating << endl;
        }
    }

    return 0;
}


/* Add your run time analysis for part 3 of the assignment here as commented block */

