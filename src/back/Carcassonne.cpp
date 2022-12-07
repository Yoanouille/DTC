#include "back/Carcassonne.hpp"

Carcassonne::Carcassonne() {}

Carcassonne::~Carcassonne() {}

void Carcassonne::place(int i, int j, Piece &p)
{
    if(!canPlace(i, j, p)) return;
    Game::place(i, j, p);
    
    //Sur tout les chemins de la piece -> parcours de chemin
    //    durant le parcours stocker les pions qui sont sur le chemin
    //    appeler récursivement le chemin d'après 
    //      si on tombe sur vide on renvoie *FAUX*
    //      si on tombe en son centre sur ville, carrefour ou abbaye stop on renvoie VRAI
    //    si y a pas un faux, on incrémente le score du/des joueurs qui a/ont le plus de pions, vider les pions et les rendre aux joueurs

    //Si la piece a une ville -> parcours ville
    //    durant le parcouts stocker les pions qui sont dans la ville
    //    appeler récursivement la ville d'à côté tout en marquant
    //    on stocke le nombre case visité
    //    si on detecte une ville connectée au vide on stop tout
    //    sinon on incrémente comme il faut le score des joueurs et faut vider les pions pour les rendre aux joueurs

    //Regarder autour si on trouve une abbaye avec un pion et voir si on la ferme
}

bool Carcassonne::gameOver()
{
    //Plus de cartes et ensuite calculer le reste des points
    return false;
}