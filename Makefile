CXX := g++
AR := ar
CXXFLAGS := -std=c++17 -Iinclude
LDFLAGS := 
SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)
LIB := libsumcheck.a

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: all test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -L. -lsumcheck -o test
	@echo "\n"
	./test

clean:
	rm -f $(OBJ) $(LIB) test