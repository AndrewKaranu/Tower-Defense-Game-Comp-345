CXX = g++
CXXFLAGS = -std=c++11 -Wall -I. # Added -I. to include current directory
TARGET = as1_driver # Changed target name

SRCS = as1_driver.cpp slow_tower.cpp base_tower.cpp aoe_tower.cpp critter.cpp CritterGroupGenerator.cpp map.cpp tower.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)