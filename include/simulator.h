#ifndef simulator
#define simulator

#include <iostream>
#include <vector>

#include "parser.h"

/*
    2D matrix, max node.

    vector<vector<int>> v;

    first col = 1

    MNA STAMP:

    As you encounter el, add its Y to circuit[el.n1][el.n1] and circuit[el.n2][el.n2]
    then negate from ...[el.n1][el.n2] and ...[el.n2][el.n1]

    1. iterate through nodes. find els connected to node except sources.
    2. add all Ys of els -> store in mat[node][node].
    3. iter through all els. if el connected to other node excpet 0, sub that Y
       from mat[node][other]
        - if el floating on other side, raise except on el

*/

class Simulator {
    std::vector<std::vector<double>> circuit;
    std::vector<double> currents;

    bool _error = false;

public:
    Simulator(Parser& p);

    std::vector<double>& get_currents();
    std::vector<std::vector<double>>& get_circuit();

    bool error();
};

#endif
