
//Title     : Bomb.h
//Purpose   : Bomb header.
//Author    : Matthew Peers
//Date      : 05/12/16

#pragma once

#include "GameObject.h"

class Bomb : public GameObject
{
private:
  Rectangle2D collisionShape;   // Objects collision shape
  Vector2D m_velocity;          // The velocity of the bomb
  Vector2D m_imageSize;         // The size of the bomb graphic within the image file

  float m_speed;                // How fast the bomb should fall
public:

  // Constructor
  Bomb();

  // Set up the bomb
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

