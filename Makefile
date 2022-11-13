CC=g++ --std=c++11 -Wall
INCL=-Iinclude
SFML=-lsfml-graphics -lsfml-window -lsfml-system
CCO=$(CC) $(INCL) -c $< -o $@

OBJ_DIR=@mkdir obj -p
OBJECTS=obj/Main.o obj/Menu.o obj/FirstScene.o obj/Scene.o obj/MainScene.o obj/Piece.o obj/DomPiece.o

TEST_OBJ=obj/Test.o obj/Piece.o obj/DomPiece.o

TARGET=main

all: $(TARGET)
	./$(TARGET)

memory: $(TARGET) $(OBJECTS)
	valgrind ./$(TARGET)

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(SFML)

obj/Main.o: src/Main.cpp include/front/Menu.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Frontend Objects ====#
obj/Menu.o: src/front/Menu.cpp include/front/Menu.hpp include/front/Scene.hpp include/front/FirstScene.hpp include/front/MainScene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Scene.o: src/front/Scene.cpp include/front/Scene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/FirstScene.o: src/front/FirstScene.cpp include/front/FirstScene.hpp include/front/Scene.hpp include/front/Menu.hpp
	$(OBJ_DIR)
	$(CCO)

obj/MainScene.o: src/front/MainScene.cpp include/front/MainScene.hpp include/front/Scene.hpp include/front/Menu.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Backend Objects ====#
obj/Piece.o: src/back/Piece.cpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/DomPiece.o: src/back/DomPiece.cpp include/back/DomPiece.hpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Clean rule =====#
clean:
	rm -rf obj/ $(TARGET) $()

#==== Tests ====# 
test : testobj
	./test 

testobj : $(TEST_OBJ)
	$(CC) -o test $(TEST_OBJ)

obj/Test.o: src/Test.cpp include/back/Piece.hpp include/back/DomPiece.hpp
	$(OBJ_DIR)
	$(CCO)