#pragma once

#include "GameObject.h"

#include "Ship.h"
#include "BuildingCollection.h"
#include "EnemyCollection.h"

class GameManager : public GameObject
{
private:
  Rectangle2D collisionShape;                 // Collision shape

  bool m_gameRunning;                         // Is the game currently running
  float m_playerExperience;                   // The players xp
  float m_experienceNeeded;                   // The experience needed for the player to level up

  float m_playerFuel;                         // Players current fuel
  float m_playerHealth;                       // Players current health
  float m_playerAmmo;                         // Players current ammo
  int m_playerLevel;                          // Players current level
  float m_score;                              // Players current score

  float m_flickerCountdown;                   // "Upgrade available!" Text flicker countdown
  int m_newHighScore;                         // The index of the new highscore (-1 if there is no new highscore)

  int m_highScores[5];                        // Array of highscores
  bool m_upgradeAvailable;                    // Is an upgrade available

  Ship *m_pShip;                              // Pointer to the player
  BuildingCollection *m_pBuildingCollection;  // Pointer to the building collection
  EnemyCollection *m_pEnemyCollection;        // Pointer to the enemy collection

public:

  // Constructor
  GameManager();

  // Initialise the gameobject with default values
  void Initialise();

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Recieves and handles events
  void HandleEvent(Event evt);

  // Called when the players health reaches 0
  void GameOver();

  // 
  void Draw();
};

