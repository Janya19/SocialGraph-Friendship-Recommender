#include "pagerank.h"
#include <vector>
#include <cmath>
#include <unordered_map> // <-- This was the missing include

using namespace std;

unordered_map<int, double> calculate_pagerank(
    const SocialNetwork& network,
    double dampingFactor,
    int iterations) {

    const auto& allUsers = network.get_all_users();
    int N = allUsers.size();
    if (N == 0) {
        return {}; // Handle empty graph
    }

    // Initialize scores: everyone starts with 1/N
    unordered_map<int, double> scores;
    for (int userID : allUsers) {
        scores[userID] = 1.0 / N;
    }

    // --- Power Iteration Loop ---
    for (int i = 0; i < iterations; ++i) {
        unordered_map<int, double> newScores; // Scores for this iteration
        double total_S_contribution = 0.0; // For handling "sink" nodes (no friends)

        // 1. Calculate contributions from all nodes
        for (int userID : allUsers) {
            int degree = network.get_degree(userID);
            
            if (degree == 0) {
                // This is a "sink" node. It contributes its score to everyone.
                total_S_contribution += scores[userID];
            } else {
                // This node gives its score to all its friends
                double contribution = scores[userID] / degree;
                for (int friendID : network.get_friends(userID)) {
                    newScores[friendID] += contribution;
                }
            }
        }
        
        // 2. Combine scores with the "damping factor"
        for (int userID : allUsers) {
            // (1-d)/N is the "random jump" probability
            // d * (newScores[userID] + ... ) is the "follow a link" probability
            newScores[userID] = (1.0 - dampingFactor) / N + 
                                dampingFactor * (newScores[userID] + total_S_contribution / N);
        }

        // 3. Update scores for the next iteration
        scores = newScores;
    }

    return scores;
}