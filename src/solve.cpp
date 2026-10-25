#include <iostream>
#include <fstream>
#include <optional>

#include "graph.hpp"
#include "topological_order.hpp"

int main(int argc, char const** argv) {
    // Prüfe, dass der Pfad zu der Graphdatei eigegeben wurde
    if (argc < 2) {
        std::cerr << "error: missing graph file\n";
        return -1;
    }

    // Öffne und lese die Graphdatei
    std::ifstream file{argv[1]};
    if (!file.is_open()) {
        std::cerr << "error: failed to open file " << argv[1] << '\n';
        return -1;
    }
    Graph graph{file};

    // Berechne eine topologische Ordnung
    std::optional<std::vector<NodeId>> order{topological_sort(graph)};
    if (!order) {
        std::cerr << "error: graph contained a cycle\n";
        return -1;
    }

    // Gebe die topologische Ordnung aus
    for (auto i : *order) {
        std::cout << i << '\n';
    }

    return 0;
}
