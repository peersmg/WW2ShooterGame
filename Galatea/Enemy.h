
//Title     : Enemy.h
//Purpose   : Enemy header.
//Author    : Matthew Peers
//Date      : 05/12/16

#pragma once
#include "GameObject.h"

// Predeclaration of EnemyCollection
class EnemyCollection;

class Enemy : public GameObject
{
protected:
	Rectangle2D collisionShape;     // Collision shape
	float m_health;                 // Enemy health
	float m_hurtTimer;              // How long the enemy should flash red for when hit
	Vector2D m_velocity;            // Velocity of the enemy

public:

  // Constructor
	Enemy();

  // Initialise the gameobject with default values
  // Parameters:  Vector2D Position                 - Where the enemy will spawn
  //              EnemyCollection *enemyCollection  - Pointer to the enemy manager
  virtual void Initialise(Vector2D position, EnemyCollection *enemyCollection) = 0;

  // Update the gameobject logic, called every frame
  // Parameters:  float deltaTime     - Frame time
	virtual void Update(float deltaTime) = 0;

	// Process the collisions of this gameobject
  // Parameters:  GameObject &other   - Reference to game object collided with
	void ProcessCollision(GameObject &other);

  // Returns the collision shape
	IShape2D& GetCollisionShape();

  // Recieves and handles events
  // Parameters:  Event evt   - Struct containing event information
	void HandleEvent(Event evt);

  // Deactivate this game object and create an explosion effect
	void Explode();
};

