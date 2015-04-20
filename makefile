CC := g++
CFLAGS := -c -std=c++11

TARGET := bin/cspice
# INCLUDE := -I include

BUILDDIR := build

$(TARGET): cspice.o parser.o
	@echo "Linking.."
	$(CC) $(BUILDDIR)/cspice.o $(BUILDDIR)/parser.o -o $(TARGET)

	@./bin/cspice # Run the program

parser.o:
	$(CC) $(CFLAGS) $(INCLUDE) src/parser.cpp -o build/parser.o

cspice.o:
	@mkdir -p $(BUILDDIR)
	@echo "Building.."
	@# $(CC) $(CFLAGS) $(INCLUDE) src/cspice.cpp -o build/cspice.o
	$(CC) $(CFLAGS) src/cspice.cpp -o build/cspice.o

clean:
	@echo "Cleaning.."
	@rm -rf $(BUILDDIR)
