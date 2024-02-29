CXX = g++-12
CXXFLAGS = -std=c++20 -Wall -g -MMD
SRC_DIR = src
BUILD_DIR = build
EXEC = caesar

# Find all source files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.cc)

# Generate a list of corresponding object files in the build directory
OBJECTS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SOURCES))

# Dependency files
DEPENDS = $(OBJECTS:.o=.d)

# Default target
all: $(EXEC)

# Linking object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling each source file into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPENDS)

.PHONY: clean 
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

# Create the build directory if it does not exist
$(shell mkdir -p $(BUILD_DIR))