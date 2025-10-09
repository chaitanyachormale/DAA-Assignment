#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    double value, weight;
    bool divisible;

    Item(double v, double w, bool d) : value(v), weight(w), divisible(d) {}
};

// Function to calculate the maximum total utility value
double getMaxValue(vector<Item>& items, double capacity) {
    // Sort items by value-to-weight ratio in descending order
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (a.value / a.weight) > (b.value / b.weight);
    });

    double totalValue = 0.0;
    double currentWeight = 0.0;

    for (const Item& item : items) {
        if (currentWeight + item.weight <= capacity) {
            // Take the whole item
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            // Take fraction only if divisible
            if (item.divisible) {
                double remaining = capacity - currentWeight;
                totalValue += (item.value / item.weight) * remaining;
                currentWeight += remaining;
            }
            // Capacity full
            break;
        }
    }

    return totalValue;
}

int main() {
    double W;
    int n;

    cout << "Enter total weight capacity of the boat (kg): ";
    cin >> W;

    cout << "Enter number of relief items: ";
    cin >> n;

    vector<Item> items;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for item " << i + 1 << ":\n";
        double value, weight;
        int div;

        cout << "Utility value: ";
        cin >> value;

        cout << "Weight (kg): ";
        cin >> weight;

        cout << "Is the item divisible? (1 = Yes, 0 = No): ";
        cin >> div;

        items.emplace_back(value, weight, div == 1);
    }

    double maxValue = getMaxValue(items, W);
    cout << fixed << setprecision(2);
    cout << "\nMaximum total utility value that can be carried: " << maxValue << "\n";

    return 0;
}
