// Winter'24
// Instructor: Diba Mirza
// Student name: Oscar Valeriano

#include "movies.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <movie_csv> [prefix_file]\n";
        return 1;
    }

    std::string movieFile = argv[1];
    Movies movies;
    movies.readCSV(movieFile);

    if (argc == 2) {
        // Part 1: No prefixes, print all movies in alphabetical order
        movies.printAll();
        return 0;
    }

    // Part 2: prefixes file provided
    std::string prefixFile = argv[2];
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

    // For storing best movies for each prefix
    std::vector<std::pair<std::string, Movie>> bestMovies;

    for (size_t i = 0; i < prefixes.size(); ++i) {
        const std::string& prefix = prefixes[i];
        std::vector<Movie> matches = movies.withPrefix(prefix);

        if (matches.empty()) {
            std::cout << "No movies found with prefix " << prefix << '\n';
            continue;
        }

        // Sort matches by rating descending, then title ascending
        std::sort(matches.begin(), matches.end(), [](const Movie& a, const Movie& b) {
            if (a.rating != b.rating)
                return a.rating > b.rating;
            return a.title < b.title;
        });

        for (const Movie& m : matches) {
            std::cout << m.title << ", " << m.rating << '\n';
        }

        // Print blank line after matches - but only if there is another prefix after this one
        if (i + 1 < prefixes.size()) {
            std::cout << '\n';
        }

        bestMovies.emplace_back(prefix, matches[0]);
    }

    // Print best movie with prefix after all movies of each prefix
    for (const auto& pair : bestMovies) {
        std::cout << "Best movie with prefix " << pair.first << " is: " << pair.second.title
                  << " with rating " << pair.second.rating << '\n';
    }

    return 0;
}
