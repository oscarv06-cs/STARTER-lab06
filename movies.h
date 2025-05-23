#pragma once
#include <string>
#include <vector>
struct Movie{
    std::string title;
    double rating;
};

class Movies{
public:
    void readCSV(const std::string& filename); //Reads the file name
    void printAll()const; //Will print everything in the file 

private:
    std::vector<Movie> data; // Stores movie data
};

