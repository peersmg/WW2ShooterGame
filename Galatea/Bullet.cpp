#include "Bullet.h"
#include "ParticleEmitter.h"
#include "gamecode.h"

Bullet::Bullet() : GameObject(BULLET)
{
}

void Bullet::Initialise(float angle, Vector2D position, Vector2D gravity)
{
  m_angle = angle;                 
  m_position = position;
  m_speed = 2000.0f;
  m_gravity = gravity;

  // Set bearing and add 90 degrees to bullet angle
  m_velocity.setBearing(m_angle + 1.5708f, m_speed); 
  
  m_imageScale = 2;
  m_imageSize = Vector2D(8, 8)*m_imageScale;
  m_objectSize = m_imageSize;

  LoadImage(L"images/bullet.png");

} // Initialise end

void Bullet::ProcessCollision(GameObject &other)
{
  if (other.GetType() == BUILDING || other.GetType() == ENEMY)
  {
    Explode();
  }

} // ProcessCollision end

void Bullet::Update(float deltaTime)
{
  m_velocity += m_gravity*deltaTime;
  m_position += m_velocity*deltaTime;

  if (m_position.YValue < -1000)
  {
    Explode();
  }

} // Update end

IShape2D& Bullet::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_imageSize.YValue / 2), m_position.XValue - (m_imageSize.XValue / 2), 
                         m_position.YValue - (m_imageSize.YValue / 2), m_position.XValue + (m_imageSize.XValue / 2));
  return collisionShape;

} // GetCollisionShape end

void Bullet::Explode()
{
  Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 500, (rand() % 6) + 4, 0.3f, MyDrawEngine::DARKGREEN, 2), false);
  m_active = false;
}

void Bullet::HandleEvent(Event evt)
{
}