NAME = Noted
CXX = g++
CXXFLAGS = -std=c++23 -Ofast -Wall
SOURCES_DIR = sources
BUILD_DIR = build
LIBS = -I./headers
SOURCES = $(wildcard $(SOURCES_DIR)/*.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

.PHONY: all

all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): $(OBJECTS)
	@$(CXX) -o $@ $^ $(LIBS)

$(OBJECTS): $(SOURCES_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBS)

.PHONY: clean

clean:
	@-rm $(SOURCES_DIR)/*.o $(BUILD_DIR)/*
