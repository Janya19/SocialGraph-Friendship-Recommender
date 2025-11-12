#pragma once
// using namespace std;
#include "../SocialNetwork.h" // Note the "../" to go up one directory
#include <vector>

/**
 * @brief Recommends users based on influence (Degree * Jaccard).
 * @param network The populated SocialNetwork object.
 * @param userID The user to generate recommendations for.
 * @param top_k The number of recommendations to return.
 * @return A vector of recommended user IDs, sorted by score.
 */
vector<int> recommend_by_influence(const SocialNetwork& network, int userID, int top_k);