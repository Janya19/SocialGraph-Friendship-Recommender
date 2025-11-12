#pragma once

#include "../SocialNetwork.h"
#include <vector>

/**
 * @brief Finds the shortest path between two users using BFS.
 * @param network The populated SocialNetwork object.
 * @param startUser The user ID to start the search from.
 * @param endUser The user ID to find a path to.
 * @return A std::vector<int> representing the path from start to end.
 * If no path is found, returns an empty vector.
 */
vector<int> get_shortest_path(const SocialNetwork& network, int startUser, int endUser);