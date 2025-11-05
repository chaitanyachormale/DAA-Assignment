// Name:Chaitanya Ashok Chormale
//PRN:123B1F014
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;


struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    long long watchTime; 
};

void swap(Movie &a, Movie &b) {
    Movie temp = a;
    a = b;
    b = temp;
}


int partition(vector<Movie> &movies, int low, int high, const string &parameter) {
    double pivotValue;

 
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
            condition = movies[j].imdbRating >= pivotValue; 
        else if (parameter == "year")
            condition = movies[j].releaseYear >= pivotValue; 
        else
            condition = movies[j].watchTime >= pivotValue;

        if (condition) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return (i + 1);
}


void quickSort(vector<Movie> &movies, int low, int high, const string &parameter) {
    if (low < high) {
        int pi = partition(movies, low, high, parameter);
        quickSort(movies, low, pi - 1, parameter);
        quickSort(movies, pi + 1, high, parameter);
    }
}


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

