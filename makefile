CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRC = main.cpp Graph.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean