TARGET := cp
CFLAGS := -std=c++11

CC       = g++   -c  -fPIC
CXX   = g++   -g
LFLAGS   = -Wall

SOURCES  := $(wildcard src/*.cpp)
INCLUDES := $(wildcard inc/*.h)
OBJECTS  := $(SOURCES:.cpp=*.o)
rm       = rm -f


all:  $(TARGET)
$(TARGET): $(SOURCES) $(INCLUDES) 
	@$(CXX) $(CFLAGS) -o $(TARGET)  $(SOURCES)  -pthread  -I./

clean:
	@$(rm) $(TARGET) $(OBJECTS)
 
