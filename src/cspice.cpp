#include <iostream>

#include "parser.h"
#include "simulator.h"

int main(int argc, char *argv[]) {
    Parser p ("test.txt");
    p.parse();

    std::cout << "Parsed successfully? " << p.is_parsed() << std::endl;

    parser_error e = p.get_error();

    std::cout << "Error on line: " << e.get_line() << std::endl;

    Simulator s (p);

    return 0;
}
