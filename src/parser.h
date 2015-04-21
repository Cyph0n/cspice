#ifndef parser
#define parser

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <regex>

// C libs
#include <cctype>
#include <cstdlib>

class parser_error : public std::exception {
public:
    parser_error() {}
    ~parser_error() {}
};

template<typename T>
void clear_vector(std::vector<T*>& v) {
    for (auto e: v)
        delete e;

    v.clear();
}

enum type {
    R,
    L,
    C,
    D,
    M,
    VDC,
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

        // Empty line; what is the problem?
        std::regex(R"(^[\r\t]*\n$)")
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
        std::cout << "Destroyed!" << std::endl;

        // Close file
        file.close();

        // Clear up vectors
        clear_vector<Component>(components);
        clear_vector<Source>(sources);
    }

    void parse();
    void print_components();

private:
    template<class T>
    T* parse_line(const std::smatch, unsigned char);
    // Component* parse_component(std::string line, std::smatch matches, unsigned char c);
    // Source* parse_source(std::string line, std::smatch matches, unsigned char c);
};

#endif
