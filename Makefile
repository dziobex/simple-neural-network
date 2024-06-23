CXX = g++

CXXFLAGS = -std=c++17 -Wall -Iinclude -Iinclude/sdl -Iinclude/headers

LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

SRCS = $(wildcard src/*.cpp)

OBJS = $(SRCS:.cpp=.o)

EXEC = neuro.exe

.PHONY: clean all run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	del src\*.o $(EXEC)