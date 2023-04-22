all: bin/mps
	@echo -n ""

bin/mps: src/main.cpp
	g++ -O2 $< -o $@

clean:
	rm -rf *.o mps
