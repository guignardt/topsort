#pragma once

#include <cstdint>
#include <vector>
#include <span>
#include <istream>

// Unsigned Integer Typ für Knoten IDs und Anzahlen Knoten.
using NodeId = std::uint32_t;

// Eine Klasse, die gerichtete Graphen darstellt. Sie erlaubt effizientes
// Hinzufügen von Kanten und Abfragen von Nachbarknoten entlang ausgehende
// Kanten eines bestimmten Knotens.
//
// Die Knoten sind mit NodeIds 0, ..., n-1 identifiziert.
class Graph {
public:
    // Konstruiert einen Graphen mit node_count Knoten und keine Kanten.
    Graph(NodeId node_count);

    // Konstruiert einen Graphen aus einem Stream, aus dem Zahlen lesen werden
    // können. Die erste Zahl ist die Anzahl Knoten. Dann werden sukzessiv Paare
    // x, y von Knoten IDs eingelesen, und für jedes wird eine Kante x -> y
    // gebildet.
    Graph(std::istream& stream);

    // Gibt die Anzahl Knoten zurück. Laufzeit is O(1).
    NodeId node_count() const;

    // Gibt eine Liste der Nachbarknoten von dem Knoten mit ID node entlang
    // ausgehende Kanten. Laufzeit is O(1).
    std::span<NodeId const> out_neighbors(NodeId node) const;

    // Fügt eine Kante from -> to hinzu. Laufzeit in O(1) amortisiert,
    // O(Grad von from) Worst-Case.
    void add_edge(NodeId from, NodeId to);

private:
    // Ein einzelner Knoten.
    struct Node {
        // Die Liste der Nachbarknoten entlang ausgehende Kanten.
        std::vector<NodeId> out_neighbors;
    };

    // Die Liste aller Knoten.
    std::vector<Node> _nodes;
};
