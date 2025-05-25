//Oscar Valeriano
#include "utilities.h"
#include <string>

bool parseLine(std::string &line, std::string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex + 1));
    if (!movieName.empty() && movieName[0] == '"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}