#include "graph.hpp"

Graph::Graph(NodeId node_count) : _nodes(node_count) {}

Graph::Graph(std::istream& stream) {
    NodeId node_count{0}; stream >> node_count;
    Graph graph(node_count);
    NodeId from, to;
    while (stream >> from >> to) {
        graph.add_edge(from, to);
    }

    // std::move sorgt dafür, dass graph nicht kopiert wird
    *this = std::move(graph);
}

NodeId Graph::node_count() const {
    return _nodes.size();
}

std::span<NodeId const> Graph::out_neighbors(NodeId node) const {
    return _nodes.at(node).out_neighbors;
}

void Graph::add_edge(NodeId from, NodeId to) {
    _nodes.at(from).out_neighbors.push_back(to);
}
