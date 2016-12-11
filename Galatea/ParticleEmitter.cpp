#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Vector2D position, int force) : GameObject(EMITTER)
{
  Initialise(position, force, 5, 2.0f, MyDrawEngine::GetInstance()->RED);
}

ParticleEmitter::ParticleEmitter(Vector2D position, int force, int amount, float lifetime, int color) : GameObject(EMITTER)
{
  Initialise(position, force, amount, lifetime, color);
}

ParticleEmitter::ParticleEmitter(Vector2D position, int force, int amount, float lifetime, int color, float radius) : GameObject(EMITTER)
{
  Initialise(position, force, amount, lifetime, color, radius);
}

void ParticleEmitter::Initialise(Vector2D position, int force, int amount, float lifetime, int color, float radius)
{
  m_particleRadius = radius;
  m_position = position;
  m_particleForce = force;
  m_numParticles = amount;
  m_particleLifetime = lifetime;
  m_particleColor = color;
  m_pParticles = nullptr;

  m_pParticles = new Particle[m_numParticles];

  for (int i = 0; i < m_numParticles; i++)
  {
    m_pParticles[i].Initialise(m_position, CalculateVelocity(), m_numParticles, m_particleLifetime - (((rand() % 1000) - 500.0f) / 1000.0f), m_particleColor, m_particleRadius);
  }

  m_particlesAlive = true;

} // Initialise end

void ParticleEmitter::Update(float deltaTime)
{
  bool tempAlive = false;
  if (m_particlesAlive)
  {
    for (int i = 0; i < m_numParticles; i++)
    {
      if (m_pParticles[i].GetAlive())
      {
        m_pParticles[i].Update(deltaTime);
        tempAlive = true;
      }
    }
  }
  else
  {
    DeleteParticles();
    m_active = false;
  }

  if (!tempAlive)
  {
    m_particlesAlive = false;
  }

} // Update end

void ParticleEmitter::Draw()
{
  if (m_particlesAlive)
  {
    for (int i = 0; i < m_numParticles; i++)
    {
      if (m_pParticles[i].GetAlive())
      {
        m_pParticles[i].Draw();
      }
    }
  }

} // Draw end

Vector2D ParticleEmitter::CalculateVelocity()
{
  Vector2D vel = Vector2D((rand() % (m_particleForce * 2)) - m_particleForce, (rand() % (m_particleForce * 2)) - m_particleForce);

  return vel;

} // CalculateVelocity end

void ParticleEmitter::DeleteParticles()
{
  delete[] m_pParticles;
  m_pParticles = nullptr;

} // DeleteParticles end

void ParticleEmitter::ProcessCollision(GameObject &other)
{}

IShape2D& ParticleEmitter::GetCollisionShape()
{
  return collisionShape;
}

void ParticleEmitter::HandleEvent(Event evt)
{
  if (evt.type == EVENT_PLAYERGONE)
  {
    DeleteParticles();
  }
}