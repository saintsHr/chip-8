# ====================================================
# Source and object files
# ====================================================
SRC := $(shell find src -name "*.cpp")
OBJ := $(patsubst src/%.cpp,build/%.o,$(SRC))

# ====================================================
# Compiler settings
# ====================================================
CXX := g++
DEPFLAGS := -MMD -MP
CXXFLAGS := -Iinclude -Wall -Wextra $(DEPFLAGS)
LDFLAGS :=

# ====================================================
# Target executable
# ====================================================
TARGET := chip-8

# ====================================================
# Phony targets
# ====================================================
.PHONY: all clean

# ====================================================
# Default target: build the executable
# ====================================================
all: bin/$(TARGET)

bin/$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# ====================================================
# Compile source files into object files
# ====================================================
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ====================================================
# Include dependency files for automatic header tracking
# ====================================================
-include $(OBJ:.o=.d)

# ====================================================
# Clean build artifacts
# ====================================================
clean:
	rm -rf build bin
