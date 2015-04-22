#include "parser.h"

void Parser::parse() {
    std::string line;

    // Skip first line of input; SPICE syntax spec
    getline(file, line);
    this->line_no++;

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
                            break;
                        case R:
                        case L:
                        case C:
                        case D:
                            this->parse_line<Component>(matches, this->components, t);
                            break;
                        case VDC:
                            this->parse_line<Source>(matches, this->sources, t);
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
            std::cout << e.label << " " << e.n1 << " " << e.n2 << " " << e.value << std::endl;
        }
    }

    else
        std::cout << "The file has not been parsed successfully. Fix any issues and try again." << std::endl;
}

template<class T>
void Parser::parse_line(const std::smatch& matches, std::vector<T>& v, unsigned char t) {
    T temp;

    try {
        if (t == VDC) {
            temp = T(matches[1], t, matches[3], matches[4], matches[5]);
        }

        else if (t == D)
            temp = T(matches[1], t, matches[3], matches[4], "0");

        else
            temp = T(matches[1], t, matches[3], matches[4], matches[5]);
    }

    catch (std::out_of_range& e) {
        throw parser_error("Value out of range", this->line_no);
    }

    catch (std::invalid_argument& e) {
        throw parser_error("Invalid value", this->line_no);
    }

    catch (std::exception& e) {
        throw parser_error("Unknown error", this->line_no);
    }

    v.push_back(temp);
}

parser_error& Parser::get_error() {
    return this->error;
}
