#include "parser.h"

void Parser::parse() {
    std::string line;

    // Skip first line of input; SPICE syntax spec
    getline(file, line);
    this->line_no++;

    // Allocate for use in loop
    Component* c;
    Source* s;

    std::smatch matches;

    while (!file.eof()) {
        // Get a line of input
        getline(file, line);

        // Keep track of type in regex list
        unsigned int t = 0;

        // Flag for regex match
        bool match = false;

        try {
            // Iterate through regex patterns; if match found, determine
            // which matched based on regex order in const vector
            for (auto reg: regexes) {
                if (regex_search(line, matches, reg)) {
                    switch (t) {
                        case EMPTY_LINE:
                        case COMMENT_LINE:
                            // std::cout << "Skipped" << std::endl;
                            break;
                        case R:
                        case L:
                        case C:
                        case D:
                        case M:
                            // std::cout << "Component!" << std::endl;
                            c = this->parse_line<Component>(matches, t);
                            this->components.push_back(c);

                            break;
                        case VDC:
                            // std::cout << "v\n";

                            s = this->parse_line<Source>(matches, t);
                            this->sources.push_back(s);

                            break;
                    }

                    // Once found a match, no need to search more
                    match = true;

                    break;
                }

                t++;
            }

            if (!match) {
                throw parser_error("Syntax error", this->line_no);
            }
        }

        catch (parser_error& e) {
            this->error = e;
            this->parsed = parser_state::error;
            break;
        }

        this->line_no++;
    }

    // If really at EOF, then file has been parsed
    if (file.eof())
        this->parsed = parser_state::parsed;
}

void Parser::print_components() {
    if (this->parsed == parser_state::parsed) {
        for (auto e: this->components) {
            std::cout << e->label << " " << e->n1 << " " << e->n2 << " " << std::endl;
        }
    }

    else
        std::cout << "The file has not been parsed successfully. Fix any issues and try again." << std::endl;
}

template<class T>
T* Parser::parse_line(const std::smatch matches, unsigned char t) {
    T* temp;

    // std::cout << matches[1] << " " << matches[5] << std::endl;

    try {
        if (t == VDC)
            temp = new T(matches[1], t, matches[3], matches[4], matches[5]);
        else if (t == M)
            temp = new T(matches[1], t, matches[3], matches[4], matches[5]);
        else
            temp = new T(matches[1], t, matches[3], matches[4], matches[5]);
    }

    catch (std::out_of_range& e) {
        temp = nullptr;
        throw parser_error("Value out of range. ", this->line_no);
    }

    return temp;
}

parser_error& Parser::get_error() {
    return this->error;
}
