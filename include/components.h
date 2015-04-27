#ifndef components
#define components

#include <vector>
#include <iostream>

class Component {
public:
    std::string label;

    // R, L, C, etc.
    int type;

    // Nodes
    int n1, n2;

    double value;

    // Location of component in file for later error reporting
    unsigned int line;

    // Default constructor
    Component() {}

    Component(std::string label, int type, int n1, int n2, double value, unsigned int line) {
        this->label = label;
        this->n1 = n1;
        this->n2 = n2;
        this->type = type;
        this->value = value;
        this->line = line;
    }

    Component(std::string label, int type, std::string n1, std::string n2, std::string value, unsigned int line):
    Component(label, type, std::stoi(n1, nullptr), std::stoi(n2, nullptr),
              std::stod(value, nullptr), line) {}

    // Clone another Component
    Component(const Component& c) {
        this->label = c.label;
        this->value = c.value;
        this->n1 = c.n1;
        this->n2 = c.n2;
        this->type = c.type;
        this->line = c.line;
    }

    // Copy another Component
    Component& operator=(const Component& rhs) {
        this->label = rhs.label;
        this->value = rhs.value;
        this->n1 = rhs.n1;
        this->n2 = rhs.n2;
        this->type = rhs.type;
        this->line = rhs.line;

        return *this;
    }

    ~Component() {
        // std::cout << "Gone!" << std::endl;
    }
};

class Source : public Component {
public:
    Source() {}

    Source(std::string label, int type, int n1, int n2, double value, unsigned int line):
    Component(label, type, n1, n2, value, line) {}

    Source(std::string label, int type, std::string n1, std::string n2, std::string value, unsigned int line) {
        Component(label, type, n1, n2, value, line);
    }

    Source(const Source& s) {
        this->label = s.label;
        this->value = s.value;
        this->n1 = s.n1;
        this->n2 = s.n2;
        this->type = s.type;
        this->line = s.line;
    }

    Source& operator=(const Source& rhs) {
        this->label = rhs.label;
        this->value = rhs.value;
        this->n1 = rhs.n1;
        this->n2 = rhs.n2;
        this->type = rhs.type;
        this->line = rhs.line;

        return *this;
    }
};

#endif
