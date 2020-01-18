CXX ?= g++

# path #
SRC_PATH = .
BUILD_PATH = build
BIN_PATH = ocl_run

# extensions #
SRC_EXT = cpp

# flags #
CXXFLAGS ?= -std=c++11
COMPILE_DEBUG_FLAGS = -g
COMPILE_RELEASE_FLAGS = -O3 -march=native
INCLUDES = -I. -I/usr/local/include
LIBS = -lOpenCL

SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJECTS:.o=.d)

.PHONY: default_target
default_target: debug

.PHONY: debug
debug: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_DEBUG_FLAGS)
debug: dirs
	@$(MAKE) all

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_RELEASE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))

.PHONY: clean
clean:
	@echo "Deleting executable"
	@$(RM) $(BIN_PATH)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)

# checks the executable to the output
.PHONY: all
all: $(BIN_PATH)

-include $(DEPS)

# Creation of the executable
$(BIN_PATH): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) $(LIBS) -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@