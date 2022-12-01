CC=g++ --std=c++11 -Wall
INCL=-Iinclude
SFML=-lsfml-graphics -lsfml-window -lsfml-system
CCO=$(CC) $(INCL) -c $< -o $@

OBJ_DIR=@mkdir obj -p
OBJECTS=obj/Main.o obj/AssetsLoader.o obj/Button.o obj/TextField.o obj/App.o  obj/Scene.o obj/MainMenu.o obj/PlayerSettingsScene.o obj/MainScene.o obj/PieceDisplayer.o obj/TraxPieceDisplayer.o obj/DomPieceDisplayer.o obj/Piece.o obj/DomPiece.o obj/TraxPiece.o obj/Player.o obj/Game.o obj/Trax.o obj/Sack.o obj/Domino.o obj/Controller.o

TEST_OBJ=obj/Test.o obj/Piece.o obj/DomPiece.o obj/TraxPiece.o obj/Sack.o obj/Game.o obj/Trax.o obj/Player.o

TARGET=main
TTARGET=test

all: $(TARGET)
	./$(TARGET)

memory: $(TARGET) $(OBJECTS)
	valgrind ./$(TARGET)

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(SFML)

obj/Main.o: src/Main.cpp include/front/App.hpp include/back/VecZ.tpp include/back/VecZ.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Frontend Objects ====#
obj/AssetsLoader.o : src/front/AssetsLoader.cpp include/front/AssetsLoader.hpp
	$(OBJ_DIR)
	$(CCO)

obj/App.o: src/front/App.cpp include/front/App.hpp include/front/Scene.hpp include/front/MainMenu.hpp include/front/PlayerSettingsScene.hpp include/front/MainScene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Scene.o: src/front/Scene.cpp include/front/Scene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/MainMenu.o: src/front/MainMenu.cpp include/front/MainMenu.hpp include/front/Scene.hpp include/front/App.hpp
	$(OBJ_DIR)
	$(CCO)

obj/PlayerSettingsScene.o: src/front/PlayerSettingsScene.cpp include/front/PlayerSettingsScene.hpp include/front/TextField.hpp include/front/Button.hpp include/front/App.hpp
	$(OBJ_DIR)
	$(CCO)

obj/MainScene.o: src/front/MainScene.cpp include/front/MainScene.hpp include/front/Scene.hpp include/front/App.hpp include/front/PieceDisplayer.hpp include/front/TraxPieceDisplayer.hpp include/front/DomPieceDisplayer.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Button.o: src/front/Button.cpp include/front/Button.hpp include/front/App.hpp
	$(OBJ_DIR)
	$(CCO)

obj/TextField.o: src/front/TextField.cpp include/front/TextField.hpp include/front/App.hpp
	$(OBJ_DIR)
	$(CCO)

obj/PieceDisplayer.o: src/front/PieceDisplayer.cpp include/front/PieceDisplayer.hpp include/front/App.hpp 
	$(OBJ_DIR)
	$(CCO)

obj/TraxPieceDisplayer.o: src/front/TraxPieceDisplayer.cpp include/front/TraxPieceDisplayer.hpp include/front/PieceDisplayer.hpp include/front/Controller.hpp
	$(OBJ_DIR)
	$(CCO)

obj/DomPieceDisplayer.o: src/front/DomPieceDisplayer.cpp include/front/DomPieceDisplayer.hpp include/front/PieceDisplayer.hpp include/front/Controller.hpp include/front/AssetsLoader.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Controller.o: src/front/Controller.cpp include/front/Controller.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Backend Objects ====#
obj/Piece.o: src/back/Piece.cpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/DomPiece.o: src/back/DomPiece.cpp include/back/DomPiece.hpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/TraxPiece.o: src/back/TraxPiece.cpp include/back/TraxPiece.hpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Sack.o : src/back/Sack.cpp include/back/Sack.hpp include/back/Piece.hpp include/back/DomPiece.hpp include/back/TraxPiece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Player.o: src/back/Player.cpp include/back/Player.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Game.o: src/back/Game.cpp include/back/Game.hpp include/back/VecZ.hpp include/back/Sack.hpp include/back/Piece.hpp include/back/Player.hpp include/back/VecZ.tpp include/back/VecZ.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Trax.o: src/back/Trax.cpp include/back/Trax.hpp include/back/Game.hpp include/back/TraxPiece.hpp include/back/VecZ.hpp include/back/Sack.hpp include/back/Piece.hpp include/back/Player.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Domino.o: src/back/Domino.cpp include/back/Domino.hpp include/back/Game.hpp include/back/DomPiece.hpp include/back/VecZ.hpp include/back/Sack.hpp include/back/Piece.hpp include/back/Player.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Clean rule =====#
clean:
	rm -rf obj/ $(TARGET) test

#==== Tests ====# 
memtest: test $(TEST_OBJ)
	valgrind ./$(TTARGET)

test: $(TEST_OBJ)
	$(CC) -o $(TTARGET) $(TEST_OBJ)

obj/Test.o: src/Test.cpp include/back/Piece.hpp include/back/DomPiece.hpp include/back/TraxPiece.hpp include/back/Sack.hpp include/back/VecZ.hpp include/back/Game.hpp include/back/Trax.hpp include/back/Player.hpp
	$(OBJ_DIR)
	$(CCO)