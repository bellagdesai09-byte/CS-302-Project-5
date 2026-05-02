# ============================================================
# CS 302 Project 5 Makefile
# Word Frequency Analyzer
# ============================================================
#
# Directory layout:
#   project_05/
#   ├── include/    <- Header files (.h)
#   ├── src/        <- Source files (.cpp)
#   ├── texts/      <- Text files for analysis
#   ├── build/      <- Compiled objects and executable
#   └── Makefile
#
# NOTE ON TEMPLATES:
#   HashTable.h and hashFunctions.h are header-only templates.
#   They do NOT appear in SRCS. The compiler sees them when
#   they are included by driver.cpp.
#
# TARGETS:
#   make        Build the executable
#   make run    Build and run
#   make debug  Rebuild with -g -O0 -fsanitize=address,undefined
#               for stack traces on segfaults and UB
#   make clean  Remove all build artifacts
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
DEBUGFLAGS = -g -O0 -fsanitize=address,undefined

SRC_DIR   = src
BUILD_DIR = build
TARGET    = project5

SRCS = $(SRC_DIR)/driver.cpp \
       $(SRC_DIR)/TextParser.cpp

OBJS       = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE = $(BUILD_DIR)/$(TARGET)

.PHONY: all clean run debug

all: $(EXECUTABLE)

# Rebuild with debug symbols and AddressSanitizer + UBSan.
# Use this when you hit a segfault, bad read, or suspect
# undefined behavior. Run the resulting binary normally;
# the sanitizers will print a stack trace on the first
# problem they detect.
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean all

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: $(EXECUTABLE)
	$(EXECUTABLE)
