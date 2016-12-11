#include "Particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Initialise(Vector2D position, Vector2D velocity, int amount, float lifetime, int color, float radius)
{
  m_alive = true;
  m_color = color;
  m_lifetime = lifetime;
  m_position = position;
  m_velocity = velocity;
  m_radius = radius;

} // Initialise end

void Particle::Update(float deltaTime)
{
  m_lifetime -= deltaTime;

  if (m_lifetime <= 0)
  {
    m_alive = false;
  }

  if (m_alive)
  {
    m_velocity += Vector2D(0, -320)*deltaTime;
    m_position += m_velocity*deltaTime;
  }

} // Update end

void Particle::Draw()
{
  MyDrawEngine *pDrawEngine = MyDrawEngine::GetInstance();

  pDrawEngine->FillCircle(m_position, m_radius, m_color);

} // Draw end

bool Particle::GetAlive()
{
  return m_alive;

} // GetAlive end