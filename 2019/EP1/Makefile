BUILD_DIR := build
PROJECT_NAME := EP1

C_SOURCES := $(wildcard *.cpp)
H_SOURCES := $(wildcard *.h)
OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(C_SOURCES))

C_FLAGS := -Wall -Wextra -std=c++11

all: $(BUILD_DIR) $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	@echo "Creating executable"
	g++ -o $@ $^

$(BUILD_DIR)/%.o: %.cpp %.h
	@echo "Compiling $<..."
	g++ -c $< -o $@ $(C_FLAGS)
	@echo " "

$(BUILD_DIR)/main.o: main.cpp $(H_SOURCES)
	@echo "Compiling $<..."
	g++ -c $< -o $@ $(C_FLAGS)
	@echo " "

$(BUILD_DIR): 
	@echo "Creating build directory"
	@mkdir -p $@
	@echo " "

run:
ifeq ($(OS),Windows_NT)
	@./$(PROJECT_NAME).exe
else
	@./$(PROJECT_NAME)
endif

clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR)
