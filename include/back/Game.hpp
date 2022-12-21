#ifndef GAME_HPP
#define GAME_HPP

#include "back/VecZ.hpp"
#include "back/Piece.hpp"
#include "back/Player.hpp"
#include "back/Sack.hpp"

typedef struct PiecePos
{
    Piece *p;
    int i;
    int j;
} PiecePos;

class Game
{
    protected:
        VecZ<VecZ<Piece *>> board; 
        std::vector<Player *> players;
        Sack s;

        int nb_player;
        int current_player;
        int nb_piece;

        void cleanColor();

    public:
        Game();
        virtual ~Game();

        virtual void addPlayer(std::string name);
        int getCurrentPlayer() const;
        const std::vector<Player *> getPlayers() const;

        virtual Piece &draw();
        virtual bool canPlace(int, int, Piece &p);
        virtual void place(int, int, Piece &p);
        virtual Player *getWinner() const;
        std::vector<PiecePos> getAllPiece();

        virtual bool gameOver() = 0;


};

#endif