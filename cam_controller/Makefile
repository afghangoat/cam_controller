CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11 -I./include

# OpenGL and GLEW libraries
LDFLAGS = -lGL -lGLU -lglut -lGLEW

TARGET = main
SRCS = $(wildcard src/*.cpp)
#src/main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS) $(TARGET)