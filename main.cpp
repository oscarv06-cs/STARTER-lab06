// Winter'24
// Instructor: Diba Mirza
// Student name: Oscar Valeriano

#include <chrono>

#include "movies.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cerr << "Elapsed time: " << ms << " ms\n";
    return 0;
}
/*
# CS24 PA02 Report  
Oscar Valeriano Leiva
Part 3a: Time Complexity Analysis

Let:
- **n** = number of movies
- **m** = number of prefixes
- **k** = maximum number of movies matching a single prefix
- **l** = maximum length of a movie title

**Step-by-step Analysis:**
1. Reading and Sorting Movies: 
   - Reading the file into a vector: O(n)  
   - Sorting the movies by title: O(n log n)  
   So this part takes O(n log n).

2. Processing Prefixes:
   For each prefix:
   - Binary search to find the first match using `lower_bound`: O(log n)  
   - Collecting all k matches: O(k)  
   - Sorting those k movies by rating (and title if there’s a tie): O(k log k)  
   So for one prefix, it’s O(log n + k log k).  
   For all m prefixes, the total becomes O(m (log n + k log k)).

**Overall Time Complexity:**  
O(n log n + m (log n + k log k))

worse case, if all movies match a prefix (k = n):
O(n log n + m n log n)

Empirical Runtimes

Below are the measured runtimes (in milliseconds) for the random datasets


 Dataset                   Runtime (ms) 
 input_20_random.csv          4        
 input_100_random.csv         4
 input_1000_random.csv        6         
 input_76920_random.csv      92         

The runtimes grew slowly as the dataset got larger, which fits well with our expected O(n log n + m n log n) complexity.

## Part 3b: Space Complexity Analysis

Storing all movies is O(n)
Storing all prefixes is O(m)
Storing matches for a prefix is O(k)
No additional major data structures are used.

TOtal Space Complexity
O(n + m + k)
---
## Part 3c: Time/Space Tradeoff Discussion

**Design Goal:**  
I mainly designed my algorithm to be fast (low time complexity), especially since the assignment and leaderboard really emphasized speed for larger inputs.

 - By sorting movies up front and using binary search, I made sure lookups were quick.
- I didn’t add extra data structures like tries or trees—just a sorted vector so memory usage stayed low and so the implementation and thinking things out would be easier. 
- Temporary vectors for matches were the only extra memory I used. 

**How it turned out:**  
I was able to keep both time and space usage low. C++’s `std::sort` and `lower_bound` made everything efficient and easier to do.  
Between the two, keeping time complexity low was harder because scanning every prefix with a naive and brute approach would have been way too slow with the complexity being (O(nm)).
 Using a sorted vector with binary search helped me get around that and this was in the final code. 

---
*/