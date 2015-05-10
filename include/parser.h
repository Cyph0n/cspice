#ifndef parser
#define parser

#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <regex>

#include "components.h"

class parser_error : public std::exception {
    unsigned int line;
    std::string msg;
    std::string line_content;

public:
    // Default constructor - no message
    parser_error(): msg(""), line(0) {}

    parser_error(std::string msg, std::string line_content, unsigned int line):
    msg(msg), line_content(line_content), line(line) {
        print_error();
    }

    ~parser_error() {}

    unsigned int get_line() { return line; }

    void print_error() {
        std::cerr << "*** (PARSER ERROR) " << msg << " on line " << line << " -> [" << line_content << "]" << " ***\n";
    }
};

enum class parser_state {
    error,
    parsed,
    not_parsed
};

enum line_type {
    R,
    // L,
    // C,
    VDC,
    IDC,
    COMMENT_LINE,
    EMPTY_LINE,
    NONE
};

// Regex match class
class ComponentRegex
{
public:
    unsigned int type;
    std::regex reg;

    ComponentRegex(unsigned int type, std::regex reg): type(type), reg(reg) {}
};

class Parser {
    std::ifstream file;

    unsigned int line_no = 1;

    std::vector<Source> sources;
    std::vector<Component> comps;

    parser_state state = parser_state::not_parsed;

    // Default error
    parser_error error;

    // Track max node seen in file
    int max_node = -1;

    // Regexes for line parsing
    const std::vector<ComponentRegex> regexes = {
        ComponentRegex(R, std::regex(R"(^(R(\d+)) (\d+) (\d+) (\d+\.?\d+?)(\s*%.*)?$)", std::regex::icase)),
        // ComponentRegex(VDC, std::regex(R"(^(V(\d+)) (\d+) (\d+) (\d+\.?\d+?)(\s*%.*)?$)", std::regex::icase)),
        ComponentRegex(IDC, std::regex(R"(^(I(\d+)) (\d+) (\d+) (\d+\.?\d+?)(\s*%.*)?$)", std::regex::icase)),
        ComponentRegex(COMMENT_LINE, std::regex(R"(^%.*$)")),
        ComponentRegex(EMPTY_LINE, std::regex(R"(^[ \r\t]*$)"))
    };

public:
    Parser(const std::string& path);
    ~Parser();

    std::vector<Source>& get_sources();
    std::vector<Component>& get_components();

    bool is_parsed();
    unsigned int get_max_node();
    parser_error& get_error();
    void parse();
    void insert_line(const std::string&);
    bool match_line(const std::string&);

private:
    template<class T> void parse_line(const std::smatch&, std::vector<T>&, unsigned char);
};

#endif
