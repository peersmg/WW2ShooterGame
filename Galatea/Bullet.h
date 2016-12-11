#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private:
  Rectangle2D collisionShape;   // Collision shape
  Vector2D m_velocity;          // Velocity of the bullet
  Vector2D m_gravity;           // Gravity to apply to the bullet
  Vector2D m_imageSize;         // Size of the bullet graphic in the image file

  float m_speed;                // Speed of the bullet

public:

  // Constructor
  Bullet();

  // Initialise the gameobject with default values
  void Initialise(float angle, Vector2D position, Vector2D gravity);

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

