BUILD_DIR := build
PROJECT_NAME := EP1

C_SOURCES := $(wildcard */*.cpp)
C_INCLUDES := -I. -Iinc
OBJECTS := $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.cpp=.o)))

C_FLAGS := $(C_INCLUDES) -O2 -Wall -Wextra -std=c++11

all: $(BUILD_DIR) $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	@echo "Creating executable"
	g++ -o $@ $^

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	g++ -c $< -o $@ $(C_FLAGS)
	@echo 

$(BUILD_DIR): 
	@echo "Creating build directory"
	@mkdir -p $@
	@echo 

run:
ifeq ($(OS),Windows_NT)
	@./$(PROJECT_NAME).exe
else
	@./$(PROJECT_NAME)
endif

clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR)
ifeq ($(OS),Windows_NT)
	rm $(PROJECT_NAME).exe
else
	rm $(PROJECT_NAME)
endif 


.PHONY: all clean run
