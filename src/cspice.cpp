#include <iostream>

#include "parser.h"
#include "simulator.h"

void print_help() {
    std::cout << "Quit: q or quit\n";
    std::cout << "View loaded file: which\n";
    std::cout << "Run simulation: run\n";
    std::cout << "Help: help or usage\n";
}

void run_repl(std::string& file) {
    // REPL loop
    std::cout << "CSpice - Interative SPICE Simulator\n";

    // Keep one parser instance; will not change through session
    Parser p (file);
    p.parse();

    if (!p.is_parsed())
        return;

    std::cout << file << " parsed successfully!\n";

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
                std::cout << file << "\n";
            else if (in == "run") {
                Simulator s;
                s.simulate(p);

                std::cout << "Simulation complete!\n";
            }

            std::cout << prompt;
        }
    }
}

int main(int argc, char** argv) {
    std::string file;

    if (argc == 2) {
        file = argv[1];
        run_repl(file);
    }

    else
        std::cout << "Please specify input SPICE netlist.\n";

    return 0;
}
