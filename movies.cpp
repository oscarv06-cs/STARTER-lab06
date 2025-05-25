#include "movies.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "utilities.h"

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
    std::sort(data.begin(), data.end(), [](const Movie& a, const Movie& b){
        return a.title < b.title;
    });
}

void Movies::printAll() const {
    std::cout << std::fixed << std::setprecision(1);
    for (const Movie& m : data){
        std::cout << m.title << ", " << m.rating << '\n';
    }
}

std::vector<Movie> Movies::withPrefix(const std::string& prefix) const {
    std::vector<Movie> result;
    auto comp = [](const Movie& m, const std::string& p) {
        return m.title.compare(0, p.size(), p) < 0;
    };
    auto it = std::lower_bound(data.begin(), data.end(), prefix, comp);
    while (it != data.end() && it->title.compare(0, prefix.size(), prefix) == 0) {
        result.push_back(*it);
        ++it;
    }
    return result;
}