#include <bits/stdc++.h>
using namespace std;

class TimetableScheduler {
private:
    int numCourses;
    vector<vector<int>> adj;
    vector<int> color;

public:
    TimetableScheduler(int n) {
        numCourses = n;
        adj.resize(n);
        color.assign(n, -1);
    }

    // Add conflict (edge) between two courses
    void addConflict(int c1, int c2) {
        adj[c1].push_back(c2);
        adj[c2].push_back(c1);
    }

    // ==========================
    // 1️⃣ GREEDY COLORING
    // ==========================
    int greedyColoring() {
        color.assign(numCourses, -1);
        color[0] = 0;
        vector<bool> available(numCourses, false);

        for (int u = 1; u < numCourses; u++) {
            for (int v : adj[u])
                if (color[v] != -1)
                    available[color[v]] = true;

            int cr;
            for (cr = 0; cr < numCourses; cr++)
                if (!available[cr])
                    break;

            color[u] = cr;

            for (int v : adj[u])
                if (color[v] != -1)
                    available[color[v]] = false;
        }

        int totalColors = *max_element(color.begin(), color.end()) + 1;
        return totalColors;
    }

    // ==========================
    // 2️⃣ WELSH-POWELL ALGORITHM
    // ==========================
    int welshPowellColoring() {
        vector<pair<int, int>> degree(numCourses);
        for (int i = 0; i < numCourses; i++)
            degree[i] = {adj[i].size(), i};

        sort(degree.rbegin(), degree.rend()); // sort by degree descending
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
                        for (int w : adj[u])
                            if (color[w] == colorCount) {
                                canColor = false;
                                break;
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

    // ==========================
    // 3️⃣ DSATUR ALGORITHM
    // ==========================
    int dsaturColoring() {
        vector<int> degree(numCourses), saturation(numCourses, 0);
        for (int i = 0; i < numCourses; i++)
            degree[i] = adj[i].size();

        color.assign(numCourses, -1);
        int colored = 0;

        while (colored < numCourses) {
            int maxSat = -1, maxDeg = -1, node = -1;
            for (int i = 0; i < numCourses; i++) {
                if (color[i] == -1) {
                    if (saturation[i] > maxSat ||
                        (saturation[i] == maxSat && degree[i] > maxDeg)) {
                        maxSat = saturation[i];
                        maxDeg = degree[i];
                        node = i;
                    }
                }
            }

            vector<bool> used(numCourses, false);
            for (int v : adj[node])
                if (color[v] != -1)
                    used[color[v]] = true;

            int c;
            for (c = 0; c < numCourses; c++)
                if (!used[c])
                    break;

            color[node] = c;
            colored++;

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

        int totalColors = *max_element(color.begin(), color.end()) + 1;
        return totalColors;
    }

    // ==========================
    // 4️⃣ ROOM ALLOCATION EXTENSION
    // ==========================
    void allocateRooms(int totalColors, vector<int> roomCapacities, vector<int> courseSizes) {
        cout << "\n--- Room Allocation per Slot ---\n";
        for (int slot = 0; slot < totalColors; slot++) {
            cout << "\nTime Slot " << slot << ":\n";
            int totalStudents = 0;
            vector<int> coursesInSlot;
            for (int i = 0; i < numCourses; i++)
                if (color[i] == slot) {
                    totalStudents += courseSizes[i];
                    coursesInSlot.push_back(i);
                }

            cout << "Courses in slot: ";
            for (int c : coursesInSlot)
                cout << c << " ";
            cout << "\nTotal Students: " << totalStudents << endl;

            int totalRoomCapacity = accumulate(roomCapacities.begin(), roomCapacities.end(), 0);
            if (totalStudents <= totalRoomCapacity)
                cout << "✅ Room allocation feasible\n";
            else
                cout << "⚠️ Not enough room capacity! Adjust rooms or reassign exams.\n";
        }
    }

    // ==========================
    // Display Results
    // ==========================
    void displaySchedule(int slots) {
        cout << "\nTotal Exam Slots Required: " << slots << "\n";
        for (int i = 0; i < numCourses; i++)
            cout << "Course " << i << " → Slot " << color[i] << "\n";
    }
};

// ==========================
// MAIN FUNCTION
// ==========================
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

    // -------------------------
    // Compare Algorithms
    // -------------------------
    cout << "\n=== UNIVERSITY EXAM SCHEDULING ===\n";

    auto start = chrono::high_resolution_clock::now();
    int greedySlots = scheduler.greedyColoring();
    auto end = chrono::high_resolution_clock::now();
    cout << "\n[Greedy Coloring]";
    scheduler.displaySchedule(greedySlots);
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs\n";

    start = chrono::high_resolution_clock::now();
    int wpSlots = scheduler.welshPowellColoring();
    end = chrono::high_resolution_clock::now();
    cout << "\n[Welsh-Powell Coloring]";
    scheduler.displaySchedule(wpSlots);
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs\n";

    start = chrono::high_resolution_clock::now();
    int dsSlots = scheduler.dsaturColoring();
    end = chrono::high_resolution_clock::now();
    cout << "\n[DSATUR Coloring]";
    scheduler.displaySchedule(dsSlots);
    cout << "Execution Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs\n";

    // -------------------------
    // Room Allocation Extension
    // -------------------------
    cout << "\nEnter room capacities (e.g., 3 rooms): ";
    vector<int> roomCapacities(3);
    for (int &r : roomCapacities) cin >> r;

    cout << "Enter number of students in each course:\n";
    vector<int> courseSizes(courses);
    for (int &c : courseSizes) cin >> c;

    scheduler.allocateRooms(dsSlots, roomCapacities, courseSizes);

    return 0;
}
