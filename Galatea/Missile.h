#pragma once

#include "GameObject.h"

class Missile : public GameObject
{
private:
  Rectangle2D collisionShape;   // Missile collision shape
  Vector2D m_velocity;          // Missile velocity
  Vector2D m_imageSize;         // Size of the missile graphic within the file

  float m_speed;                // Speed of the missile
public:

  // Constructor
  Missile();

  // Initialise the gameobject with default values
  void Initialise(float angle, Vector2D position);

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Deactivate this game object and create an explosion effect
  void Explode();

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Recieves and handles events
  void HandleEvent(Event evt);
};

