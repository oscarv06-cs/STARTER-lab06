#include "movies.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> 
#include <algorithm>

void Movies::readCSV(const std::string& filename){
    std::ifstream file_input(filename);
    if (!file_input){
        std::cerr << "Error: Cannot Open the file " << filename << '\n';
        return;
    }
    std::string line;
    while (std::getline(file_input, line)) {
        std::istringstream line_stream(line);
        std::string title, ratingStr;
    
        if (std::getline(line_stream, title, ',') && std::getline(line_stream, ratingStr)) {
            if (!ratingStr.empty()) { // Check if ratingStr is not empty
                try {
                    double rating = std::stod(ratingStr);
                    data.push_back({title, rating});
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid rating found in line: " << line << std::endl;
                }
            }
        }
    }
    
    std::sort(data.begin(), data.end(),
        [](const Movie& a, const Movie& b) { return a.title < b.title; });

}

void Movies::printAll()const {
    std::cout << std::fixed << std::setprecision(1);
    for (const Movie& m : data){
        std::cout << m.title << ", " << m.rating << '\n';
    }
}
std::vector<Movie> Movies::withPrefix(const std::string& prefix) const {
    std::vector<Movie> result;
    for (const Movie& m : data) {
        if (m.title.compare(0, prefix.size(), prefix) == 0) {
            result.push_back(m);
        }
    }
    return result;
}

