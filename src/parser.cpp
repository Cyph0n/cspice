#include "parser.h"

Parser::Parser(const std::string& path) {
    // Path must be relative to running process directory!
    file.open(path);

    if (!file.is_open()) {
        std::cout << "File does not exist.\n";
    }
}

Parser::~Parser() {
    // Close file
    file.close();
}

bool Parser::is_parsed() {
    return this->state == parser_state::parsed;
}

parser_error& Parser::get_error() {
    return this->error;
}

unsigned int Parser::get_max_node() {
    return this->max_node;
}

std::vector<Source>& Parser::get_sources() {
    return this->sources;
}

std::vector<Component>& Parser::get_components() {
    return this->comps;
}

void Parser::parse() {
    std::string line;

    // Skip first line of input; SPICE syntax spec
    getline(file, line);
    this->line_no++;

    std::smatch matches;

    // Track highest node in file to determine matrix size
    int max_node = -1;

    while (!file.eof()) {
        // Get a line of input
        getline(file, line);

        // Flag for regex match
        bool match = false;

        try {
            // Check for line match
            match = this->match_line(line);

            // // Iterate through regex patterns; if match found, determine
            // // which component matched
            // for (auto r: this->regexes) {
            //     if (regex_search(line, matches, r.reg)) {
            //         switch (r.type) {
            //             case EMPTY_LINE: case COMMENT_LINE:
            //                 break;
            //             case R:
            //                 this->parse_line<Component>(matches, this->comps, r.type, &max_node);
            //                 break;
            //             case VDC: case IDC:
            //                 this->parse_line<Source>(matches, this->sources, r.type, &max_node);
            //                 break;
            //         }

            //         // Once found a match, no need to search more
            //         match = true;

            //         break;
            //     }
            //}

            if (!match) {
                throw parser_error("Syntax error", line, this->line_no);
            }
        }

        catch (parser_error& e) {
            this->error = e;
            this->state = parser_state::error;
            break;
        }

        this->line_no++;
    }

    // If really at EOF, then file has been parsed
    if (file.eof()) {
        this->state = parser_state::parsed;
    }
}

void Parser::insert_line(const std::string& line) {
    try {
        bool match = this->match_line(line);

        if (match)
            this->line_no++;
        else
            throw parser_error("Syntax error", line, -1);
    }

    catch (parser_error& e) {
    }
}

bool Parser::match_line(const std::string& line) {
    std::smatch matches;

    bool match = false;

    // Iterate through regex patterns; if match found, determine
    // which component matched
    for (auto r: this->regexes) {
        if (regex_search(line, matches, r.reg)) {
            switch (r.type) {
                case EMPTY_LINE: case COMMENT_LINE:
                    break;
                case R:
                    this->parse_line<Component>(matches, this->comps, r.type);
                    break;
                case VDC: case IDC:
                    this->parse_line<Source>(matches, this->sources, r.type);
                    break;
            }

            // Once found a match, no need to search more
            match = true;

            break;
        }
    }

    return match;
}

template<class T>
void Parser::parse_line(const std::smatch& matches, std::vector<T>& v, unsigned char t) {
    T temp;

    try {
        if (t == VDC || t == IDC) {
            temp = T(matches[1], t, matches[3], matches[4], matches[5], this->line_no);
        }

        else {
            temp = T(matches[1], t, matches[3], matches[4], matches[5], this->line_no);

            // Track max_node
            if (temp.n1 > this->max_node || temp.n2 > this->max_node) {
                if (temp.n1 > temp.n2)
                    this->max_node = temp.n1;
                else
                    this->max_node = temp.n2;
            }
        }
    }

    catch (std::out_of_range& e) {
        throw parser_error("Value out of range", matches[0], this->line_no);
    }

    catch (std::invalid_argument& e) {
        throw parser_error("Invalid value", matches[0], this->line_no);
    }

    catch (std::exception& e) {
        throw parser_error("Unknown error", matches[0], this->line_no);
    }

    // Some other possible errors
    if (temp.n1 == temp.n2)
        throw parser_error("Nodes must be different", matches[0], this->line_no);

    // Resistor value must be > 0
    if (temp.value <= 0 && t == R)
        throw parser_error("Component value must be > 0", matches[0], this->line_no);

    v.push_back(temp);
}
