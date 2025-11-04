# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Executable name
TARGET = student_program

# Source files
SRCS = main.cpp GradeCalc.cpp Student.cpp StudentIO.cpp StudentSort.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Convenience targets to build with either container type
.PHONY: vector list

vector:
	$(MAKE) clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -DUSE_VECTOR" all

list:
	$(MAKE) clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -DUSE_LIST" all

