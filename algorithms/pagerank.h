#pragma once

#include "../SocialNetwork.h"
#include <unordered_map>

/**
 * @brief Calculates the PageRank score for all nodes in the graph.
 * @param network The populated SocialNetwork object.
 * @param dampingFactor (d) How much to trust the random walk. (0.85 is standard).
 * @param iterations The number of iterations to run. (More is more accurate).
 * @return An std::unordered_map<int, double> mapping UserID to PageRank score.
 */
std::unordered_map<int, double> calculate_pagerank(
    const SocialNetwork& network,
    double dampingFactor = 0.85,
    int iterations = 100
);