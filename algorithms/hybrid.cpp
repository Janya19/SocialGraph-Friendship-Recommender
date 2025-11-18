#include "hybrid.h"
#include "influence.h"
#include "proximity.h"
#include "utils.h"
#include "pagerank.h"
#include <unordered_map>
#include <queue>
#include <utility>
#include <cmath>

using namespace std;
using ScorePair = pair<double, int>;

vector<int> recommend_by_hybrid(const SocialNetwork& network, int userID, int top_k, double w_influence, double w_proximity) {
    
    unordered_map<int, double> hybridScores;

    // --- Pre-calculate PageRank ---
    unordered_map<int, double> pagerank_scores = calculate_pagerank(network);

    // --- Influence Score Logic ---
    const auto& myFriends = network.get_friends(userID);
    const auto& myTags = network.get_tags(userID);
    
    for (int candidateID : network.get_all_users()) {
        if (candidateID == userID || myFriends.count(candidateID)) continue;

        const auto& candidateTags = network.get_tags(candidateID);
        double jaccard = jaccard_similarity(myTags, candidateTags);
        
        double pagerank = pagerank_scores[candidateID];
        double influenceScore = pagerank * jaccard;

        if (influenceScore > 0) {
            hybridScores[candidateID] += w_influence * influenceScore;
        }
    }

    // --- Proximity Score Logic ---
    for (int friendID : myFriends) {
        for (int fofID : network.get_friends(friendID)) {
            if (fofID == userID || myFriends.count(fofID)) continue;
            
            int commonFriendDegree = network.get_degree(friendID);
            if (commonFriendDegree > 1) {
                hybridScores[fofID] += w_proximity * (1.0 / log(commonFriendDegree)); 
            }
        }
    }

    // --- Get Top K Results ---
    priority_queue<ScorePair> pq;
    for (auto const& [candidateID, score] : hybridScores) {
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