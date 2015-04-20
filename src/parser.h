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
    parser_error() { std::cout << "Dude!\n"; }
    ~parser_error() {}
};

enum component_type {
    R,
    C,
    L,
    M,
    VDC,
    EMPTY_LINE,
    NONE
};

class Component {
public:
    int label, node1, node2;
    double value;

    Component(int label, int node1, int node2, double value) {
        this->label = label;
        this->node1 = node1;
        this->node2 = node2;
        this->value = value;
    }
};

class Transistor : public Component {
public:
    int node3;

    Transistor(int label, int node1, int node2, int node3, double value)
    : Component(label, node1, node2, value) {
        this->node3 = node3;
    }
};

class Parser {
    // std::vector<Component*> two_terminal;
    // std::vector<Transistor*> three_terminal;
    // std::vector<Source*> sources;
    std::vector<Component*> components;
    std::ifstream file;

    // Regexes
    const std::vector<const std::regex> regexes = {
        std::regex("^R", std::regex::icase),
        std::regex("^C", std::regex::icase),
        std::regex("^L", std::regex::icase),
        std::regex("^M", std::regex::icase),
        std::regex("^V", std::regex::icase),
        std::regex(R"(^[ \r\t]*\n$)")
    };

public:
    Parser(const std::string path) {
        // Path must be relative to running process directory!
        file.open(path);

        if (!file.is_open()) {
            std::cout << "Invalid file.\n";
            exit(0);
        }
    }

    ~Parser() {
        // std::cout << "Destroyed!" << std::endl;

        // Free each and every component
        for (auto c: components)
            delete c;

        // Shrink vector size to 0
        components.clear();

        // Close file
        file.close();
    }

    void parse();
    void print_components();

private:
    Component* parse_line(std::string line, unsigned char c);
};

#endif
