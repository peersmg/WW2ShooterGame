#pragma once


// List of object types available in the game
// Add a name for each possible type of entity in your game
// Still using old enums until C++11 is available

enum ObjectType{ UNKNOWN, MANAGER, UI, SHIP, PING, BUILDING, BULLET, ENEMYBULLET, EXPLOSION, ENEMY, EMITTER, MISSILE, BOMB};

enum GameState{ MENU, PAUSED, RUNNING, GAMEOVER, LEVELUP };