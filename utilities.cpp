//Oscar Valeriano
#include "utilities.h"
#include <string>

bool parseLine(std::string &line, std::string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    if (commaIndex == std::string::npos) return false;

    movieName = line.substr(0, commaIndex);
    movieRating = std::stod(line.substr(commaIndex + 1));

    if (!movieName.empty() && movieName.front() == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}