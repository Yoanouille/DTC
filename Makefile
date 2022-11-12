CC=g++ --std=c++11 -Wall
INCL=-Iinclude
SFML=-lsfml-graphics -lsfml-window -lsfml-system
CCO=$(CC) $(INCL) -c $< -o $@
OBJ_DIR=@mkdir obj/ -p
OBJECTS=obj/Main.o obj/Menu.o obj/FirstScene.o obj/Scene.o
TARGET=main

all: $(TARGET)
	./$(TARGET)

memory: $(TARGET) $(OBJECTS)
	valgrind ./$(TARGET)

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(SFML)

obj/Main.o: src/Main.cpp include/Menu.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Menu.o: src/Menu.cpp include/Menu.hpp include/Scene.hpp include/FirstScene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Scene.o: src/Scene.cpp include/Scene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/FirstScene.o: src/FirstScene.cpp include/FirstScene.hpp include/Scene.hpp include/Menu.hpp
	$(OBJ_DIR)
	$(CCO)

clean:
	rm -rf obj/ $(TARGET)
