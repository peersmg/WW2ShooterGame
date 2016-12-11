
//Title     : MissileLauncher.h
//Purpose   : MissileLauncher header.
//Author    : Matthew Peers
//Date      : 05/12/16

#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include "EnemyCollection.h"

class MissileLauncher : public Enemy
{
private:
  EnemyCollection *m_pEnemyCollection;  // Pointer to enemy collection
  float m_siloCooldown;                 // Cooldown between volley of missiles
  float m_siloFireCount;                // How many missiles have been fired
  float m_missileCooldown;              // Cooldown between each missile fired

public:

  // Constructor
  MissileLauncher();

  // Initialise the gameobject with default values
  void Initialise(Vector2D position, EnemyCollection *enemyCollection);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);
};