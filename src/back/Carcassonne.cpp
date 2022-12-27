#include "back/Carcassonne.hpp"
#include "back/CarcPiece.hpp"
#include "back/PlayerCarc.hpp"
#include <stack>

using namespace std;

/** 
 * Constructor :
 * We initialize the sack and we place the first Piece on the board.
 */
Carcassonne::Carcassonne(int size, int perm) : pawn_player{}
{ 
    s.fill(size, 2, perm);
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
    //cout << "CANPLACE" << endl;
    if(((CarcPiece &) p).getType(di, dj, false, di == 4) == Abbaye) return true;
    board[i][j] = &p;
    int s = search(i, j, di, dj, ((CarcPiece &) p).getType(di, dj, false, di == 4), true, false, false, false);
    cleanColor();
    board[i][j] = nullptr;
    return (s != -1);
}

bool Carcassonne::canPlace(int i, int j, Piece &p){
    // Connectivity test
    if(Game::canPlace(i,j,p)){
        CarcPiece c = (CarcPiece &) p;
        if(c.hasPawn()){
            bool b = canPlacePawn(i,j, c.getPawnCoordinates().i,c.getPawnCoordinates().j, p);
            //cout << b << endl;
            return b;
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
            if(c->getType(di, dj, false,false) == Road || c->getType(di, dj, false, di == 4) == Town)
            {
                //cout << "EXPLORE " << c->getType(di, dj, false, di == 4) << endl;
                // Search removes the pawns so it's ok to iterate over all subcases.
                search(i, j, di, dj, CarcType(c->getType(di, dj, false,  di == 4)), false, false, false, true);
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
            if(board[i + di][j + dj] != nullptr)
                if(((CarcPiece *)board[i + di][j + dj])->getCenter() == Abbaye 
                && ((CarcPiece *)board[i + di][j + dj])->hasPawn()
                && ((CarcPiece *)board[i + di][j + dj])->getPawnCoordinates().i == 4)
                {
                    abbayes.push_back({i+di, j+dj});
                }
        

    // Give points to all players that have the Abbaye surrounded and give the pawns back
    for (Pos &p : abbayes){
        int count = 0;
        for(int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
                if((di != 0 || dj != 0) && board[p.i + di][p.j + dj] != nullptr)
                    count ++;
        if (count == 8)
        {
            players[((CarcPiece *)board[p.i][p.j])->getPawn()]->addScore(9);
            ((PlayerCarc *)players[((CarcPiece *)board[p.i][p.j])->getPawn()])->addPawn(1);
            ((CarcPiece *)board[p.i][p.j])->removeAllPawn();
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
 * @param cent A boolean that is true if we are handling the central subcase.
 * 
 * @return The points gained at the end of the exploration
 */
int Carcassonne::search(int i, int j, int di, int dj, CarcType type, bool placing, bool final, bool finalField, bool remove)
{
    // Initialize the stack and push the first element
    stack<Elem> s{};
    s.push({i, j, di, dj});

    if(finalField) 
    {
        pawn_player = {};
        pawn_player.resize(nb_player);
        for(int i = 0; i < nb_player; i++)
            pawn_player[i] = 0;
    }

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
            if(final) continue;
            if(finalField) return 0;
            if(!placing) return 0;
            continue;
        }

        // If the subcase[di][dj] of the Piece at (i,j) is aleady marked we do nothing and pop the next element
        // Same if the type of the subcase[di][dj] of the Piece is the type we're proceeding
        //cout << "Color : " << c->getColor(e.di, e.dj, false, e.di == 4) << endl;
        //cout << "Type : " << c->getColor(e.di, e.dj, false, e.di == 4) << endl;


        if(c->getColor(e.di, e.dj, false, e.di == 4) == 1) continue;
        if(c->getType(e.di, e.dj, false, e.di == 4) != type) continue;

        //cout << "i=" << e.i  << " j=" << e.j << " di=" << e.di << " dj=" << e.dj << endl;
        //cout << c->toString() << endl;
        // Exploration inside the Piece
        c->beginExplore(e.di, e.dj, e.di == 4, type);

        //cout << c->printColor() << endl;
        //c->printColor();
    
        if(c->hasPawn() && c->isPawnMarked() && placing && !(e.i == i && e.j == j)) return -1;

        if (c->hasPawn() && c->isPawnMarked()) nb_pawn[c->getPawn()] ++;
        v.push_back({e.i, e.j});

        // Get all the possibly connected pieces
        // Push them in the stack in order to continue the search
        vector<Pos> next_pos = c->getNextDir();
        for(Pos &p : next_pos)
        {
            //cout << type << " " << "ndi=" << p.i << " " << "ndj=" << p.j << endl;
            int direc = p.i;
            int opp_direc = (direc + 2) % 4;
            int opp_dj = 2 - p.j;

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

    //cout << "Sort de BOUCLE" << endl;
    
    // We get here only if the stack is empty i.e we've finished the exploration

    // If we are looking for placing the Piece, we stop here
    if(placing) {
        //cout << "JE RENVOIE " << nb << endl;
        return nb;
    }
    
    //cout << "Score : " << nb << endl;
    //cout << type << " " << di << " " << dj << " " << nb <<  endl;

    int score = 0;

    if(final && type == Field) 
    {
        //cout << "HEYEYEYE" << endl;
        for(size_t ii = 0; ii < nb_player; ii++)
        {
            pawn_player[ii]+= nb_pawn[ii];
        }
        return 0;
    }

    if(finalField)
    {
        //cout << "i=" << i << " j=" << j << " nb=" << nb << endl;
        for(Pos &p : v)
        {
            CarcPiece *c = (CarcPiece *)board[p.i][p.j];
            for(int dii = 0; dii < 4; dii++)
            {
                for(int djj = 0; djj < 3; djj++)
                {
                    CarcType t = c->getType(dii, djj, false, false);
                    if(t == Field) 
                    {
                        //cout << "BEGIN SEARCH" << endl;
                        search(p.i, p.j, dii, djj, Field, false, true, false, false);
                    }
                }
            }
        }

        return nb;
    }

    if(remove)
    {
        // Remove the pawn on the pieces
        for(Pos &p : v){
            ((CarcPiece *)(board[p.i][p.j]))->removePawn();
        }

        // Give the pawn back to their owners
        for(int i = 0; i < nb_player; i++)
            ((PlayerCarc *)(players[i]))->addPawn(nb_pawn[i]);
    }
    
    // Updating the scores 
    // We give the points to the players that have the maximum number of pawn
    int max = 0;
    for(int i = 0; i < nb_player; i++)
        if(nb_pawn[i] > max) 
            max = nb_pawn[i];

    // max = 0 mean that no pawn has been placed and so we do nothing
    if(max == 0) return nb;

    //Special Score for Town !
    if(!final && type == Town && nb != 2) nb *= 2;

    for(int i = 0; i < nb_player; i++)
    {
        if(nb_pawn[i] == max)
        {
            players[i]->addScore(nb);
        }
    }
    return nb;
}

void Carcassonne::searchFinalTownAndRoadAndAbbaye()
{
    for(int i = board.get_min(); i <= board.get_max(); i++)
    {
        for(int j = board[i].get_min(); j <= board[i].get_max(); j++)
        {
            if(board[i][j] != nullptr)
            {
                CarcPiece *c = (CarcPiece *)(board[i][j]);
                if(c->hasPawn())
                {
                    Pos p = c->getPawnCoordinates();
                    if(c->getType(p.i, p.j, false, p.i == 4) == Town || c->getType(p.i, p.j, false, p.i == 4) == Road)
                    {
                        search(i, j, p.i, p.j, c->getType(p.i, p.j, false, p.i == 4), false, true, false, true);
                    } if(p.i == 4 && c->getType(p.i, p.j, false, true) == Abbaye)
                    {
                        finalSearchAbbaye(i, j);
                    }
                }
            }
        }
    }
}

void Carcassonne::finalSearchAbbaye(int i, int j)
{
    int player = ((CarcPiece *)(board[i][j]))->getPawn();
    int count = 0;
    for(int di = -1; di <= 1; di++)
    {
        for(int dj = -1; dj <= 1; dj++)
        {
            CarcPiece *c = ((CarcPiece *)(board[di][dj]));
            if(c != nullptr) count++;
        }
    }
    players[player]->addScore(count);
    ((CarcPiece *)(board[i][j]))->removeAllPawn();
}

void Carcassonne::finalSearchField()
{
    /**
     * On cherche les villes ferme 
     * dans ses villes ferme, on explore les paines tout autour
     * puis on stocke les pion dans pawn_player
     * 
    */

    for(int i = board.get_min(); i <= board.get_max(); i++)
    {
        for(int j = board[i].get_min(); j <= board[i].get_max(); j++)
        {
            if(board[i][j] != nullptr)
            {
                CarcPiece *c = (CarcPiece *)(board[i][j]);

                for(int di = 0; di < 4; di++)
                {
                    for(int dj = 0; dj < 3; dj++)
                    {
                        if(c->getType(di, dj, false, false) == Town)
                        {
                            if(search(i, j, di, dj, c->getType(di, dj, false, false), false, false, true, false) > 0)
                            {
                                //cout << "BLABLA" << endl;
                                // Updating the scores 
                                // We give the points to the players that have the maximum number of pawn
                                int max = 0;
                                for(int i = 0; i < nb_player; i++)
                                    if(pawn_player[i] > max) 
                                        max = pawn_player[i];

                                if(max != 0)
                                {
                                    for(int i = 0; i < nb_player; i++)
                                    {
                                        if(pawn_player[i] == max)
                                        {
                                            players[i]->addScore(4);
                                        }
                                    }
                                }
                            }

                            cleanField();
                        }
                    }
                }
            }
        }
    }
}


// TODO : Faire en dernier 
bool Carcassonne::gameOver()
{
    //Plus de cartes et ensuite calculer le reste des points
    if(!s.isEmpty()) return false;
    //Algo Final !
    //cout << "FIN CARC -> DEBUT GALERE" << endl;
    searchFinalTownAndRoadAndAbbaye();
    cleanColor();
    //cout << "HEY" << endl;
    finalSearchField();

    return true;
}

void Carcassonne::cleanField()
{
    for(int i = board.get_min(); i <= board.get_max(); i++)
    {
        for(int j = board[i].get_min(); j <= board[i].get_max(); j++)
        {
            if(board[i][j] != nullptr)
                ((CarcPiece *)board[i][j])->cleanColorField();
        }
    }
}