# Makefile for compiling minesweeper_solve.cpp

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -I libraries/armadillo-14.2.2/include -I libraries/SFML-2.6.2/include

# Linker flags
LDFLAGS = -L libraries/SFML-2.6.2/lib -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = minesweeper_solver

# Source files
SRCS = gui.cpp minesweeper_solve.cpp minesweeper_class.cpp arma_helper.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# # Add a new target for the SFML application
# SFML_APP = sfml-app

# # Source files for the SFML application
# SFML_SRCS = gui.cpp minesweeper_solve.cpp minesweeper_class.cpp arma_helper.cpp

# # Object files for the SFML application
# SFML_OBJS = $(SFML_SRCS:.cpp=.o)

# # Include and library paths for SFML
# SFML_INCLUDES = -I armadillo-14.2.2/armadillo-14.2.2/include -I SFML-2.6.2/include
# SFML_LIBS = -L SFML-2.6.2/lib -lsfml-graphics -lsfml-window -lsfml-system

# # Target for the SFML application
# $(SFML_APP): $(SFML_OBJS)
# 	$(CXX) $(SFML_OBJS) -o $(SFML_APP) $(SFML_LIBS) $(LDFLAGS)

# # Compile source files for the SFML application
# %.o: %.cpp
# 	$(CXX) -c $< -o $@ $(SFML_INCLUDES)
