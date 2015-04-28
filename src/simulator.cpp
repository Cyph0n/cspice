#include "simulator.h"

Simulator::Simulator(Parser& p) {
    if (p.is_parsed()) {
        int i, j;

        unsigned int max_node = p.get_max_node();

        auto sources = p.get_sources();
        auto comps = p.get_components();

        // Init current vector
        for (i = 0; i <= max_node; i++)
            this->currents.push_back(0);

        std::cout << sources.size() << std::endl;

        // Add currents at n1 = i to currents[i] and n2 = j -ve
        for (auto s: sources) {
            if (s.type == IDC) {
                this->currents[s.n1] += s.value;
                this->currents[s.n2] -= s.value;
            }
        }

        // Init circuit vector
        for (i = 0; i <= max_node; i++) {
            std::vector<double> v (max_node+1);
            this->circuit.push_back(v);
        }

        try {
            // Iterate over components, placing them in appropriate location in circuit
            // (i, i) and (j, j) += Y -> minus for opp pair
            for (auto c: comps) {
                this->circuit[c.n1][c.n1] += 1/c.value;
                this->circuit[c.n2][c.n2] += 1/c.value;
                this->circuit[c.n1][c.n2] -= 1/c.value;
                this->circuit[c.n2][c.n1] -= 1/c.value;
            }
        }

        catch (parser_error& e) {
            this->_error = true;
            exit(0);
        }
    }
}

std::vector<double>& Simulator::get_currents() {
    return this->currents;
}

std::vector<std::vector<double>>& Simulator::get_circuit() {
    return this->circuit;
}

bool Simulator::error() {
    return this->_error;
}
