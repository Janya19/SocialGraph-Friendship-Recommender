#include "closeness.h"
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

unordered_map<int, double> calculate_closeness_scores(const SocialNetwork& network) {
    
    const auto& allUsers = network.get_all_users();
    int N = allUsers.size();
    if (N <= 1) return {};

    unordered_map<int, double> scores;

    // --- Loop 1: Run BFS from every single user (All-Pairs-Shortest-Path) ---
    for (int startUser : allUsers) {
        
        // 1. Setup BFS for distance calculation
        queue<int> q;
        // map<UserID, DistanceFromStartNode>
        unordered_map<int, int> distance; 
        
        q.push(startUser);
        distance[startUser] = 0;
        
        int sum_of_distances = 0;
        int reachable_nodes = 0;

        // 2. Run the BFS
        while (!q.empty()) {
            int currentUser = q.front();
            q.pop();

            // Add this node's distance to the total sum
            sum_of_distances += distance[currentUser];
            
            // Check neighbors
            for (int neighbor : network.get_friends(currentUser)) {
                // If distance map does not contain the neighbor, it's unvisited
                if (distance.find(neighbor) == distance.end()) {
                    distance[neighbor] = distance[currentUser] + 1;
                    q.push(neighbor);
                    reachable_nodes++;
                }
            }
        }
        
        // --- 3. Calculate Closeness Score ---
        // Closeness is only calculated if the entire network is reachable (i.e., N-1 nodes)
        // Note: For simplicity and since our graph is connected, we assume all N-1 nodes are reachable.
        if (sum_of_distances > 0) {
            // Closeness = (N - 1) / sum of all shortest paths
            scores[startUser] = (double)(N - 1) / sum_of_distances;
        } else {
            // Should only happen if N=1 or error. We set score to 0.
            scores[startUser] = 0.0;
        }
    }
    
    return scores;
}