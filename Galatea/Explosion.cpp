#include "Explosion.h"
#include "gamecode.h"
#include "ParticleEmitter.h"

Explosion::Explosion() : GameObject(EXPLOSION)
{
  LoadImage(L"images/explosion/explosion00.png");
  LoadImage(L"images/explosion/explosion01.png");
  LoadImage(L"images/explosion/explosion02.png");
  LoadImage(L"images/explosion/explosion03.png");
  LoadImage(L"images/explosion/explosion04.png");
  LoadImage(L"images/explosion/explosion05.png");
  LoadImage(L"images/explosion/explosion06.png");
  LoadImage(L"images/explosion/explosion07.png");
  LoadImage(L"images/explosion/explosion08.png");

} // Explosion end

void Explosion::Initialise(Vector2D position, Vector2D velocity, float scale, float animationSpeed, bool playerExplosion)
{
  m_position = position;
  m_velocity = velocity;

  m_imageScale = scale;
  m_animationSpeed = animationSpeed;
  m_animationPos = 0;
  m_playerExplosion = playerExplosion;

  m_drawDepth = -2;

} // Initialise end

void Explosion::Update(float deltaTime)
{
  m_animationPos += m_animationSpeed*deltaTime;

  if (m_imageScale > 0)
  {
    m_imageScale -= 0.2f*deltaTime;
  }

  if (m_animationPos <= 8)
  {
    m_imageNumber = (int)m_animationPos;

  }
  else
  {
    if (m_playerExplosion)
    {
      Event evt;
      evt.type = EVENT_PLAYERDESTROYED;
      Game::instance.NotifyEvent(evt);
    }

    m_active = false;
  }

  m_position += m_velocity*deltaTime;

} // Update end

IShape2D& Explosion::GetCollisionShape()
{
  return collisionShape;

} // GetCollisionShape end

void Explosion::HandleEvent(Event evt)
{
}

void Explosion::ProcessCollision(GameObject &other)
{
}