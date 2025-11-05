#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure to represent a relief item
struct Item {
    string name;
    double weight;     // weight in kg
    double value;      // utility value
    bool divisible;    // true if item can be divided (e.g. food/water)

    double valuePerWeight() const {
        return value / weight;
    }
};

// Comparator: sort items by value-to-weight ratio in descending order
bool compare(Item a, Item b) {
    return a.valuePerWeight() > b.valuePerWeight();
}

// Fractional Knapsack algorithm
double fractionalKnapsack(vector<Item> &items, double capacity) {
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    double currentWeight = 0.0;

    cout << "\nItems selected for transport:\n";
    cout << left << setw(15) << "Item"
         << setw(15) << "WeightTaken"
         << setw(15) << "ValueGained" << endl;
    cout << string(45, '-') << endl;

    for (auto &item : items) {
        if (currentWeight >= capacity)
            break;

        // If item can be fully taken
        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            totalValue += item.value;
            cout << left << setw(15) << item.name
                 << setw(15) << item.weight
                 << setw(15) << item.value << endl;
        } 
        else if (item.divisible) {
            // Take fractional part of divisible items
            double remain = capacity - currentWeight;
            double fraction = remain / item.weight;
            double valueTaken = item.value * fraction;

            currentWeight += remain;
            totalValue += valueTaken;
            cout << left << setw(15) << item.name
                 << setw(15) << remain
                 << setw(15) << valueTaken << endl;
            break; // boat is full
        }
        // If item is indivisible and can't fit, skip it
    }

    cout << "\nTotal weight carried: " << currentWeight << " / " << capacity << " kg\n";
    cout << "Maximum total utility value: " << totalValue << endl;

    return totalValue;
}

int main() {
    int n;
    double capacity;

    cout << "Enter number of relief items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "\nEnter details for each item (Name Weight Value Divisible[1/0]):\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].name >> items[i].weight >> items[i].value >> items[i].divisible;
    }

    cout << "\nEnter maximum weight capacity of boat (kg): ";
    cin >> capacity;

    fractionalKnapsack(items, capacity);

    return 0;
}
