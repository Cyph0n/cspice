# Todo

## Now

* Write a very simple SPICE syntax parser. Follow the spec from problem at the end of Chapter 1 of Najm's Circuit Simulation.
    * Create one Component type with different constructors for overloading... will be complex [x]
    * Instead of above, opted for Component class and Source class for simplicity [x]
    * Issue with lost values for n1, n2, etc. --- TODO

* Simulation engine --- PROBABLY NOT
    * Represent each node as an object (struct?). Stores pointer to each element connected to that node.
    * Store all nodes with sources connected in sources vector.
    * Store rest of nodes in general nodes vector.

    * For DC:
        1. Iterate through each source -> apply superposition; compute all node voltages assuming only
           that source is operational.
        2. Output node values.

    * For AC and Transient:
        * Do the same as for DC, but complete simulation at each time step. Output values of all nodes
          to temp file.


## Next

* Implement basic SPICE syntax parser. Two different possible approaches:
    1. Simple line-by-line parser. Use spaces as seperators. Detect keywords and node names using a simple lookup table.
    2. More advanced approach -> lexer and parser. Watch Compiler course.

* Write a REPL that allows further commands to be run (sim, plot, etc.)
    * Should allow for verification of design given spec
    * Should support dynamic insertion of new nodes and new components

* Plotting
    * GNU Plot

* SPICE coverage
    * Support for DC and AC (pulse, sin) sources
    * Support for R, L, C, D (?)
    * Support for large number of nodes

* Simulation engine
    * Engine should run on background thread (?)
    * Allow setting arbitrary simulation time
    * Allow real-time pause/resume of simulation

* Models
    * For R -> easy
    * For L and C -> diff equation builder and solver
    * For D -> exp. model

* Verification
    * User provides spec using simple syntax via REPL
    * Verifier runs simulation for some time and determines if design is correct
