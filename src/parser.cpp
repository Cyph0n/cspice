#include "parser.h"

void Parser::parse() {
    std::string line;

    // Skip first line of input; SPICE syntax spec
    getline(file, line);

    while (!file.eof()) {
        // Get a line of input
        getline(file, line);

        // Iterate through regex patterns; if match found, determine
        // which matched based on regex order in const vector
        Component* c;

        unsigned char p = 0;

        for (auto reg: regexes) {
            if (regex_search(line, reg)) {
                switch (p) {
                    case EMPTY_LINE:
                        std::cout << "empty\n";
                        break;
                    case VDC:
                        std::cout << "v\n";
                        c = this->parse_line(line, p);
                        break;
                    case R:
                        std::cout << "r\n";
                        c = this->parse_line(line, p);
                        break;
                    case M:
                        std::cout << "M, baby\n";
                        c = this->parse_line(line, p);
                        break;
                    default:
                        std::cout << "None?\n";
                }

                this->components.push_back(c);

                // Once found a match, no need to search more
                break;
            }

            p++;
        }

    }
}

void Parser::print_components() {
    for (auto c: this->components) {
        std::cout << c->node1 << " " << c->node2 << std::endl;
    }
}

Component* Parser::parse_line(std::string line, unsigned char c) {
    if (c == R)
        return new Component(1, 1, 0, 30.45);
    else if (c == VDC)
        return new Component(5, 2, 3, 10.5);
    else if (c == M)
        return new Transistor(5, 2, 3, 1, 10.5);
}
