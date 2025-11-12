#include "influence.h"
#include "utils.h"
#include "pagerank.h" // <-- It calls your pagerank function
#include <queue>
#include <vector>
#include <utility>
#include <unordered_map> 

using namespace std;
using ScorePair = pair<double, int>;

vector<int> recommend_by_influence(const SocialNetwork& network, int userID, int top_k) {
    
    // --- Caclulate PageRank scores ONCE ---
    unordered_map<int, double> pagerank_scores = calculate_pagerank(network);

    priority_queue<ScorePair> pq;
    const auto& myFriends = network.get_friends(userID);
    const auto& myTags = network.get_tags(userID);

    for (int candidateID : network.get_all_users()) {
        if (candidateID == userID) continue;
        if (myFriends.count(candidateID)) continue;

        // --- Calculate Score ---
        const auto& candidateTags = network.get_tags(candidateID);
        double jaccard = jaccard_similarity(myTags, candidateTags);
        
        // --- UPGRADED LOGIC ---
        // Get the pre-calculated PageRank score
        double pagerank = pagerank_scores[candidateID]; 
        
        // Final Score: PageRank * Jaccard
        double finalScore = pagerank * jaccard;

        if (finalScore > 0) {
            pq.push({finalScore, candidateID});
        }
    }

    // --- Format Output ---
    vector<int> recommendations;
    while (!pq.empty() && recommendations.size() < static_cast<size_t>(top_k)) {
        recommendations.push_back(pq.top().second); 
        pq.pop(); 
    }
    return recommendations;
}