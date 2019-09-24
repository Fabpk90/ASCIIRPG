#include "Actor.h"


Actor::Actor(int health, int damage, char character, DWORD colorMask) : Tile(character, colorMask)
, health(health), damage(damage)
{}

Actor::~Actor()
{
}
