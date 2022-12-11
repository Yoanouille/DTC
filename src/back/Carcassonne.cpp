#include "back/Carcassonne.hpp"
#include "back/CarcPiece.hpp"
#include "back/PlayerCarc.hpp"
#include <stack>

using namespace std;

Carcassonne::Carcassonne() {}

Carcassonne::~Carcassonne() {}

//! Il faut verifier qu'il y a personne d'autres sur la route/ville/plaine
bool Carcassonne::canPlace(int i, int j, Piece &p)
{
    if(!Game::canPlace(i, j, p)) return false;
    bool flag = false;

    CarcPiece *c = (CarcPiece *)(plateau[i][j]);

    for(int di = 0; di < 4; di++)
    {
        for(int dj = 0; dj < 3; dj++)
        {
            if(search_bis(i, j, di, dj, CarcType(c->getType(di, dj, false)), true) > 0) flag = true;
            cleanColor();
            if(flag) return false;
        }   
    }
    return true;
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
            search_bis(i, j, di, dj, CarcType(c->getType(di, dj, false)), false);
            cleanColor();
        }   
    }

    //Regarder autour si on trouve une abbaye avec un pion et voir si on la ferme

}

//! REFLECHIR POUR ADAPTER AUSSI A FIELD OU ALORS FAIRE UNE FONCTION A COTE !!!!

//! AJOUTER BOOLEEN POUR DIRE SI BONUS VILLE !
//? Surement Obsolète maintenant !
//? Fonction très laide !
int Carcassonne::search(int i, int j, Direction d, CarcType type, bool placing)
{
    vector<int> player_pawn{};
    player_pawn.resize(nb_player);
    stack<Triple> s;

    vector<Container> v{};

    s.push({i, j, d});

    int nb;

    while(true)
    {
        if(s.empty()) break;

        Triple &t = s.top();
        Container cont {t.i, t.j, {0,0,0,0}};
        CarcPiece *c = (CarcPiece *)(plateau[t.i][t.j]);
        nb++;

        int play_pawn[5] = {-1,-1,-1,-1,-1};
        c->getPlayPawn(play_pawn);

        c->setColor(1);

        //! SI ON EST AU BORD !
        //C'est un cas particulier car le type n'est pas connecté aux autres type de la piece !
        if((c->getCenter() == Town && type == Road) || c->getCenter() == Crossroad || c->getCenter() == Abbaye)
        {
            if(d == UP && plateau[t.i - 1][t.j] == nullptr)
            {
                if(!placing) return 0;
            }
            else if(d == UP && plateau[t.i - 1][t.j]->getColor() == 0) 
            {
                s.push({t.i - 1, t.j, DOWN});
                if(play_pawn[UP] != -1)
                {
                    if(placing) return 0;
                    player_pawn[play_pawn[UP]]++;
                    cont.pawn[UP] = true;
                }
            }

            if(d == DOWN && plateau[t.i + 1][t.j] == nullptr) 
            {
                if(!placing) return 0;
            }
            else if(d == DOWN && plateau[t.i + 1][t.j]->getColor() == 0) 
            {
                s.push({t.i + 1, t.j, UP});
                if(play_pawn[DOWN] != -1) 
                {
                    if(placing) return 0;
                    player_pawn[play_pawn[DOWN]]++;
                    cont.pawn[DOWN] = true;
                }
            }
            
            if(d == LEFT && plateau[t.i][t.j - 1] == nullptr) 
            {
                if(!placing) return 0;
            }
            else if(d == LEFT && plateau[t.i][t.j - 1]->getColor() == 0) 
            {
                s.push({t.i, t.j - 1, RIGHT});
                if(play_pawn[LEFT] != -1) 
                {
                    if(placing) return 0;
                    player_pawn[play_pawn[LEFT]]++;
                    cont.pawn[LEFT] = true;
                }
            }
            
            if(d == RIGHT && plateau[t.i][t.j + 1] == nullptr) 
            {
                if(!placing) return 0;
            }
            else if(d == RIGHT && plateau[t.i][t.j + 1]->getColor() == 0)
            { 
                s.push({t.i, t.j + 1, LEFT});
                if(play_pawn[RIGHT] != -1) 
                {
                    if(placing) return 0;
                    player_pawn[play_pawn[RIGHT]]++;
                    cont.pawn[RIGHT] = true;
                }
            }
            
            v.push_back(cont);
            s.pop();

            //On arrete ici l'itération
            continue;
        }

        //! SI C'EST JUSTE UNE ROUTE
        int col[4] = {-1,-1,-1,-1};
        c->getConnectColor(col);

        //On compte les pions
        for(int i = 0; i < 4; i++)
        {
            if(play_pawn[i] != -1 && col[i] == type) 
            {
                if(placing) return 0;
                player_pawn[play_pawn[i]]++;
                cont.pawn[i] = true;
            }
        }

        //On ajoute dans la pile la/les suites
        if(col[UP] == type && plateau[t.i - 1][t.j] == nullptr) 
        {
            if(!placing) return 0;
        }
        else if(col[UP] == type && plateau[t.i - 1][t.j]->getColor() == 0)
            s.push({t.i - 1, t.j, DOWN});
        
        if(col[DOWN] == type && plateau[t.i + 1][t.j] == nullptr)
        {
            if(!placing) return 0;
        }
        else if(col[DOWN] == type && plateau[t.i + 1][t.j]->getColor() == 0)
            s.push({t.i + 1, t.j, UP});

        if(col[LEFT] == type && plateau[t.i][t.j - 1] == nullptr) 
        {
            if(!placing) return 0;
        }
        else if(col[LEFT] == type && plateau[t.i][t.j - 1]->getColor() == 0)
            s.push({t.i, t.j - 1, RIGHT});

        if(col[RIGHT] == type && plateau[t.i][t.j + 1] == nullptr) 
        {
            if(!placing) return 0;
        }
        else if(col[RIGHT] == type && plateau[t.i][t.j + 1]->getColor() == 0)
            s.push({t.i, t.j + 1, LEFT});
        

        s.pop();
    }
    //Normalement si on est ici, c'est que la route était fini
    if(placing) return nb;

    //! Enlever les pions des pieces
    for(Container &c : v)
    {
        for(int i = 0; i < 4; i++)
            if(c.pawn[i])
                ((CarcPiece *)(plateau[c.i][c.j]))->removePawn(i);
    }

    //! Redonner aux joueurs leurs pions
    for(int i = 0; i < nb_player; i++)
    {
        ((PlayerCarc *)(players[i]))->addPawn(player_pawn[i]);
    }

    //! ON AJUSTE LES SCORES
    int max = 0;
    for(int i = 0; i < nb_player; i++)
        if(player_pawn[i] > max) 
            max = player_pawn[i];

    for(int i = 0; i < nb_player; i++)
        if(player_pawn[i] == max) players[i]->addScore(nb);
    
    return nb;

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
int Carcassonne::search_bis(int i, int j, int di, int dj, CarcType type, bool placing)
{
    stack<Elem> s{};
    s.push({i, j, di, dj});

    int nb;

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

        if(c->getColor(di, dj, false) == 1) continue;
        if(c->getType(di, dj, false) != type) continue;

        c->explore(di, dj, false, type);
        if(c->getNbPawn(nb_pawn, nb_player) > 0 && placing) return 0;

        v.push_back({e.i, e.j});

        vector<Pos> next_pos = c->getNextDir();
        for(Pos &p : next_pos)
        {
            int direc = p.i;
            int opp_direc = (direc + 2) % 4;
            int opp_dj = 2 - dj;

            if(direc == UP) s.push({e.i - 1, e.j, opp_direc, opp_dj});
            if(direc == DOWN) s.push({e.i + 1, e.j, opp_direc, opp_dj});
            if(direc == LEFT) s.push({e.i, e.j - 1, opp_direc, opp_dj});
            if(direc == RIGHT) s.push({e.i, e.j + 1, opp_direc, opp_dj});
        }

        nb++;
        if(c->getBonus()) nb++;
        
    }

    if(placing) return nb;

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

    for(int i = 0; i < nb_player; i++)
        if(nb_pawn[i] == max) players[i]->addScore(nb);
    
    return nb;


}

bool Carcassonne::gameOver()
{
    //Plus de cartes et ensuite calculer le reste des points
    return false;
}