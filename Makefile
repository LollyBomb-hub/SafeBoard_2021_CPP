# Compiler variable
CXX := g++
# Sources variable
SOURCES := $(wildcard ./*.cpp)
# Target variable
TARGET := ./build/scan_util
TESTS_FOLDER := ./tests
GENERATE_TESTS := ./generate_tests.py
COUNT_OF_TESTS := 150
PROGRAM_RESULT := program_result.txt
CFLAGS := -O3 -Wall -Wextra -Wpedantic -Werror -std=c++17


linux_target:
	$(CXX) $(CFLAGS) -DLINUX $(SOURCES) -o $(TARGET)


macOS_target:
	$(CXX) $(CFLAGS) $(SOURCES) -o $(TARGET)


tests: $(SOURCES)
	rm -rf $(TESTS_FOLDER)/*
	$(GENERATE_TESTS) $(TESTS_FOLDER) $(COUNT_OF_TESTS)
	$(TARGET) $(TESTS_FOLDER) > $(PROGRAM_RESULT)
	cat $(PROGRAM_RESULT) true_results.txt


.PHONY: tests
