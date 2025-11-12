#pragma once
// using namespace std;
#include "../SocialNetwork.h"
#include <vector>

/**
 * @brief Recommends users using a hybrid rank-based approach.
 * @param network The populated SocialNetwork object.
 * @param userID The user to generate recommendations for.
 * @param top_k The number of recommendations to return.
 * @param w_influence The weight given to the influence rank.
 * @param w_proximity The weight given to the proximity rank.
 * @return A vectorof recommended user IDs, sorted by hybrid score.
 */
vector<int> recommend_by_hybrid(const SocialNetwork& network, int userID, int top_k,
                                       double w_influence, double w_proximity);