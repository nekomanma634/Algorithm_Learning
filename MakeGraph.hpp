#include <bits/stdc++.h>

struct edge {
    int next;
    int weight;
};
using Graph = std::vector<std::vector<edge>>;

// Weighted Directed Acyclic Graph (DAG)
Graph MakeGraph_DAG(int node, int seed){
    Graph graph(node);

    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> weight_dist(1, 10);

    for (int i = 0; i < node - 1; ++i) {
        graph[i].push_back({i + 1, weight_dist(mt)});
        
        if (i + 2 < node) graph[i].push_back({i + 2, weight_dist(mt)});
        if (i + 3 < node) graph[i].push_back({i + 3, weight_dist(mt)});
    }

    return graph;
}

// Weighted Directed Cyclic Graph (DCG)
Graph MakeGraph_Cyclic(int node, int seed){
    Graph graph(node);

    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> weight_dist(1, 10);
    std::uniform_int_distribution<int> rand_percent(1, 100); 

    for (int i = 0; i < node - 1; ++i) {
        graph[i].push_back({i + 1, weight_dist(mt)});
        if (i + 2 < node) graph[i].push_back({i + 2, weight_dist(mt)});
        if (i + 3 < node) graph[i].push_back({i + 3, weight_dist(mt)});

        if (i > 0 && rand_percent(mt) <= 30) {
            std::uniform_int_distribution<int> back_node_dist(0, i - 1);
            int back_node = back_node_dist(mt);
            graph[i].push_back({back_node, weight_dist(mt)});
        }
    }

    return graph;
}

// Random Directed Tree
Graph MakeGraph_Tree(int node, int seed) {
    Graph graph(node);
    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> weight_dist(1, 10);

    for (int i = 1; i < node; ++i) {
        std::uniform_int_distribution<int> parent_dist(0, i - 1);
        int parent = parent_dist(mt);
        
        graph[parent].push_back({i, weight_dist(mt)});
        
        // ※無向グラフ（双方向）にしたい場合は以下をコメントアウト解除
        // graph[i].push_back({parent, weight_dist(mt)});
    }
    return graph;
}

// Complete Graph
Graph MakeGraph_Complete(int node, int seed) {
    Graph graph(node);
    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> weight_dist(1, 10);

    for (int i = 0; i < node; ++i) {
        for (int j = 0; j < node; ++j) {
            if (i == j) continue;
            
            graph[i].push_back({j, weight_dist(mt)});
        }
    }
    return graph;
}

// Star Graph
Graph MakeGraph_Star(int node, int seed) {
    Graph graph(node);
    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> weight_dist(1, 10);

    for (int i = 1; i < node; ++i) {
        int w = weight_dist(mt);
        graph[0].push_back({i, w});
        
        // ※中心に向かって戻る（双方向）にしたい場合は以下をコメントアウト解除
        // graph[i].push_back({0, w});
    }
    return graph;
}