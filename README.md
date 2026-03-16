# SocialGraph: Friendship Recommender & Network Analyzer

A dynamic, stateful C++ application that models a social network graph and provides advanced friend recommendations, network topology analysis, and interactive web-based data visualization. Built entirely from scratch using standard C++ libraries.

## Key Features

### 1. Advanced Graph Algorithms
The core engine utilizes several well-known data science algorithms to deliver highly intelligent friendship recommendations and network analysis:
- **Influence (PageRank + Jaccard):** Recommends users based on shared interests (Jaccard Similarity) coupled with true network influence computed via the **PageRank** algorithm (transitive popularity).
- **Proximity (Adamic-Adar Index):** Evaluates "friends-of-friends." Unlike simple common-friend counts, Adamic-Adar gives more weight to shared friends who are less connected themselves, predicting much stronger intimate connections.
- **Hybrid Recommender:** A robust, weighted ensemble model fusing the normalized PageRank/Jaccard score with the Adamic-Adar index.
- **Degrees of Separation (BFS):** Implements a Breadth-First Search to find the shortest path between any two disparate users.
- **Network Centrality:** Computes Betweenness Centrality and Closeness Centrality to identify the most critical bridge nodes and most accessible users in the graph.
- **Community Detection:** Analyzes the network structure to uncover isolated or tightly-knit sub-communities.

### 2. Dynamic Graph Engine & Persistence
The social network is highly interactive and perfectly stateful.
- **Graph Mutations:** Add new users, assign them a custom list of personality tags (solving the "cold start" recommendation problem), and dynamically forge or sever undirected friendship edges.
- **Automatic Persistence:** Upon exiting the application, all structural changes (nodes, edges, tags) are automatically serialized and saved to flat-file storage in the `data/` directory, ensuring no work is lost between sessions.

### 3. Interactive Web Export & Visualization
The C++ backend includes a custom `WebExporter` that serializes the current network state into JavaScript (`graph_data.js`).
- **Browser-based Visuals:** Open `index.html` to view a stunning, interactive force-directed graph of the social network.
- **Rich Metadata:** Nodes are colored heuristically based on user tags (e.g., coding, art, sports). The web view exposes user details, tag arrays, friend lists, and computed PageRank scores via interactive profile cards.

## Tech Stack & Architecture
- **Language:** C++17 (Strictly standard library - STL: `std::unordered_map`, `std::unordered_set`, `std::vector`, etc.)
- **Frontend Visualization:** HTML5, CSS3, JavaScript (consuming the exported C++ data structures)
- **Architecture:** 
  - `SocialNetwork`: Core class encapsulating the graph adjacency lists and disk I/O.
  - `algorithms/`: Modular, custom-built implementations of PageRank, Adamic-Adar, BFS, Centrality, and Community Detection.
  - `WebExporter`: Data serialization layer mapping C++ state to JS objects.

## Code Structure

- `src/`: Contains all of the source code (`.cpp`) files.
  - `main.cpp`: Contains all the logic for the interactive menu system and user input validation.
  - `SocialNetwork.cpp`: Core logic for managing graph modifications and file I/O.
  - `algorithms/`: Modular implementations of PageRank, BFS, Adamic-Adar, etc.
- `include/`: Contains all header (`.h`) declarations for the project structure.
  - `SocialNetwork.h`: Interface for the adjacency lists and tag graph.
  - `WebExporter.h`: Data serialization layer mapping C++ state to JS objects.
  - `LogManager.h`: Tracks the internal history.
  - `algorithms/`: The interface APIs for the advanced graph algorithms.
- `data/`: Contains the graph edge list and tag files.
- `Makefile`: The build script mapping the `src/` files using `-Iinclude`.

## Compilation & Usage

Use the provided `Makefile` to compile the C++ application into a single executable:

```bash
# Compile the application
make

# Run the interactive CLI menu
./recommender
```

To view the network visualization, simply open `index.html` in any modern web browser after interacting with the console app to generate updated data.

To clean up object files:
```bash
make clean
```
