CPPFLAGS := -I src
CXXFLAGS := -g -Wall -Wextra -Werror -std=c++20

CPPFILES := src/graph.cpp src/topological_order.cpp src/solve.cpp
HPPFILES := src/graph.hpp src/topological_order.hpp

build/topsort: $(CPPFILES) $(HPPFILES)
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(CPPFILES) -o $@

.PHONY: clean
clean:
	rm -rf build
