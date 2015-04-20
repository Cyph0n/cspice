#include <iostream>
#include <vector>
#include <string>

#include "parser.h"
// #include "simulator.h"

// struct Node1 {
//     int a;
//     string s;
// };

// class Node {
// public:
//     int a;
//     std::string s;

//     Node() {}
//     Node(int p1, std::string p2) { a = p1; s = p2; }
// };

int main(int argc, char *argv[]) {
    // cout << v[0] <<  " " << v.size() << endl;

    // Node n1; // Node on stack? value is stored at n1
    // n1.a = 10;
    // n1.s = "Assil";

    // std::cout << &n1 << std::endl;

    // std::unique_ptr<Node> p1 (new Node); // unique_ptr to a Node equiv. to Node*, so value stored on heap
    // // new allocates space on heap; not confined to local scope

    // p1->a = 10;
    // p1->s = "James";

    // std::cout << p1->s << std::endl;
    // std::cout << &p1 << std::endl;

    // // let's try moving p1's Node to another unique_ptr p2
    // std::unique_ptr<Node> p2 (std::move(p1));

    // std::cout << (p1 == nullptr) << std::endl; // true!
    // std::cout << p2->s << std::endl; // points to the same Node

    // Node n2(10, "james"); // new Node -> value stored on stack once more
    // n2.a = 15;

    // std::cout << n2.s << std::endl;
    // std::cout << n2.a << std::endl;
    // std::cout << &n2 << std::endl;

    // Node* n3 = new Node(10, "Jacks"); // and another one on the heap

    // std::cout << n3->s << std::endl;
    // std::cout << &n3 << std::endl;

    // Simulator testing
    // Component* e = new Component;

    // Component c (3, 1, 0, 200);


    // Parser *p = new Parser("test.txt");
    // p->parse();
    // delete p;
    Parser p ("test.txt");
    p.parse();

    p.print_components();

    return 0;
}
