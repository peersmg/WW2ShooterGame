
//Title     : BulletEnemy.h
//Purpose   : BulletEnemy header.
//Author    : Matthew Peers
//Date      : 05/12/16

#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include "EnemyCollection.h"

class BulletEnemy : public Enemy
{
private:
  EnemyCollection *m_pEnemyCollection;    // Pointer to the enemy collection
  float m_turretAngle;                    // Angle the turret on the ship is pointing
  float m_bulletCooldown;                 // Cooldown between shots

public:

  // Constructor
  BulletEnemy();

  // Initialise the gameobject with default values
  void Initialise(Vector2D position, EnemyCollection *enemyCollection);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Update the gameojects graphics
  void Draw();

};

