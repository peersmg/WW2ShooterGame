#include "Missile.h"
#include "gamecode.h"
#include "Explosion.h"
#include "SoundFX.h"
#include "ParticleEmitter.h"

Missile::Missile() : GameObject(MISSILE)
{

}

void Missile::Initialise(float angle, Vector2D position)
{
  m_angle = angle;
  m_position = position;
  m_speed = 700;
  m_handleEvents = true;

  m_velocity.setBearing(m_angle, m_speed); // Set bearing and add 90 degrees to bullet angle

  m_imageScale = 2;
  m_imageSize = Vector2D(56, 16)*m_imageScale;
  m_objectSize = m_imageSize;

  LoadImage(L"images/enemies/missile_silo.png");

} // Initialise end

void Missile::ProcessCollision(GameObject &other)
{
  if (other.GetType() == BUILDING || other.GetType() == BULLET || other.GetType() == SHIP || other.GetType() == MISSILE)
  {
    Explode();
  }

} // ProcessCollision end

void Missile::Update(float deltaTime)
{
  m_angle = (m_position - Game::instance.GetPlayer()->GetPosition()).angle() + 1.57;

  m_velocity.setBearing(m_angle-1.57, m_speed);

  m_position += -m_velocity*deltaTime;

  if (m_position.YValue < -1000)
  {
    Explode();
  }

  Vector2D offset = Vector2D(-50, -5);

  if (rand() % 100 < 90)
  {
	  Explosion *pExplosion = new Explosion;
    pExplosion->Initialise(m_position + offset.rotatedBy(-m_angle), Vector2D(0, 0), 0.03f);
	  Game::instance.m_objects.AddItem(pExplosion, false);
  }
  
} // Update end

IShape2D& Missile::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_imageSize.YValue / 2), m_position.XValue - (m_imageSize.XValue / 2), m_position.YValue - (m_imageSize.YValue / 2), m_position.XValue + (m_imageSize.XValue / 2));
  return collisionShape;

} // GetCollisionShape end

void Missile::HandleEvent(Event evt)
{
  if (evt.type == EVENT_PLAYERDESTROYED)
  {
    m_active = false;
  }

} // HandleEvent end

void Missile::Explode()
{

  Explosion *pExplosion = new Explosion;
  pExplosion->Initialise(m_position, Vector2D(0, 0), 0.2f);
  Game::instance.m_objects.AddItem(pExplosion, false);

  Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 500, (rand() % 6) + 4, 0.3f, MyDrawEngine::DARKRED, 3), false);

  SoundFX::instance.PlayExplosion();
  m_active = false;

}  // Explode end