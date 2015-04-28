#include <iostream>

#include "parser.h"
#include "simulator.h"

void print_help() {
    std::cout << "Quit: q or quit" << std::endl;
    std::cout << "Change input file: file <path_to_file>" << std::endl;
    std::cout << "View loaded file: which" << std::endl;
    std::cout << "Simulate file: simulate" << std::endl;
    std::cout << "Help: help or usage" << std::endl;
}

void run_repl(std::string& file) {
    // REPL loop
    std::cout << "CSpice - Interative SPICE Simulator" << std::endl;

    std::string in;
    const std::string prompt = "~> ";

    std::cout << prompt;

    while (true) {
        if (std::cin >> in) {
            if (in == "quit" || in == "q")
                break;
            else if (in == "help" || in == "usage")
                print_help();
            else if (in == "which")
                std::cout << file << std::endl;
            else if (in == "file") {
                // Update file
                std::string new_file;
                std::cin >> new_file;
                file = new_file;

                std::cout << "File is now " << file << std::endl;
            }

            std::cout << prompt;
        }
    }
}

int main(int argc, char** argv) {
    // Two options: REPL or single simulation
    std::string file;

    // Single
    if (argc == 2) {
        file = argv[1];
        run_repl(file);
    }

    else
        std::cout << "Please specify input SPICE netlist." << std::endl;

    // Parser p ("test.txt");
    // p.parse();

    // std::cout << "Parsed successfully? " << p.is_parsed() << std::endl;

    // parser_error e = p.get_error();

    // Simulator s (p);

    // // Testing simulator
    // int i = 0;

    // if (!s.error()) {
    //     std::cout << "Currents:" << std::endl;

    //     for (auto c: s.get_currents()) {
    //         std::cout << "I" << i << " = " << c << std::endl;
    //         i++;
    //     }

    //     std::cout << "Y matrix" << std::endl;

    //     for (auto v: s.get_circuit()) {
    //         for (auto e: v)
    //             std::cout << e << " ";

    //         std::cout << std::endl;
    //     }
    // }

    return 0;
}
