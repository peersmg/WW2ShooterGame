#pragma once

#include "GameObject.h"

class Explosion : public GameObject
{
private:
  Rectangle2D collisionShape;   // Collision shape
  Vector2D m_velocity;          // Explosion velocity
  float m_animationSpeed;       // Explosion animation speed
  float m_animationPos;         // Image index to show
  bool m_playerExplosion;       // Is the explosion for the player

public:

  // Constructor
  Explosion();

  // Initialise the gameobject with default values
  void Initialise(Vector2D position, Vector2D velocity, float scale, float animationSpeed = 30, bool playerExplosion = false);

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // 
  void SetPostion(float newXPosition);

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Recieves and handles events
  void HandleEvent(Event evt);
};

