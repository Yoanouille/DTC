#include "back/Carcassonne.hpp"
#include "back/CarcPiece.hpp"
#include "back/PlayerCarc.hpp"
#include <stack>

using namespace std;

Carcassonne::Carcassonne() {
    s.fill(0, 2);
}

Carcassonne::~Carcassonne() {}

void Carcassonne::addPlayer(std::string name)
{
    players.push_back(new PlayerCarc{name});
    nb_player++;
}

//! Il faut verifier qu'il y a personne d'autres sur la route/ville/plaine
bool Carcassonne::canPlace(int i, int j, Piece &p)
{

    if(!Game::canPlace(i, j, p)) return false;

    //TODO return true à enlever, seulement pour test
    // ce qui y a en dessous m'empeche de mettre des pions donc à régler
    return true;

    CarcPiece &c = (CarcPiece &)(p);
    if(!c.hasPawn()) return true;

    Pos po = c.getPosPawn();

    bool rep = false;
    
    //! Cas du milieu à gérer
    //! Peut être seulement les abbayes
    
    if(search(i, j, po.i, po.j, CarcType(c.getType(po.i, po.j, false)), true) > 0) rep = false;
    cleanColor();
    return rep;
}

void Carcassonne::place(int i, int j, Piece &p)
{
    if(!canPlace(i, j, p)) return;
    Game::place(i, j, p);

    CarcPiece *c = (CarcPiece *)(plateau[i][j]);
    
    for(int di = 0; di < 4; di++)
    {
        for(int dj = 0; dj < 3; dj++)
        {
            // ! Ne faire ça que pour CarcType Road et Town
            if(c->getType(di,dj,false) == Road)
            {
                //cout << "Explore" << endl;
                //cout << "i=" << i << " j=" << j << " di=" << di << " dj=" << dj << endl;
                search(i, j, di, dj, CarcType(c->getType(di, dj, false)), false);
                //cout << endl;
                cleanColor();
            }
        }   
    }

    //Regarder autour si on trouve une abbaye avec un pion et voir si on la ferme

}

typedef struct Elem
{
    int i;
    int j;
    int di;
    int dj;
} Elem;


//! TEST d'une autre facon de parcourir plus général mais un peu plus complexe 
//? Fonction beaucoup plus élégante
int Carcassonne::search(int i, int j, int di, int dj, CarcType type, bool placing)
{
    stack<Elem> s{};
    s.push({i, j, di, dj});

    int nb = 0;

    int nb_pawn[nb_player];
    for(int k = 0; k < nb_player; k++)
        nb_pawn[k] = 0;
    
    vector<Pos> v;

    while(true)
    {
        if(s.empty()) break;
        Elem e = s.top();
        s.pop();
        CarcPiece *c = (CarcPiece *)(plateau[e.i][e.j]);
        if(c == nullptr) 
        {
            if(!placing) return 0;
            continue;
        }


        //cout << "i=" << e.i << " j=" << e.j << " di=" << e.di << " dj=" << e.dj << endl;
        //cout << c->toString() << endl;

        if(c->getColor(e.di, e.dj, false) == 1)
        {
            //cout << c->getColor(e.di, e.dj, false) << endl;
            continue;
        }
        //cout << "type=" << c->getType(e.di, e.dj, false) << endl;
        if(c->getType(e.di, e.dj, false) != type) 
        {
            continue;
        }

        c->beginExplore(e.di, e.dj, false, type);
        c->printColor();
        if(c->getNbPawn(nb_pawn, nb_player) > 0 && placing && !(e.i == i && e.j == j)) return 0;

        v.push_back({e.i, e.j});

        vector<Pos> next_pos = c->getNextDir();
        for(Pos &p : next_pos)
        {
            cout << type << " " << "ndi=" << p.i << " " << "ndj=" << p.j << endl;
            int direc = p.i;
            int opp_direc = (direc + 2) % 4;
            int opp_dj = 2 - dj;

            if(direc == UP) s.push({e.i - 1, e.j, opp_direc, opp_dj});
            if(direc == DOWN) s.push({e.i + 1, e.j, opp_direc, opp_dj});
            if(direc == LEFT) s.push({e.i, e.j - 1, opp_direc, opp_dj});
            if(direc == RIGHT) s.push({e.i, e.j + 1, opp_direc, opp_dj});
        }
        cout << endl;

        nb++;
        if(c->getBonus()) nb++;
        
    }
    

    if(placing) return nb;
    //cout << type << " " << di << " " << dj << " " << nb <<  endl;

    //! On enlève les pions
    for(Pos &p : v)
        ((CarcPiece *)(plateau[p.i][p.j]))->removeAllPawn();
    
    //! On redonne les pions
    for(int i = 0; i < nb_player; i++)
        ((PlayerCarc *)(players[i]))->addPawn(nb_pawn[i]);
    
    //! On update les scores
    int max = 0;
    for(int i = 0; i < nb_player; i++)
        if(nb_pawn[i] > max) 
            max = nb_pawn[i];

    if(max == 0) return nb;

    for(int i = 0; i < nb_player; i++)
        if(nb_pawn[i] == max) players[i]->addScore(nb);
    
    return nb;

}

bool Carcassonne::gameOver()
{
    //Plus de cartes et ensuite calculer le reste des points
    return false;
}