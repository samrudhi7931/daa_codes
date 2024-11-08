#include <iostream>
#include <queue>
using namespace std;

// Define the maximum number of items
const int MAX = 100;

// Class to represent a node in the decision tree
class Node {
public:
    int level;     // Level of the node in the tree (corresponds to the index of the item)
    int profit;    // Total profit at the current node
    int weight;    // Total weight at the current node
    float bound;   // Upper bound of the profit for the node

    Node() {
        level = -1;
        profit = 0;
        weight = 0;
        bound = 0.0;
    }
};

// Function to calculate the upper bound on profit for a node
float bound(Node u, int n, int W, int weights[], int values[]) {
    if (u.weight >= W)  // If weight exceeds capacity, bound is 0
        return 0;

    float profitBound = (float)u.profit;
    int totalWeight = u.weight;
    int j = u.level + 1;

    while (j < n && totalWeight + weights[j] <= W) {
        totalWeight += weights[j];
        profitBound += values[j];
        j++;
    }

    if (j < n)  // Add fractional part of the next item
        profitBound += (W - totalWeight) * (float)values[j] / weights[j];

    return profitBound;
}

// Function to solve the 0/1 Knapsack problem using branch and bound
int knapsack(int n, int W, int weights[], int values[]) {
    queue<Node> Q;  // Queue to store nodes
    Node u, v;      // u: Current node, v: Child node

    v.bound = bound(v, n, W, weights, values);
    Q.push(v);

    int maxProfit = 0;

    while (!Q.empty()) {
        v = Q.front();
        Q.pop();

        if (v.level == -1) // Initialize root node
            u.level = 0;
        else
            u.level = v.level + 1;

        if (u.level < n) {
            // Consider including the current item
            u.weight = v.weight + weights[u.level];
            u.profit = v.profit + values[u.level];

            if (u.weight <= W && u.profit > maxProfit) {
                maxProfit = u.profit;  // Update max profit
            }

            u.bound = bound(u, n, W, weights, values);
            if (u.bound > maxProfit)
                Q.push(u);  // Enqueue left child

            // Consider excluding the current item
            u.weight = v.weight;
            u.profit = v.profit;
            u.bound = bound(u, n, W, weights, values);
            if (u.bound > maxProfit)
                Q.push(u);  // Enqueue right child
        }
    }

    return maxProfit;
}

int main() {
    int n, W;
    int weights[MAX], values[MAX];

    cout << "Enter the number of items: ";
    cin >> n;

    cout << "Enter the weights and values of the items:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " weight: ";
        cin >> weights[i];
        cout << "Item " << i + 1 << " value: ";
        cin >> values[i];
    }

    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> W;

    int maxProfit = knapsack(n, W, weights, values);
    cout << "The maximum profit is: " << maxProfit << endl;

    return 0;
}

