#include "simulator.h"

Simulator::Simulator(Parser& p) {
    if (p.state == parser_state::parsed) {
        int i, j;

        unsigned int max_node = p.max_node;

        // Init circuit vector
        for (i = 0; i <= max_node; i++) {
            std::vector<double> v (max_node+1);
            this->circuit.push_back(v);
        }

        try {
            // Iterate over components, placing them in appropriate location in circuit
            // (i, i) and (j, j) += Y -> minus for opp pair
            for (auto c: p.comps) {
                this->circuit[c.n1][c.n1] += 1/c.value;
                this->circuit[c.n2][c.n2] += 1/c.value;
                this->circuit[c.n1][c.n2] -= 1/c.value;
                this->circuit[c.n2][c.n1] -= 1/c.value;
            }
        }

        catch (parser_error& e) {
            exit(0);
        }

        std::cout << "Circuit!" << std::endl;

        // Print circuit
        for (i = 0; i < this->circuit.size(); i++) {
            for (j = 0; j < this->circuit[0].size(); j++)
                std::cout << this->circuit[i][j] << " ";

            std::cout << std::endl;
        }
    }
}
