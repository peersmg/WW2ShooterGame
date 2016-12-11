#include "Bomb.h"
#include "gamecode.h"
#include "Explosion.h"
#include "SoundFX.h"

Bomb::Bomb() : GameObject(BOMB)
{
  LoadImage(L"images/enemies/bomb.png");
  
} // Bomb end

void Bomb::Initialise(float angle, Vector2D position)
{
  m_angle = angle;
  m_position = position;
  m_speed = 700;
  m_handleEvents = true;

  // Set bearing and add 90 degrees to bullet angle
  m_velocity.setBearing(m_angle, m_speed); 

  m_imageScale = 3;
  m_imageSize = Vector2D(30, 30)*m_imageScale;
  m_objectSize = m_imageSize;

  m_velocity = Vector2D(100, 620);

} // Initialise end

void Bomb::ProcessCollision(GameObject &other)
{
  if (other.GetType() == BUILDING || other.GetType() == BULLET || other.GetType() == SHIP)
  {
    Explode();
  }
} // ProcessCollision end

void Bomb::Update(float deltaTime)
{
  m_position += -m_velocity*deltaTime;

  if (m_position.YValue < -1000)
  {
    Explode();
  }

} // Update end

IShape2D& Bomb::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_imageSize.YValue / 2), m_position.XValue - (m_imageSize.XValue / 2), 
                         m_position.YValue - (m_imageSize.YValue / 2), m_position.XValue + (m_imageSize.XValue / 2));
  return collisionShape;

} // GetCollisionShape end

void Bomb::HandleEvent(Event evt)
{
	if (evt.type == EVENT_PLAYERDESTROYED)
	{
		m_active = false;
	}

} // HandleEvent end

void Bomb::Explode()
{

  Explosion *pExplosion = new Explosion;
  pExplosion->Initialise(m_position, Vector2D(0, 0), 0.2f);
  Game::instance.m_objects.AddItem(pExplosion, false);

  SoundFX::instance.PlayExplosion();
  m_active = false;

} // Explode end