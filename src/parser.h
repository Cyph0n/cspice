#ifndef parser
#define parser

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <regex>

class parser_error : public std::exception {
    unsigned int line;
    std::string msg;

public:
    parser_error() {
        this->msg = "";
        this->line = 0;
    }

    parser_error(std::string msg, unsigned int line) {
        this->msg = msg;
        this->line = line;

        print_error();
    }

    ~parser_error() {}

    unsigned int get_line() { return line; }

    void print_error() {
        std::cout << "[Line " << line << "] -> " << msg << std::endl;
    }
};

template<typename T>
void clear_vector(std::vector<T*>& v) {
    for (auto e: v)
        delete e;

    v.clear();
}

enum class parser_state {
    error,
    parsed,
    not_parsed
};

enum type {
    R,
    L,
    C,
    D,
    M,
    VDC,
    COMMENT_LINE,
    EMPTY_LINE,
    NONE
};

class Component {
public:
    std::string label;

    // R, L, C, etc.
    int type;

    // Nodes; 3rd for M
    int n1, n2, n3;

    double value;

    // R, C, L, D, M
    Component(std::string label, int type, int n1, int n2, double value) {
        this->label = label;
        this->n1 = n1;
        this->n2 = n2;
        this->type = type;

        // Set sane defaults for value and n3
        if (type != M) {
            this->value = value;
            this->n3 = -1;
        }

        else {
            this->value = -1;
            this->n3 = (int)value;
        }
    }

    // Proxy constructor for direct calling
    Component(std::string label, int type, std::string n1, std::string n2, std::string value) {
        Component(label, type, std::stoi(n1, nullptr), std::stoi(n2, nullptr),
                  std::stod(value, nullptr));
    }
};

class Source : public Component {
public:
    Source(std::string label, int type, int n1, int n2, double value):
    Component(label, type, n1, n2, value) {}

    Source(std::string label, int type, std::string n1, std::string n2, std::string value):
    Component(label, type, n1, n2, value) {}
};

class Parser {
    std::vector<Component*> components;
    std::vector<Source*> sources;

    std::ifstream file;

    unsigned int line_no = 1;

    parser_state parsed = parser_state::not_parsed;

    // Default error
    parser_error error;

    // Regexes
    const std::vector<const std::regex> regexes = {
        // Resistor, inductor, capacitor - split to simplify identification in loop
        std::regex(R"(^(R(\d+)) (\d+) (\d+) (\d+\.?\d+?)$)", std::regex::icase),
        std::regex(R"(^(L(\d+)) (\d+) (\d+) (\d+\.?\d+?)$)", std::regex::icase),
        std::regex(R"(^(C(\d+)) (\d+) (\d+) (\d+\.?\d+?)$)", std::regex::icase),

        // Diode
        std::regex(R"(^(D(\d+)) (\d+) (\d+)$)", std::regex::icase),

        // Transistor
        std::regex(R"(^(M(\d+)) (\d+) (\d+) (\d+)$)", std::regex::icase),

        // DC voltage source
        std::regex(R"(^(V(\d+)) (\d+) (\d+) (\d+\.?\d+?)$)", std::regex::icase),

        // Comment line
        std::regex(R"(^%.*$)"),

        // Empty line
        std::regex(R"(^[ \r\t]*$)")
    };

public:
    Parser(const std::string path) {
        // Path must be relative to running process directory!
        file.open(path);

        if (!file.is_open()) {
            std::cout << "File does not exist.\n";
            exit(0);
        }
    }

    ~Parser() {
        // std::cout << "Destroyed!" << std::endl;

        // Close file
        file.close();

        // Clear up vectors
        clear_vector<Component>(components);
        clear_vector<Source>(sources);
    }

    bool is_parsed() { return parsed == parser_state::parsed; }

    parser_error& get_error();

    void parse();
    void print_components();

private:
    template<class T> T* parse_line(const std::smatch, unsigned char);
};

#endif
