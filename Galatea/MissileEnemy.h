
//Title     : MissileEnemy.h
//Purpose   : MissileEnemy header.
//Author    : Matthew Peers
//Date      : 05/12/16

#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include "EnemyCollection.h"

class MissileEnemy : public Enemy
{
private:
  EnemyCollection *m_pEnemyCollection;  // Pointer to EnemyCollection
  float m_bombCooldown;                 // Cooldown between each bomb fired
public:
  
  // Constructor
  MissileEnemy();

  // Initialise the gameobject with default values
  void Initialise(Vector2D position, EnemyCollection *enemyCollection);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);
};

