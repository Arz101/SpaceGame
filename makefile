CXX = clang++

CXXFLAGS = -std=c++17 -Wall -fexceptions -g -Iinclude -Iinclude/ManagerIncludes -I/usr/local/include/SDL2 -I/usr/local/Cellar/sdl2_image/2.8.4/include/SDL2 -I/usr/local/Cellar/sdl2_ttf/2.24.0/include
LIBS = -L/usr/local/Cellar/sdl2/2.30.11/lib -L/usr/local/Cellar/sdl2_image/2.8.4/lib -L/usr/local/Cellar/sdl2_ttf/2.24.0/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

SRC = main.cpp $(wildcard src/*.cpp) $(wildcard src/components/*.cpp) $(wildcard src/Entities/*.cpp) $(wildcard src/components/ManagerComponents/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))  

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
