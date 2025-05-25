#pragma once
#include <string>
#include <vector>
struct Movie{
    std::string title;
    double rating;
};

class Movies{
    public:
        void readCSV(const std::string& filename);
        void printAll()const;
        std::vector<Movie> withPrefix(const std::string& prefix) const;
    
    private:
        std::vector<Movie> data; // sorted by title after readCSV
    };
