#include "ArenaObjects.h"

Vector <Object> ArenaObjects::stones;
Vector <Object> ArenaObjects::walls;
Vector <Bomb> ArenaObjects::bombs;
Vector <Explosion> ArenaObjects::explosions;
Vector <Enemy> ArenaObjects::enemies;

ArenaObjects& ArenaObjects::getInstance()
{
	static ArenaObjects objects;
	return objects;
}

ArenaObjects::ArenaObjects() {}


