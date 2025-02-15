CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = tower_defense

SRCS = main.cpp slow_tower.cpp base_tower.cpp aoe_tower.cpp critter.cpp tower.cpp CritterGroupGenerator.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)