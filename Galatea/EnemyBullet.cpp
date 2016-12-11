#include "EnemyBullet.h"
#include "gamecode.h"
#include "ParticleEmitter.h"

EnemyBullet::EnemyBullet() : GameObject(ENEMYBULLET)
{
  // Load the bullet graphic
  LoadImage(L"images/bullet.png");
}

void EnemyBullet::Initialise(float angle, Vector2D position, Vector2D gravity)
{
  m_angle = angle;
  m_position = position;
  m_speed = 2000.0f;
  m_gravity = gravity;
  m_drawDepth = 100;
  m_handleEvents = true;

  m_velocity.setBearing(m_angle, m_speed); // Set bearing and add 90 degrees to bullet angle

  m_imageScale = 2;
  m_imageSize = Vector2D(8, 8)*m_imageScale;
  m_objectSize = m_imageSize;
}

void EnemyBullet::ProcessCollision(GameObject &other)
{
  if (other.GetType() == BUILDING || other.GetType() == SHIP)
  {
    Explode();
  }
}

void EnemyBullet::Update(float deltaTime)
{
  m_velocity += m_gravity*deltaTime;
  m_position += m_velocity*deltaTime;

  if (m_position.YValue < -1000)
  {
    Explode();
  }
}

IShape2D& EnemyBullet::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_imageSize.YValue / 2), m_position.XValue - (m_imageSize.XValue / 2), m_position.YValue - (m_imageSize.YValue / 2), m_position.XValue + (m_imageSize.XValue / 2));
  return collisionShape;
}

void EnemyBullet::HandleEvent(Event evt)
{
  if (evt.type == EVENT_PLAYERDESTROYED)
  {
    m_active = false;
  }
}

void EnemyBullet::Explode()
{
  Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 500, (rand() % 6) + 4, 0.3f, MyDrawEngine::DARKGREEN, 2), false);
  m_active = false;
}