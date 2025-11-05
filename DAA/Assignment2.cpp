#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

// Movie structure
struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    long long watchTime; // in minutes, or number of views
};

// Swap helper
void swap(Movie &a, Movie &b) {
    Movie temp = a;
    a = b;
    b = temp;
}

// Partition function for QuickSort
int partition(vector<Movie> &movies, int low, int high, const string &parameter) {
    double pivotValue;

    // Choose pivot value based on sorting parameter
    if (parameter == "rating") 
        pivotValue = movies[high].imdbRating;
    else if (parameter == "year") 
        pivotValue = movies[high].releaseYear;
    else 
        pivotValue = movies[high].watchTime;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool condition = false;

        if (parameter == "rating")
            condition = movies[j].imdbRating >= pivotValue; // higher rating first
        else if (parameter == "year")
            condition = movies[j].releaseYear >= pivotValue; // latest first
        else
            condition = movies[j].watchTime >= pivotValue; // more popular first

        if (condition) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return (i + 1);
}

// Recursive QuickSort
void quickSort(vector<Movie> &movies, int low, int high, const string &parameter) {
    if (low < high) {
        int pi = partition(movies, low, high, parameter);
        quickSort(movies, low, pi - 1, parameter);
        quickSort(movies, pi + 1, high, parameter);
    }
}

// Display movie list
void displayMovies(const vector<Movie> &movies) {
    for (const auto &m : movies) {
        cout << m.title << " | Rating: " << m.imdbRating 
             << " | Year: " << m.releaseYear
             << " | Watch Time: " << m.watchTime << " views\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter number of movies: ";
    cin >> n;

    vector<Movie> movies(n);

    cout << "\nEnter movie details (Title Rating Year WatchTime):\n";
    for (int i = 0; i < n; i++) {
        cin >> movies[i].title >> movies[i].imdbRating >> movies[i].releaseYear >> movies[i].watchTime;
    }

    string parameter;
    cout << "\nSort by parameter (rating/year/watchtime): ";
    cin >> parameter;

    // Normalize parameter
    if (parameter == "watch" || parameter == "watch_time")
        parameter = "watchtime";

    auto start = chrono::high_resolution_clock::now();
    quickSort(movies, 0, n - 1, parameter);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\nSorted Movies (based on " << parameter << "):\n";
    displayMovies(movies);

    cout << "\nSorting completed in " << duration.count() << " seconds.\n";

    return 0;
}
