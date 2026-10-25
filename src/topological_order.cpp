#include "topological_order.hpp"

// Status von einem Knoten.
//
// - VisitState::PENDING: der Knoten wurde noch nicht durchlaufen.
// - VisitState::STARTED: wir befinden uns in einer DFS-Arboreszenz,
// die den Knoten bereits enthält.
// - VisitState::FINISHED: eine DFS-Arboreszenz, die diesen Knoten enthält,
// wurde schon geordnet.
enum class VisitState : uint8_t {
    PENDING = 0,
    STARTED,
    FINISHED,
};

// Der Zustand vom Algorithmus. next_index ist dienächsten Nummer in
// n-1, ..., 0, die einen Knoten in der topologische Ordnung bekommen wird.
// order speichert der schon berechnete Teil der topologischen Ordnung und
// visit_status den Status von jedem Knoten.

struct State {
    Graph const& graph;
    size_t next_index;
    std::vector<NodeId> order;
    std::vector<VisitState> visit_status;
};

// Führt DFS von dem Knoten node aus durch, findet eine topologische Ordnung
// von der erhaltenen DFS-Arboreszenz und speichert diese in state.order.
// Dabei werden die Knoten soweit rechts wie möglich in state.order gespeichert.
// Gibt zurück, ob der Teilgraph, der von den Knoten der DFS-Arboreszenz
// erzeugt wird, kreisfrei ist.
static bool visit(NodeId node, State& state);

std::optional<std::vector<NodeId>> topological_sort(Graph const& graph) {
    State state{
        graph,                                          // graph
        graph.node_count() - 1,                         // next_index
        std::vector<NodeId>(graph.node_count()),        // order
        std::vector<VisitState>(graph.node_count()),    // visit_status
    };

    for (NodeId i = 0; i < graph.node_count(); i++) {
        // visit hat die Eigenschaft, dass wenn w von v aus erreichbar ist,
        // die von visit(v) berechnetete topologische Ordnung in visit(w)
        // benutzt wird.
        // Wenn visit einen Kreis findet, gibt es keine topologische Ordnung.
        if (!visit(i, state)) return std::nullopt;
    }

    return state.order;
}

static bool visit(NodeId node, State& state) {
    VisitState& vs = state.visit_status.at(node);

    switch (vs) {
        case VisitState::STARTED:
            // node gibt es schon in der aktuellen DFS-Arboreszenz,
            // also haben wir einen Kreis gefunden.
            return false;
        case VisitState::FINISHED:
            // node ist Teil einer schon berechnetet topologischen Ordnung,
            // also ersparen wir uns die Arbeit.
            return true;
        case VisitState::PENDING:
            // Dieser knoten wurde noch nicht besucht, also tun wir das jetzt.
            break;
    }

    vs = VisitState::STARTED;

    // DFS
    for (NodeId i : state.graph.out_neighbors(node)) {
        // Falls ein Kreis gefundet wurde, gib es sofort weiter.
        if (!visit(i, state)) return false;
    }

    // Speichere node in der topologischen Ordnung.
    state.order.at(state.next_index) = node;
    state.next_index--;

    vs = VisitState::FINISHED;

    return true;
}
