CC=g++ --std=c++11 -Wall
INCL=-Iinclude
SFML=-lsfml-graphics -lsfml-window -lsfml-system
CCO=$(CC) $(INCL) -c $< -o $@

# Make an obj/ directrory to store all .o files
OBJ_DIR=@mkdir obj -p

# Backend Objects
BACK_OBJ=obj/Carcassonne.o obj/CarcPiece.o obj/Domino.o obj/DomPiece.o obj/Game.o obj/Piece.o obj/Player.o obj/PlayerCarc.o obj/Sack.o obj/Trax.o obj/TraxPiece.o 
# Frontend Objects 
FRONT_OBJ=obj/App.o obj/AssetsLoader.o obj/Button.o obj/CarcPieceDisplayer.o obj/DomPieceDisplayer.o obj/DrawZone.o obj/ChooseScene.o obj/FinalScene.o obj/MainMenu.o obj/MainScene.o obj/PieceDisplayer.o obj/PlayerSettingsScene.o obj/ScoreBoard.o obj/TextField.o obj/TraxPieceDisplayer.o  

# Final Objects
OBJECTS=obj/Main.o $(BACK_OBJ) $(FRONT_OBJ) 
TEST_OBJ=obj/Test.o obj/Piece.o obj/DomPiece.o obj/TraxPiece.o obj/CarcPiece.o obj/Sack.o obj/Game.o obj/Trax.o obj/Player.o obj/PlayerCarc.o

# Output files' names.
TARGET=main
TTARGET=test

all: $(TARGET) $(TTARGET)

#==== Clean rule =====#
clean:
	rm -rf obj/ $(TARGET) test

#==== Main ====#
main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(SFML)

obj/Main.o: src/Main.cpp include/front/App.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Test ====#
test: $(TEST_OBJ)
	$(CC) -o $(TTARGET) $(TEST_OBJ)

obj/Test.o: src/Test.cpp include/back/Piece.hpp include/back/DomPiece.hpp include/back/TraxPiece.hpp include/back/Sack.hpp include/back/VecZ.hpp include/back/Game.hpp include/back/Trax.hpp include/back/Player.hpp include/back/CarcPiece.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Frontend Objects ====#
obj/App.o: src/front/App.cpp include/front/App.hpp include/front/AssetsLoader.hpp include/front/Scene.hpp include/back/Game.hpp include/back/UnknownGamemodeException.hpp include/front/MainMenu.hpp include/front/PlayerSettingsScene.hpp include/front/MainScene.hpp include/front/FinalScene.hpp include/front/ChooseScene.hpp include/back/Domino.hpp include/back/Trax.hpp include/back/Carcassonne.hpp
	$(OBJ_DIR)
	$(CCO)

obj/AssetsLoader.o: src/front/AssetsLoader.cpp include/front/AssetsLoader.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Button.o: src/front/Button.cpp include/front/Button.hpp include/front/App.hpp
	$(OBJ_DIR)
	$(CCO)

obj/CarcPieceDisplayer.o: src/front/CarcPieceDisplayer.cpp include/front/CarcPieceDisplayer.hpp include/front/PieceDisplayer.hpp include/back/CarcPiece.hpp include/back/PlayerCarc.hpp
	$(OBJ_DIR)
	$(CCO)

obj/ChooseScene.o: src/front/ChooseScene.cpp include/front/ChooseScene.hpp include/front/App.hpp include/front/Scene.hpp include/front/Button.hpp include/back/PlayerCarc.hpp include/back/TraxPiece.hpp include/back/CarcPiece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/DomPieceDisplayer.o: src/front/DomPieceDisplayer.cpp include/front/DomPieceDisplayer.hpp include/front/PieceDisplayer.hpp include/back/DomPiece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/DrawZone.o: src/front/DrawZone.cpp include/front/DrawZone.hpp include/front/App.hpp include/front/Button.hpp include/front/PieceDisplayer.hpp include/front/DomPieceDisplayer.hpp include/front/TraxPieceDisplayer.hpp include/front/CarcPieceDisplayer.hpp
	$(OBJ_DIR)
	$(CCO)

obj/FinalScene.o: src/front/FinalScene.cpp include/front/FinalScene.hpp include/front/App.hpp include/front/Scene.hpp include/front/Button.hpp include/front/MainScene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/MainMenu.o: src/front/MainMenu.cpp include/front/MainMenu.hpp include/front/App.hpp include/front/Button.hpp include/front/Scene.hpp
	$(OBJ_DIR)
	$(CCO)

obj/MainScene.o: src/front/MainScene.cpp include/front/MainScene.hpp include/front/ScoreBoard.hpp include/front/DrawZone.hpp include/front/App.hpp include/front/Scene.hpp include/front/ScoreBoard.hpp include/front/TextField.hpp include/front/PieceDisplayer.hpp include/back/Game.hpp include/front/TraxPieceDisplayer.hpp include/front/CarcPieceDisplayer.hpp include/front/DomPieceDisplayer.hpp include/back/Domino.hpp include/back/Trax.hpp include/back/Carcassonne.hpp include/Pos.hpp
	$(OBJ_DIR)
	$(CCO)

obj/PieceDisplayer.o: src/front/PieceDisplayer.cpp include/front/PieceDisplayer.hpp include/front/App.hpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/PlayerSettingsScene.o: src/front/PlayerSettingsScene.cpp include/front/PlayerSettingsScene.hpp include/front/App.hpp include/front/Scene.hpp include/front/Button.hpp include/front/TextField.hpp 
	$(OBJ_DIR)
	$(CCO)

obj/ScoreBoard.o: src/front/ScoreBoard.cpp include/front/ScoreBoard.hpp include/front/App.hpp include/back/Game.hpp include/back/PlayerCarc.hpp
	$(OBJ_DIR)
	$(CCO)

obj/TextField.o: src/front/TextField.cpp include/front/TextField.hpp include/front/App.hpp
	$(OBJ_DIR)
	$(CCO)

obj/TraxPieceDisplayer.o: src/front/TraxPieceDisplayer.cpp include/front/TraxPieceDisplayer.hpp include/front/PieceDisplayer.hpp include/front/AssetsLoader.hpp include/back/TraxPiece.hpp
	$(OBJ_DIR)
	$(CCO)

#==== Backend Objects ====#
obj/Carcassonne.o: src/back/Carcassonne.cpp include/back/Carcassonne.hpp include/back/Game.hpp include/back/CarcPiece.hpp include/back/PlayerCarc.hpp include/back/VecZ.hpp include/back/VecZ.tpp include/back/Piece.hpp include/back/Player.hpp include/back/Sack.hpp include/back/Piece.hpp include/back/UnknownGamemodeException.hpp
	$(OBJ_DIR)
	$(CCO)

obj/CarcPiece.o: src/back/CarcPiece.cpp include/back/CarcPiece.hpp include/back/Piece.hpp include/Pos.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Domino.o: src/back/Domino.cpp include/back/Domino.hpp include/back/Game.hpp include/back/VecZ.hpp include/back/VecZ.tpp include/back/Piece.hpp include/back/Player.hpp include/back/Sack.hpp include/back/Piece.hpp include/back/UnknownGamemodeException.hpp include/back/DomPiece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/DomPiece.o: src/back/DomPiece.cpp include/back/DomPiece.hpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Game.o: src/back/Game.cpp include/back/Game.hpp include/back/VecZ.hpp include/back/VecZ.tpp include/back/Piece.hpp include/back/Player.hpp include/back/Sack.hpp include/back/Piece.hpp include/back/UnknownGamemodeException.hpp include/back/DomPiece.hpp include/back/TraxPiece.hpp include/back/CarcPiece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Piece.o: src/back/Piece.cpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Player.o: src/back/Player.cpp include/back/Player.hpp
	$(OBJ_DIR)
	$(CCO)

obj/PlayerCarc.o: src/back/PlayerCarc.cpp include/back/PlayerCarc.hpp include/back/Player.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Sack.o: src/back/Sack.cpp include/back/Sack.hpp include/back/Piece.hpp include/back/UnknownGamemodeException.hpp include/back/DomPiece.hpp include/back/TraxPiece.hpp include/back/CarcPiece.hpp
	$(OBJ_DIR)
	$(CCO)

obj/Trax.o: src/back/Trax.cpp include/back/Trax.hpp include/back/Game.hpp include/back/TraxPiece.hpp include/back/Piece.hpp include/back/VecZ.hpp include/back/VecZ.tpp include/back/Piece.hpp include/back/Player.hpp include/back/Sack.hpp include/back/Piece.hpp include/back/UnknownGamemodeException.hpp include/back/TraxPiece.hpp include/Pos.hpp
	$(OBJ_DIR)
	$(CCO)

obj/TraxPiece.o: src/back/TraxPiece.cpp include/back/TraxPiece.hpp include/back/Piece.hpp
	$(OBJ_DIR)
	$(CCO)