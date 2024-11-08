#include <iostream>
#include <limits.h>
using namespace std;

#define N 4   // Define the number of cities as 4

// This function calculates the lower bound (minimum possible cost) for the remaining tour.
int calculateBound(int currentCost, int adjMatrix[N][N], bool visited[N], int currentCity) {
    int bound = currentCost;  // Start with the current cost
    
    int minOutgoing = INT_MAX;  // Variable to store the minimum outgoing edge cost

    // Find the minimum cost edge to an unvisited city
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            minOutgoing = min(minOutgoing, adjMatrix[currentCity][i]);
        }
    }

    // Add the minimum outgoing cost to the bound
    return bound + minOutgoing;
}

// This function implements the Branch and Bound approach for TSP
void tspBranchAndBound(int adjMatrix[N][N], int bestPath[N], int &minCost) {
    
    int currentPath[N];   // Array to store the current path
    bool visited[N] = {false};  // Track which cities are visited
    int currentCost = 0;  // Start with 0 cost

    currentPath[0] = 0;  // Start from city 0
    visited[0] = true;   // Mark city 0 as visited

    // Recursive function to explore all possible paths
    auto explorePaths = [&](int level, int currentCity, auto &explorePaths) -> void {
        
        if (level == N - 1) {  // If all cities are visited
            int tourCost = currentCost + adjMatrix[currentCity][0];  // Complete the tour by returning to the start
            if (tourCost < minCost) {  // If this tour has a lower cost, update the minimum cost and best path
                minCost = tourCost;
                for (int i = 0; i < N; i++) {
                    bestPath[i] = currentPath[i];
                }
            }
            return;  // Exit recursion
        }

        // Try visiting each unvisited city
        for (int nextCity = 0; nextCity < N; nextCity++) {
            if (!visited[nextCity]) {
                int costWithNextCity = currentCost + adjMatrix[currentCity][nextCity];  // Calculate the new cost
                
                // Calculate the bound and check if it's promising (less than the current best solution)
                int bound = calculateBound(costWithNextCity, adjMatrix, visited, nextCity);

                // If the bound is less than the minimum cost, continue exploring this path
                if (bound < minCost) {
                    visited[nextCity] = true;  // Mark the city as visited
                    currentPath[level + 1] = nextCity;  // Add the city to the current path
                    currentCost = costWithNextCity;  // Update the cost

                    // Recursively explore the next level
                    explorePaths(level + 1, nextCity, explorePaths);

                    // Backtrack: unmark the city as visited and restore the cost
                    visited[nextCity] = false;
                    currentCost -= adjMatrix[currentCity][nextCity];
                }
            }
        }
    };

    // Start exploring from the first city
    explorePaths(0, 0, explorePaths);
}

int main() {
   
    // Define the adjacency matrix that represents the distances between cities
    int adjMatrix[N][N] = {
        { 0, 10, 15, 20 },
        { 10, 0, 35, 25 },
        { 15, 35, 0, 30 },
        { 20, 25, 30, 0 }
    };

    int bestPath[N];  // Array to store the best path
    int minCost = INT_MAX;  // Initialize the minimum cost to a very large number

    // Call the Branch and Bound function
    tspBranchAndBound(adjMatrix, bestPath, minCost);

    // Output the results
    cout << "Minimum Cost: " << minCost << endl;
    cout << "Best Path: ";
    for (int i = 0; i < N; i++) {
        cout << bestPath[i] << " -> ";
    }
    cout << "0" << endl;  // Complete the path by returning to the starting city

    return 0;
}
