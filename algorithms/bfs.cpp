#include "bfs.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm> // For std::reverse

vector<int> get_shortest_path(const SocialNetwork& network, int startUser, int endUser) {
    vector<int> path; // This is what we will return

    // 1. Handle edge cases
    if (startUser == endUser) {
        return {startUser}; // Path to yourself is just you
    }
    
    // 2. Setup BFS data structures
    queue<int> q; // The queue for nodes to visit
    unordered_set<int> visited; // To avoid loops
    
    // "parent_map" is the key. It stores: map<node, its_parent>
    // How did we get to node 'B'? From 'A'. So: parent_map[B] = A
    unordered_map<int, int> parent_map;

    // 3. Start the BFS
    q.push(startUser);
    visited.insert(startUser);
    parent_map[startUser] = -1; // The start user has no parent

    bool found = false;

    while (!q.empty()) {
        int currentUser = q.front();
        q.pop();

        if (currentUser == endUser) {
            found = true;
            break; // We found the target!
        }

        // Add all neighbors to the queue
        for (int neighbor : network.get_friends(currentUser)) {
            if (visited.find(neighbor) == visited.end()) {
                // This is a new node
                visited.insert(neighbor);
                parent_map[neighbor] = currentUser; // We got to 'neighbor' from 'currentUser'
                q.push(neighbor);
            }
        }
    }

    // 4. Reconstruct the path
    if (found) {
        int current = endUser;
        while (current != -1) {
            path.push_back(current);
            current = parent_map[current]; // Walk backwards up the chain
        }
        // The path is backwards (endUser -> startUser), so reverse it
        reverse(path.begin(), path.end());
    }
    
    return path; // Will be empty if 'found' is false
}