#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include "BuildingCollection.h"

class EnemyCollection : public GameObject
{
private:

  static const int MAXENEMIES = 20;           // Maxumum number of enemies that can ever spawn
  int m_maxEnemies;                           // Maximum number of enemies that can currently spawn
  int m_currentEnemyCount;                    // Number of enemies currently in the world
  float m_spawnCooldown;                      // Time between spawning enemies

  Rectangle2D collisionShape;                 // Collision shpe
  Enemy *m_pEnemies[MAXENEMIES];              // Array of enemies
  BuildingCollection *m_pBuildingCollection;  // Pointer to the building collection

public:

  // Constructor
  EnemyCollection();

  // Initialise the gameobject with default values
  void Initialise(BuildingCollection *buildingCollection);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);
  
  // Update the gameojects graphics
  void Draw();

  // Reset the cooldown between enemies spawning
  void ResetCooldown();
  
  // Creates a random enemy
  void SpawnRandomEnemy();

  // Remove an enemy from the master array
  void RemoveEnemy(Enemy *enemy);

  // Deactivate a given enemy
  void DeactivateEnemy(Enemy *enemy);

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Recieves and handles events
  void HandleEvent(Event evt);

  // Deactivate this game object
  void Explode();
};

