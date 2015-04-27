CC := g++
CFLAGS := -c -std=c++11
LINKER_OPTS :=

TARGET := bin/cspice
INCLUDE := -I include

BUILDDIR := build
SRCDIR := src

$(TARGET): parser.o simulator.o cspice.o
	@echo "Linking.."
	$(CC) $(LINKER_OPTS) $(BUILDDIR)/cspice.o $(BUILDDIR)/parser.o  $(BUILDDIR)/simulator.o -o $(TARGET)

	@./bin/cspice # Run the program

parser.o:
	@mkdir -p $(BUILDDIR)
	@echo "Building.."
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR)/parser.cpp -o $(BUILDDIR)/parser.o

simulator.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR)/simulator.cpp -o $(BUILDDIR)/simulator.o

cspice.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR)/cspice.cpp -o $(BUILDDIR)/cspice.o

clean:
	@echo "Cleaning.."
	@rm -rf $(BUILDDIR)
