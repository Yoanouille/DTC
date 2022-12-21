#ifndef CARCPIECE_HPP
#define CARCPIECE_HPP

#include "Piece.hpp"
#include <iostream>
#include <vector>

enum CarcType
{
    Field = 0,
    Town = 1,
    Road = 2,
    Abbaye = 3,
    Crossroad = 4,
};

typedef struct Pos
{
    int i;
    int j;
} Pos;

class CarcPiece : public Piece
{
    private:
        int const id;

        CarcType border[4][3];

        CarcType center_border[4][3];
        CarcType center;

        // Represents the player that owns the pawn
        int pawn;
        int pawn_coordinates[2];

        int color_border[4][3];
        int color_center_border[4][3];
        int color_center;
        bool bonus;

        // Used by beginExplore
        void explore(int i, int j, CarcType t);
        void exploreCenter(int i, int j, bool cent, CarcType t);
    
    public:
        CarcPiece(int id);
        ~CarcPiece();

        // Getters
        const int getId() const;
        bool getBonus() const;
        CarcType getCenter() const;
        int getColor(int i, int j, bool centArray, bool cent) const;
        CarcType getType(int i, int j, bool centArray, bool cent) const;
        int getPawn() const;
        Pos getPawnCoordinates();

        bool connectable(Piece &p, int pDir) override;
        void getConnectColor(int *t) const override;
        std::string toString() const override;

        bool hasPawn();
        void placePawn(int i, int j, int player);
        void removePawn();
        void removeAllPawn();

        void cleanColor() override;
        //void printColor();

        void beginExplore(int i, int j, bool cent, CarcType t);
        std::vector<Pos> getNextDir();
};

#endif