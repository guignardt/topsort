#pragma once

#include <vector>
#include <optional>

#include "graph.hpp"

// Berechnet eine topologische Ordnung und gibt die zurück. Wenn graph einen
// Kreis enthält, gibt std::nullopt zurück.
std::optional<std::vector<NodeId>> topological_sort(Graph const& graph);
