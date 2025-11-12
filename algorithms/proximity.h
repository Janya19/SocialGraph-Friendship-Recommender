#pragma once
// using namespace std;
#include "../SocialNetwork.h"
#include <vector>

/**
 * @brief Recommends users based on proximity (common friends count).
 * @param network The populated SocialNetwork object.
 * @param userID The user to generate recommendations for.
 * @param top_k The number of recommendations to return.
 * @return A vectorof recommended user IDs, sorted by score.
 */
vector<int> recommend_by_proximity(const SocialNetwork& network, int userID, int top_k);