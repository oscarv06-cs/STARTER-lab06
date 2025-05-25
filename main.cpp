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
    std::chrono::duration<double> elapsed = end - start;
    std::cerr << "Elapsed time: " << elapsed.count() << " seconds.\n";
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
1. **Reading and Sorting Movies:**  
   - Reading all movies from file: O(n)
   - Sorting all movies by title: O(n log n)  
   - **Total:** O(n log n)
2. **Processing Prefixes:**  
   For each prefix:
   - Binary search for the first movie with the prefix (using `lower_bound`): O(log n)
   - Collect all k matching movies: O(k)
   - Sorting k matches by rating (and title): O(k log k)
   - **Total per prefix:** O(log n + k log k)
   - **Total for m prefixes:** O(m (log n + k log k))
**Overall Time Complexity:**  
O(n log n + m (log n + k log k))

Empirical Runtimes

Below are the measured runtimes (in milliseconds) for the random datasets using `prefix_large.txt` as input.


 Dataset                   Runtime (ms) 
 input_20_random.csv          2         
 input_100_random.csv         5         
 input_1000_random.csv       30         
 input_76920_random.csv     950         

The runtime increases sub-linearly with n, consistent with our O(n log n + m (log n + k log k)) analysis.

---

## Part 3b: Space Complexity Analysis

- Storing all movies: O(n)
- Storing all prefixes: O(m)
- Storing matches for a prefix: O(k) (not cumulative)
- No additional major data structures are used.

**Overall Space Complexity:**  
O(n + m + k)

---

## Part 3c: Time/Space Tradeoff Discussion

**Design Goal:**  
I primarily designed the algorithm for low time complexity, since the assignment and leaderboard emphasized fast performance for large input sizes.

- By sorting all movies up front and using binary search (`lower_bound`) for each prefix, I achieved fast prefix lookups.
- I avoided using heavy additional data structures (like a Trie) to keep space usage low, sticking with a sorted vector.
- Only temporary vectors for matches per prefix are created.

**Outcome:**  
I was able to achieve both low time and space complexity. The STL's efficient sort and binary search allowed fast queries with minimal additional memory.

**Which was harder to achieve?**  
Maintaining low time complexity for large datasets was the greater challenge, as a naive scan per prefix would have been too slow (O(nm)). The use of sorted data with binary search solved this efficiently.

---
*/