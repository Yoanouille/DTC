#include "back/Carcassonne.hpp"
#include "back/CarcPiece.hpp"
#include "back/PlayerCarc.hpp"
#include <stack>

using namespace std;

/** 
 * Constructor :
 * We initialize the sack and we place the first Piece on the board.
 */
Carcassonne::Carcassonne() { 
    s.fill(0, 2);
    board[0][0] = s.draw();
    nb_piece++;
}

/** Destructor : We do nothing */
Carcassonne::~Carcassonne() {}

/** 
 * Overriden Game::addPlayer in order to add PlayerCarc instead of Player
 * because PlayerCarc have pawns in addition.
 */
void Carcassonne::addPlayer(std::string name)
{
    players.push_back(new PlayerCarc{name});
    nb_player++;
}

/**
 * Check if a pawn can be placed on a piece at (i,j)
 * @param i The line
 * @param j The column
 * @param p The Piece 
 * @param di the side of the Piece
 * @param dj the index of the element in the di-th array of the Piece
 */
bool Carcassonne::canPlacePawn(int i, int j, int di, int dj, Piece &p)
{
    //TODO CHANGER cette horreur                           ici (mettre en argument la piece en plus !)
    return search(i, j, di, dj, ((CarcPiece &) p).getType(di, dj, false, false), true) == -1;
}

/**
 * Place a pawn on a Piece 
 */
void Carcassonne::placePawn(int i, int j, int di, int dj, int player)
{
    if(canPlacePawn(i, j, di, dj, *((CarcPiece *)(board[i][j])))) 
        ((CarcPiece *)(board[i][j]))->placePawn(di,dj,player);
}

bool Carcassonne::canPlace(int i, int j, Piece &p){
    // Connectivity test
    if(Game::canPlace(i,j,p)){
        CarcPiece c = (CarcPiece &) p;
        //TODO : enlever de return true, mais comme ça je peux test
        //return true;
        if(c.hasPawn()){
            return canPlacePawn(i,j, c.getPawnCoordinates().i,c.getPawnCoordinates().j, p);
        }
        return true;
    }

    return false;
}

/**
 * Place the Piece and update scores if needed.
 * Only Road, Town, and Abbaye can give points during the Game.
 * We'll treat these 3 cases.
 */
void Carcassonne::place(int i, int j, Piece &p)
{
    if(!canPlace(i, j, p)) return;
    Game::place(i, j, p);

    CarcPiece *c = (CarcPiece *)(board[i][j]);
    
    for(int di = 0; di < 4; di++)
    {
        for(int dj = 0; dj < 3; dj++)
        {
            if(c->getType(di, dj, false,false) == Road || c->getType(di, dj, false, false) == Town)
            {
                // Search removes the pawns so it's ok to iterate over all subcases.
                search(i, j, di, dj, CarcType(c->getType(di, dj, false, false)), false);
                cleanColor();
            }
        }   
    }

    searchAbbaye(i,j);
    current_player = (current_player + 1) % nb_player;
}


/**
 * Look for an Abbaye next to the Piece at (i,j)
 * And check if the Abbaye has a pawn and if it is surrounded
 * Give the points to the player if the conditions are true
 * 
 * NB : Nothing prevents the Piece at (i,j) to not having an Abbaye at its center.
 */
void Carcassonne::searchAbbaye(int i, int j)
{
    // We store all the neighbour Abbaye in a vector
    vector<Pos> abbayes{};
    for(int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++)
            if(board[i + di][j + di] != nullptr)
                if(((CarcPiece *)board[i + di][j + di])->getCenter() == Abbaye 
                && ((CarcPiece *)board[i + di][j + di])->getPawn() != -1 
                && ((CarcPiece *)board[i + di][j + di])->getPawnCoordinates().i == 4)
                    abbayes.push_back({i+di, j+dj});
        

    // Give points to all players that have the Abbaye surrounded and give the pawns back
    for (Pos &p : abbayes){
        int count = 0;
        for(int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
                if(di != 0 || dj != 0 && board[i + di][j + di] != nullptr)
                    count ++;
        if (count == 8)
        {
            players[((CarcPiece *)board[p.i][p.j])->getPawn()]->addScore(9);
            ((PlayerCarc *)players[((CarcPiece *)board[p.i][p.j])->getPawn()])->addPawn(1);
            ((CarcPiece *)board[p.i][p.j])->removePawn();
        }
    }
}

typedef struct Elem
{
    int i;
    int j;
    int di;
    int dj;
} Elem;

/**
 * DFS to check connectivity
 * Done with a stack as we usually do
 * Instead of using the pieces themselves, we're doing it with their coordinates
 * and the direction toward the next Piece to explore
 * 
 * The function will be called both 
 * to check if a Piece can be placed and
 * to handle point earnings after a Piece was just placed.
 * 
 * @param i The starting line index
 * @param j The starting column index
 * @param di The index of the subarray of the CarcPiece at (i,j)
 * @param dj The index of the element in the di-th subarray
 * @param type The type we are checking
 * @param placing A boolean that is true if we currently want to place the Piece
 * @return The points gained at the end of the exploration
 */
int Carcassonne::search(int i, int j, int di, int dj, CarcType type, bool placing)
{
    // Initialize the stack and push the first element
    stack<Elem> s{};
    s.push({i, j, di, dj});

    // nb is used to count the points gained at the end of the exploration
    // counting points is equivalent to counting the number of tiles(of some type) that are connected.
    // bonuses will be added to it.
    int nb = 0;

    // We'll count the number of pawn we'll come across through the exploration
    // It will be used to determine a max to give the points to the Players
    int nb_pawn[nb_player];
    for(int k = 0; k < nb_player; k++)
        nb_pawn[k] = 0;
    
    // This vector stored the Pieces we've explored
    // in order to remove the pawns and give points.
    vector<Pos> v{};

    // Start the exploration
    while(true)
    {
        if(s.empty()) break;

        // Pop doesn't return the element poped se we have to store it with top before poping
        Elem e = s.top();
        s.pop();
        
        // Check if the Piece is nullptr
        CarcPiece *c = (CarcPiece *)(board[e.i][e.j]);
        if(c == nullptr) 
        {
            if(!placing) return 0;
            continue;
        }

        // If the subcase[di][dj] of the Piece at (i,j) is aleady marked we do nothing and pop the next element
        // Same if the type of the subcase[di][dj] of the Piece is the type we're proceeding
        if(c->getColor(e.di, e.dj, false, false) == 1) continue;
        if(c->getType(e.di, e.dj, false, false) != type) continue;

        // Exploration inside the Piece
        c->beginExplore(e.di, e.dj, false, type);
        //c->printColor();
    
        if(c->isPawnMarked() && placing && !(e.i == i && e.j == j)) return -1;

        if (c->getPawn() != -1)
                if (c-> isPawnMarked())
                    nb_pawn[i] ++;
        v.push_back({e.i, e.j});

        // Get all the possibly connected pieces
        // Push them in the stack in order to continue the search
        vector<Pos> next_pos = c->getNextDir();
        for(Pos &p : next_pos)
        {
            //cout << type << " " << "ndi=" << p.i << " " << "ndj=" << p.j << endl;
            int direc = p.i;
            int opp_direc = (direc + 2) % 4;
            int opp_dj = 2 - dj;

            if(direc == UP) s.push({e.i - 1, e.j, opp_direc, opp_dj});
            if(direc == DOWN) s.push({e.i + 1, e.j, opp_direc, opp_dj});
            if(direc == LEFT) s.push({e.i, e.j - 1, opp_direc, opp_dj});
            if(direc == RIGHT) s.push({e.i, e.j + 1, opp_direc, opp_dj});
        }
        //cout << endl;

        // TODO : pq nb bizarre ? 
        // End of the actual Piece's exploration : we increment number
        nb++;
        if(c->getBonus()) nb++;
    }
    
    // We get here only if the stack is empty i.e we've finished the exploration

    // If we are looking for placing the Piece, we stop here
    if(placing) return nb;
    
    //cout << type << " " << di << " " << dj << " " << nb <<  endl;

    // Remove the pawn on the pieces
    for(Pos &p : v){
        ((CarcPiece *)(board[p.i][p.j]))->removePawn();
    }

    // Give the pawn back to their owners
    for(int i = 0; i < nb_player; i++)
        ((PlayerCarc *)(players[i]))->addPawn(nb_pawn[i]);
    
    // Updating the scores 
    // We give the points to the players that have the maximum number of pawn
    int max = 0;
    for(int i = 0; i < nb_player; i++)
        if(nb_pawn[i] > max) 
            max = nb_pawn[i];

    // max = 0 mean that no pawn has been placed and so we do nothing
    if(max == 0) return nb;

    for(int i = 0; i < nb_player; i++)
        if(nb_pawn[i] == max) players[i]->addScore(nb);
    
    return nb;
}

// TODO : Faire en dernier 
bool Carcassonne::gameOver()
{
    //Plus de cartes et ensuite calculer le reste des points
    return false;
}