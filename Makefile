TARGET = hangman
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I/mingw64/include/SDL2 -Dmain=SDL_main
LDFLAGS = -L/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

SRC = main.cpp graphics.cpp functions.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del *.o *.exe
