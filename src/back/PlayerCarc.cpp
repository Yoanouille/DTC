#include "back/PlayerCarc.hpp"

using namespace std;

PlayerCarc::PlayerCarc(string nom) : Player(nom), nb_pawn{10} {}

PlayerCarc::~PlayerCarc() {}

void PlayerCarc::addPawn(int nb) {nb_pawn += nb;}

int PlayerCarc::getNbPawn() const {return nb_pawn;}