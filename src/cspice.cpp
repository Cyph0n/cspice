#include <iostream>
#include <vector>
#include <string>

#include "parser.h"
// #include "simulator.h"

int main(int argc, char *argv[]) {
    Parser p ("test.txt");
    p.parse();

    p.print_components();

    std::cout << p.is_parsed() << std::endl;

    parser_error e = p.get_error();

    std::cout << e.get_line() << std::endl;

    return 0;
}
