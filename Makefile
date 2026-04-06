CXX     = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

# All .cpp files we need to compile
SRCS = main.cpp \
       utils/IdGenerator.cpp

TARGET = uber_clone

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
