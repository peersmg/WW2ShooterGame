#pragma once

#include "GameObject.h"
#include "Particle.h"

class ParticleEmitter : public GameObject
{
private:
  Rectangle2D collisionShape;     // The collision shape
  int m_particleForce;            // How fast the particles shoot out
  int m_numParticles;             // The number of particles to fire
  float m_particleLifetime;       // How long the fired particles should live for
  int m_particleColor;            // The color of the particles
  bool m_particlesAlive;          // Are there any particles left
  float m_particleRadius;         // The size of the particles

  Particle *m_pParticles;         // Array of particles

public:

  // Constructor
  ParticleEmitter(Vector2D position, int force);
  ParticleEmitter(Vector2D position, int force, int amount, float lifetime, int color);
  ParticleEmitter(Vector2D position, int force, int amount, float lifetime, int color, float radius);

  // Initialise the gameobject with default values
  void Initialise(Vector2D position, int force, int amount, float lifetime, int color, float radius = 5);

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Update the gameojects graphics
  void Draw();

  // Removes all the particles emmited
  void DeleteParticles();

  // Calculate the velocity of a fired particle
  Vector2D CalculateVelocity();

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Recieves and handles events
  void HandleEvent(Event evt);
};

