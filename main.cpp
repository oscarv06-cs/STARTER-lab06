// Winter'24
// Instructor: Diba Mirza
// Student name: Oscar Valeriano
#include "movies.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <movie_csv> <prefix_file>\n";
        return 1;
    }

    std::string movieFile = argv[1];
    std::string prefixFile = argv[2];

    // Read movies
    Movies movies;
    movies.readCSV(movieFile);

    // Read prefixes
    std::ifstream prefix_input(prefixFile);
    if (!prefix_input) {
        std::cerr << "Error: Cannot open prefix file " << prefixFile << '\n';
        return 1;
    }

    std::vector<std::string> prefixes;
    std::string line;
    while (std::getline(prefix_input, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    // For each prefix, print matching movies (in CSV order)
    for (const std::string& prefix : prefixes) {
        std::vector<Movie> matches = movies.withPrefix(prefix);
        if (!matches.empty()) {
            for (const Movie& m : matches) {
                std::cout << m.title << ", " << m.rating << '\n';
            }

            // Find best movie (highest rating)
            const Movie* best = &matches[0];
            for (const Movie& m : matches) {
                if (m.rating > best->rating) {
                    best = &m;
                }
            }
            std::cout << "Best movie with prefix " << prefix << " is: " << best->title << " with rating " << best->rating << '\n';
        } else {
            std::cout << "No movies found with prefix " << prefix << '\n';
        }
    }

    return 0;
}
