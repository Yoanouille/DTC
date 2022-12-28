#include "back/Player.hpp"

using namespace std;

Player::Player(string n) : name{n}, score{0} {}

Player::~Player() {}

string Player::getName() const { return name; }

int Player::getScore() const { return score; }

void Player::addScore(int s) { score += s; }