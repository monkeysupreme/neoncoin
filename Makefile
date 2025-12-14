CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2
LDFLAGS = -lcryptopp

SRC = src/*.cpp
TARGET = neoncoin

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
