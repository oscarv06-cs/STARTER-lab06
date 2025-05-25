#include "movies.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "utilities.h"

// Reads the CSV file and stores the data
void Movies::readCSV(const std::string& filename){
    std::ifstream file_input(filename);
    if (!file_input){
        std::cerr << "Error: Cannot Open the file " << filename << '\n';
        return;
    }
    std::string line, title;
    double rating;
    while (std::getline(file_input, line)) {
        if (parseLine(line, title, rating)) {
            data.push_back({title, rating});
        }
    }
}

// Prints all movies in alphabetical order of title
void Movies::printAll() const {
    std::vector<Movie> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end(), [](const Movie& a, const Movie& b){
        return a.title < b.title;
    });

    std::cout << std::fixed << std::setprecision(1);
    for (const Movie& m : sortedData){
        std::cout << m.title << ", " << m.rating << '\n';
    }
}

// Returns a vector of movies that start with the given prefix
std::vector<Movie> Movies::withPrefix(const std::string& prefix) const {
    std::vector<Movie> result;
    for (const Movie& m : data) {
        if (m.title.compare(0, prefix.size(), prefix) == 0) {
            result.push_back(m);
        }
    }
    return result;
}
