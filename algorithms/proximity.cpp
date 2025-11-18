#include "proximity.h"
#include <unordered_map>
#include <queue>
#include <utility>
#include <cmath> 

using namespace std;

// We're storing <score, userID>
// Score is now a 'double' because it's no longer a simple count
using ScorePair = pair<double, int>;

vector<int> recommend_by_proximity(const SocialNetwork& network, int userID, int top_k) {
    // This map will store: <candidate_userID, adamic_adar_score>
    unordered_map<int, double> adamicAdarScores;

    const auto& myFriends = network.get_friends(userID);

    // --- Core Algorithm ---
    for (int friendID : myFriends) {
        for (int fofID : network.get_friends(friendID)) {
            
            if (fofID == userID) continue;
            if (myFriends.count(fofID)) continue;

            // --- THIS IS THE UPGRADED LOGIC ---
            // 'friendID' is the common friend.
            int commonFriendDegree = network.get_degree(friendID);

            // We use log() which is natural log. log10() also works.
            // We check degree > 1 because log(1) = 0, which causes division by zero.
            if (commonFriendDegree > 1) {
                adamicAdarScores[fofID] += 1.0 / log(commonFriendDegree);
            }
            // If degree is 1, they add 0 score (log(1) is undefined in this formula)
        }
    }

    // --- Get Top K Results ---
    priority_queue<ScorePair> pq;
    for (auto const& [candidateID, score] : adamicAdarScores) {
        pq.push({score, candidateID});
    }

    // --- Format Output ---
    vector<int> recommendations;
    while (!pq.empty() && recommendations.size() < static_cast<size_t>(top_k)) {
        recommendations.push_back(pq.top().second);
        pq.pop();
    }

    return recommendations;
}