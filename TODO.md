# Todo

## Now

* Write a very simple SPICE syntax parser. Follow the spec from problem at the end of Chapter 1 of Najm's Circuit Simulation.
    * Create one Component type with different constructors for overloading... will be complex [x]
    * Instead of above, opted for Component class and Source class for simplicity [x]
    * Issue with lost values for n1, n2, etc. [x]
        - Problem was T* temp () in parse_line was a *stack-allocated* pointer! As soon as it left the scope, it was discarded..
    * Limit to two-terminal devices
    * Determine max node? [x]
    * Check for invalid components [x]
        * Connected to same node [x]
        * Floating component
    * regex vector -> ComponentRegex [x]
    * Move matrix building to simulator.h [x]
    * Write everything in header files (NO -- compile times increase significantly)
    * Put components in separate header file [x]
    * Add line number to component for further error reporting in Simulator [x]
    * Transform all V sources to I sources [later]
    * Add all I sources to currents vector
    * Implement Gaussian elimination solver for circuit matrix

* Simulation engine
    * Given sources and components, construct circuit matrix (Y matrix)
        - Yv = I
        - for VDC, Norton that baby
    * Once matrix constructed, do simple Gaussian elimination


## Next

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
