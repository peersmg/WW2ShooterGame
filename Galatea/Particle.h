#pragma once
#include "GameObject.h"

class Particle
{
private:
  bool m_alive;         // Is the particle still alive
  float m_lifetime;     // How long the particle should stay alive for
  int m_color;          // Color of the particle
  float m_radius;       // Size of the particle
  Vector2D m_position;  // Position of the particle
  Vector2D m_velocity;  // Particle velocity

public:

  // Constructor
  Particle();

  // Destructor
  ~Particle();

  // Initialise the gameobject with default values
  void Initialise(Vector2D position, Vector2D velocity, int amount, float lifetime, int color, float radius);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Update the gameojects graphics
  void Draw();

  // Retuns whether or not the particle is alive
  bool GetAlive();
};

