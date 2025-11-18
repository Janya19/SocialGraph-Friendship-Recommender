#include "communities.h"
#include <unordered_map>
#include <vector>
#include <map>

using namespace std;

unordered_map<int, int> detect_communities(const SocialNetwork& network, int iterations) {
    
    const auto& allUsers = network.get_all_users();
    unordered_map<int, int> labels;

    // --- 1. Initialization ---
    // Every user starts with their own unique label (their ID)
    for (int userID : allUsers) {
        labels[userID] = userID;
    }

    // --- 2. Iteration ---
    for (int i = 0; i < iterations; ++i) {
        // We must update all at once, so we use a 'new_labels' map
        unordered_map<int, int> new_labels = labels;
        
        for (int userID : allUsers) {
            // --- Tally the votes from neighbors ---
            map<int, int> neighbor_votes; // map<LabelID, VoteCount>
            
            const auto& neighbors = network.get_friends(userID);
            if (neighbors.empty()) {
                continue; // This user has no friends, they keep their label
            }

            for (int friendID : neighbors) {
                neighbor_votes[labels[friendID]]++;
            }

            // --- Find the winning label ---
            int max_votes = 0;
            int winning_label = -1;
            
            // Find the label with the highest vote count
            for (auto const& [label, count] : neighbor_votes) {
                if (count > max_votes) {
                    max_votes = count;
                    winning_label = label;
                }
            }
            // Update the user's label for the *next* iteration
            new_labels[userID] = winning_label;
        }
        
        // All votes are in, update the main labels map
        labels = new_labels;
    }

    // --- 3. Return the final community map ---
    return labels;
}