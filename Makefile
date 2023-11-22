CXX = g++
CXXFLAGS = -Wall -pedantic -Wextra -std=c++17

SRCS = $(wildcard src/*.cpp)
TEST_SRCS = $(wildcard tests/*.cpp)

OBJS = $(patsubst src/%.cpp,build/%.o,$(SRCS))
TEST_OBJS = $(patsubst tests/%.cpp,debug/%.o,$(TEST_SRCS))

TARGET = main
TEST_TARGET = debug/test

all: compile debug

run: compile
	./$(TARGET)

test: debug
	./$(TEST_TARGET)

compile: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

debug: $(filter-out build/main.o, $(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $^

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug/%.o: tests/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf main build/ debug/ 2>/dev/null

.DEFAULT_GOAL := compile
.PHONY: all run test compile debug clean