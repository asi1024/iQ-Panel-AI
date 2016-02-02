CXX=g++
CXXFLAGS=--std=c++11 -Wall -O2

all: judge ai

.PHONY: clean
clean:
	rm reactive.out ai.out

judge: reactive.out
reactive.out:
	$(CXX) $(CXXFLAGS) reactive.cpp -o reactive.out

# change following lines for your program
ai: ai.out
ai.out:
	$(CXX) $(CXXFLAGS) ai.cpp -o ai.out
