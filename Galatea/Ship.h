#pragma once

#include "GameObject.h"

class Ship : public GameObject
{
private:
  Rectangle2D collisionShape;   // Shape of the collision
  Vector2D m_velocity;          // Velocity of the ship
  Vector2D m_acceleration;      // Ship Acceleration
  Vector2D m_gravity;           // Gravity

  Vector2D m_imageSize;         // Size of the ship graphic within the image file

  float m_friction;             // How much friction to apply to the ship
  float m_thrust;               // The upwards thrust of the ship
  float m_thrustSuper;          // The forwards thrust of the ship
  float m_trailSize;            // Size of the engine trail
  float m_velocityLimit;        // The maximum velocity of the ship

  float m_maxHealth;            // Ship max health
  float m_maxAmmo;              // Ship max ammo
  float m_maxFuel;              // Ship max fuel
  float m_maxBulletCooldown;    // Ship max bullet cooldown

  float m_collisionDamage;      // How much damage the ship should take when colliding with a object
  float m_health;               // Ship health
  float m_fuel;                 // Ship fuel
  float m_ammo;                 // Ship ammo
  float m_bulletCooldown;       // Ship bullet cooldown

  bool m_superThrust;           // Is the ship thrusting upwards
  bool m_landed;                // Has the ship landed on a building

public:

  // Constructor
  Ship();

  // Increases the max health of the player
  void IncreseMaxHealth();

  // Increase the maximum ammo
  void IncreaseMaxAmmo();

  // Increase the max fuel
  void IncreaseMaxFuel();

  // Reduces the cooldown between bullet shots
  void ReduceBulletCooldown();

  // Reduces the damage taken by the player when colliding with objects
  void ReduceCollisionDamage();

  // Initialise the gameobject with default values
  void Initialise(Vector2D startPos);

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Deactivate this game object and create an explosion effect
  void Explode();

  // What to do when the player collides with a building
  void HitBuilding(GameObject &other);

  // Rotate the player to a given angle
  void RotateTo(float angle);

  // Return the ships health
  int GetHealth();
   
  // Returns the ships fuel
  int GetFuel();

  // Returns the ships ammo
  int GetAmmo();

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Recieves and handles events
  void HandleEvent(Event evt);
};

