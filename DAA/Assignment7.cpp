#include <bits/stdc++.h>
using namespace std;

class TimetableScheduler {
private:
    int numCourses;
    vector<vector<int>> adj; // adjacency list (conflicts)
    vector<int> color;       // assigned colors to courses

public:
    TimetableScheduler(int n) {
        numCourses = n;
        adj.resize(n);
        color.assign(n, -1);
    }

    // Add edge if two courses have overlapping students
    void addConflict(int c1, int c2) {
        adj[c1].push_back(c2);
        adj[c2].push_back(c1);
    }

    // ==============================
    // 1️⃣ GREEDY COLORING ALGORITHM
    // ==============================
    int greedyColoring() {
        color.assign(numCourses, -1);
        color[0] = 0; // assign first color to first course

        vector<bool> available(numCourses, false);

        for (int u = 1; u < numCourses; u++) {
            // Mark colors used by adjacent vertices
            for (int v : adj[u]) {
                if (color[v] != -1)
                    available[color[v]] = true;
            }

            // Find the first available color
            int cr;
            for (cr = 0; cr < numCourses; cr++)
                if (!available[cr]) break;

            color[u] = cr; // assign color

            // Reset availability
            for (int v : adj[u]) {
                if (color[v] != -1)
                    available[color[v]] = false;
            }
        }

        // Find total colors used
        int maxColor = *max_element(color.begin(), color.end()) + 1;
        return maxColor;
    }

    // ==============================
    // 2️⃣ WELSH-POWELL ALGORITHM
    // ==============================
    int welshPowellColoring() {
        vector<pair<int, int>> degree(numCourses);
        for (int i = 0; i < numCourses; i++)
            degree[i] = {adj[i].size(), i};

        // Sort vertices by descending degree
        sort(degree.rbegin(), degree.rend());

        color.assign(numCourses, -1);
        int colorCount = 0;

        for (auto &d : degree) {
            int v = d.second;
            if (color[v] == -1) {
                color[v] = colorCount;

                for (auto &d2 : degree) {
                    int u = d2.second;
                    if (color[u] == -1) {
                        bool canColor = true;
                        for (int w : adj[u]) {
                            if (color[w] == colorCount) {
                                canColor = false;
                                break;
                            }
                        }
                        if (canColor)
                            color[u] = colorCount;
                    }
                }
                colorCount++;
            }
        }
        return colorCount;
    }

    // ==============================
    // 3️⃣ DSATUR ALGORITHM (Degree of Saturation)
    // ==============================
    int dsaturColoring() {
        vector<int> degree(numCourses, 0), saturation(numCourses, 0);
        color.assign(numCourses, -1);

        for (int i = 0; i < numCourses; i++)
            degree[i] = adj[i].size();

        int coloredCount = 0;
        while (coloredCount < numCourses) {
            int maxSat = -1, maxDeg = -1, node = -1;
            for (int i = 0; i < numCourses; i++) {
                if (color[i] == -1) {
                    if (saturation[i] > maxSat || (saturation[i] == maxSat && degree[i] > maxDeg)) {
                        maxSat = saturation[i];
                        maxDeg = degree[i];
                        node = i;
                    }
                }
            }

            // Find smallest available color
            vector<bool> used(numCourses, false);
            for (int v : adj[node]) {
                if (color[v] != -1)
                    used[color[v]] = true;
            }
            int c;
            for (c = 0; c < numCourses; c++)
                if (!used[c]) break;

            color[node] = c;
            coloredCount++;

            // Update saturation of neighbors
            for (int v : adj[node]) {
                if (color[v] == -1) {
                    set<int> uniqueColors;
                    for (int x : adj[v])
                        if (color[x] != -1)
                            uniqueColors.insert(color[x]);
                    saturation[v] = uniqueColors.size();
                }
            }
        }

        int maxColor = *max_element(color.begin(), color.end()) + 1;
        return maxColor;
    }

    // Display the schedule
    void displaySchedule(int totalColors) {
        cout << "\nTotal Exam Slots Required: " << totalColors << "\n";
        for (int i = 0; i < numCourses; i++) {
            cout << "Course " << i << " → Slot " << color[i] << "\n";
        }
    }
};

// ==============================
// MAIN PROGRAM
// ==============================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int courses, conflicts;
    cout << "Enter number of courses and conflict pairs: ";
    cin >> courses >> conflicts;

    TimetableScheduler scheduler(courses);

    cout << "Enter conflict pairs (course1 course2):\n";
    for (int i = 0; i < conflicts; i++) {
        int c1, c2;
        cin >> c1 >> c2;
        scheduler.addConflict(c1, c2);
    }

    cout << "\n=== University Exam Scheduling ===";

    // 1️⃣ Greedy Coloring
    auto start = chrono::high_resolution_clock::now();
    int greedySlots = scheduler.greedyColoring();
    auto end = chrono::high_resolution_clock::now();
    cout << "\n\n[Greedy Coloring]";
    scheduler.displaySchedule(greedySlots);
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs\n";

    // 2️⃣ Welsh-Powell
    start = chrono::high_resolution_clock::now();
    int wpSlots = scheduler.welshPowellColoring();
    end = chrono::high_resolution_clock::now();
    cout << "\n[Welsh-Powell Coloring]";
    scheduler.displaySchedule(wpSlots);
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs\n";

    // 3️⃣ DSATUR
    start = chrono::high_resolution_clock::now();
    int dsSlots = scheduler.dsaturColoring();
    end = chrono::high_resolution_clock::now();
    cout << "\n[DSATUR Coloring]";
    scheduler.displaySchedule(dsSlots);
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs\n";

    return 0;
}
