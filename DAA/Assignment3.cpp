// Name:Chaitanya Ashok Chormale
//PRN:123B1F014
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;


struct Item {
    string name;
    double weight;     
    double value;      
    bool divisible;   

    double valuePerWeight() const {
        return value / weight;
    }
};


bool compare(Item a, Item b) {
    return a.valuePerWeight() > b.valuePerWeight();
}


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

        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            totalValue += item.value;
            cout << left << setw(15) << item.name
                 << setw(15) << item.weight
                 << setw(15) << item.value << endl;
        } 
        else if (item.divisible) {
          
            double remain = capacity - currentWeight;
            double fraction = remain / item.weight;
            double valueTaken = item.value * fraction;

            currentWeight += remain;
            totalValue += valueTaken;
            cout << left << setw(15) << item.name
                 << setw(15) << remain
                 << setw(15) << valueTaken << endl;
            break; 
        }
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

