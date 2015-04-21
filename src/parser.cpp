#include "parser.h"

void Parser::parse() {
    std::string line;

    // Skip first line of input; SPICE syntax spec
    getline(file, line);

    line_no++;

    while (!file.eof()) {
        // Get a line of input
        getline(file, line);

        Component* c;
        Source* s;

        std::smatch matches;

        // Keeps track of type in regex list
        unsigned int t = 0;

        // Catch any syntax errors
        try {
            // Iterate through regex patterns; if match found, determine
            // which matched based on regex order in const vector
            for (auto reg: regexes) {
                if (regex_search(line, matches, reg)) {
                    switch (t) {
                        case EMPTY_LINE:
                            std::cout << "empty\n";
                            break;
                        case R:
                        case L:
                        case C:
                        case D:
                        case M:
                            c = this->parse_line<Component>(matches, t);
                            this->components.push_back(c);

                            break;
                        case VDC:
                            std::cout << "v\n";

                            s = this->parse_line<Source>(matches, t);
                            this->sources.push_back(s);

                            break;
                        default:
                            std::cout << "None?\n";
                    }

                    // Once found a match, no need to search more
                    break;
                }

                else
                    throw parser_error();

                t++;
            }
        }

        catch (parser_error& e) {
            std::cout << "Syntax error on line " << line_no << "." << std::endl;
            break;
        }

        line_no++;
    }
}

void Parser::print_components() {
    for (auto c: this->components) {
        std::cout << c->label << " " << c->n1 << " " << c->n2 << " " << c->n3 << std::endl;
    }
}

template<class T>
T* Parser::parse_line(const std::smatch matches, unsigned char t) {
    T* temp;

    try {
        if (t == VDC)
            temp = new T(matches[1], t, matches[3], matches[4], matches[5]);
        else if (t == M)
            temp = new T(matches[1], t, matches[3], matches[4], matches[5]);
        else
            temp = new T(matches[1], t, matches[3], matches[4], matches[5]);
    }

    catch (std::out_of_range& e) {
        std::cout << "Value out of range on line " << line_no << std::endl;
        temp = nullptr;

        throw parser_error();
    }

    return temp;
}
