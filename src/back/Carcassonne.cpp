#include "back/Carcassonne.hpp"
#include "back/CarcPiece.hpp"
#include <stack>

using namespace std;

Carcassonne::Carcassonne() {}

Carcassonne::~Carcassonne() {}

void Carcassonne::place(int i, int j, Piece &p)
{
    if(!canPlace(i, j, p)) return;
    Game::place(i, j, p);
    
    //! PENSER A CLEANCOLOR APRES CHAQUE SEARCH !!!!!!!!!

    //Si la piece a une ville -> parcours ville
    //    durant le parcouts stocker les pions qui sont dans la ville
    //    appeler récursivement la ville d'à côté tout en marquant
    //    on stocke le nombre case visité
    //    si on detecte une ville connectée au vide on stop tout
    //    sinon on incrémente comme il faut le score des joueurs et faut vider les pions pour les rendre aux joueurs

    //Regarder autour si on trouve une abbaye avec un pion et voir si on la ferme
}

void Carcassonne::searchRoad(int i, int j, Direction d)
{
    vector<int> player_pawn{};
    stack<Triple> s;

    s.push({i, j, d});

    int nb;

    while(true)
    {
        if(s.empty()) break;

        Triple &t = s.top();
        
        CarcPiece *c = (CarcPiece *)(plateau[t.i][t.j]);

        // ! Stocker dans une liste pour vider les pions

        nb++;

        c->setColor(1);

        int play_pawn[5] = {-1,-1,-1,-1,-1};
        c->getPlayPawn(play_pawn);

        //! SI C'EST LA FIN D'UNE ROUTE
        //C'est un cas particulier car la route n'est pas connecté aux autres routes de la piece
        if(c->getCenter() == Town || c->getCenter() == Crossroad || c->getCenter() == Abbaye)
        {
            if(d == UP && plateau[t.i - 1][t.j] == nullptr) return;
            if(d == UP && plateau[t.i - 1][t.j]->getColor() == 0) 
            {
                s.push({t.i - 1, t.j, DOWN});
                if(play_pawn[UP] != -1) player_pawn[play_pawn[UP]]++;
            }

            if(d == DOWN && plateau[t.i + 1][t.j] == nullptr) return;
            if(d == DOWN && plateau[t.i + 1][t.j]->getColor() == 0) 
            {
                s.push({t.i + 1, t.j, UP});
                if(play_pawn[DOWN] != -1) player_pawn[play_pawn[DOWN]]++;
            }
            
            if(d == LEFT && plateau[t.i][t.j - 1] == nullptr) return;
            if(d == LEFT && plateau[t.i][t.j - 1]->getColor() == 0) 
            {
                s.push({t.i, t.j - 1, RIGHT});
                if(play_pawn[LEFT] != -1) player_pawn[play_pawn[LEFT]]++;
            }
            
            if(d == RIGHT && plateau[t.i][t.j + 1] == nullptr) return;
            if(d == RIGHT && plateau[t.i][t.j + 1]->getColor() == 0)
            { 
                s.push({t.i, t.j + 1, LEFT});
                if(play_pawn[RIGHT] != -1) player_pawn[play_pawn[RIGHT]]++;
            }
            
            s.pop();

            //On arrete ici l'itération
            continue;
        }

        //! SI C'EST JUSTE UNE ROUTE
        int col[4] = {-1,-1,-1,-1};
        c->getConnectColor(col);

        //On compte les pions
        for(int i = 0; i < 4; i++)
            if(play_pawn[i] != -1) player_pawn[play_pawn[i]]++;

        //On ajoute dans la pile la/les suites de la routes
        //les suites c'est si la premiere itération
        if(col[UP] == Road && plateau[t.i - 1][t.j] == nullptr) return;
        if(col[UP] == Road && plateau[t.i - 1][t.j]->getColor() == 0)
            s.push({t.i - 1, t.j, DOWN});
        
        if(col[DOWN] == Road && plateau[t.i + 1][t.j] == nullptr) return;
        if(col[DOWN] == Road && plateau[t.i + 1][t.j]->getColor() == 0)
            s.push({t.i + 1, t.j, UP});

        if(col[LEFT] == Road && plateau[t.i][t.j - 1] == nullptr) return;
        if(col[LEFT] == Road && plateau[t.i][t.j - 1]->getColor() == 0)
            s.push({t.i, t.j - 1, RIGHT});

        if(col[RIGHT] == Road && plateau[t.i][t.j + 1] == nullptr) return;
        if(col[RIGHT] == Road && plateau[t.i][t.j + 1]->getColor() == 0)
            s.push({t.i, t.j + 1, LEFT});
        

        s.pop();
    }

    //Normalement si on est ici, c'est que la route était fini
    //! ON AJUSTE LES SCORES
    int max = 0;
    for(int i = 0; i < nb_player; i++)
        if(player_pawn[i] > max) 
            max = player_pawn[i];

    for(int i = 0; i < nb_player; i++)
        if(player_pawn[i] == max) players[i]->addScore(max);

}

bool Carcassonne::gameOver()
{
    //Plus de cartes et ensuite calculer le reste des points
    return false;
}