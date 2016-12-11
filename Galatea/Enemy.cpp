
//Title     : Enemy.cpp
//Purpose   : Enemy Implementation.
//Author    : Matthew Peers
//Date      : 05/12/16

#include "Enemy.h"
#include "Explosion.h"
#include "gamecode.h"
#include "SoundFX.h"
#include "ParticleEmitter.h"

Enemy::Enemy() : GameObject(ENEMY)
{
  // All enemies will need to handle events
  m_handleEvents = true;

} // Enemy end

void Enemy::ProcessCollision(GameObject &other)
{
  // If the enemy collides with the ship the enemy should die instantly
	if (other.GetType() == SHIP)
	{
		m_health = 0;
	}

  // If the players bullet hits an enemy reduce its health and show a damage frame
	else if (other.GetType() == BULLET)
	{
		m_health--;
		m_imageNumber = 1;
		m_hurtTimer = 0.05f;
	}

} // ProcessCollision end

void Enemy::HandleEvent(Event evt)
{
  // Deactivate if the player is destroyed
  if (evt.type == EVENT_PLAYERDESTROYED)
  {
    m_active = false;
  }

} // HandleEvent end

void Enemy::Explode()
{

  // Create an explosion when the enemy dies
	Explosion *pExplosion = new Explosion;
	pExplosion->Initialise(m_position, Vector2D(0, 0), 0.3f);
	Game::instance.m_objects.AddItem(pExplosion, false);

  // Create a red particle effect when the enemy explodes
	Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 1000, (rand() % 10) + 8, 0.5f, MyDrawEngine::DARKRED), false);

  // Play an explosion sound
	SoundFX::instance.PlayExplosion();

  //Create explode event
  Event evt;
  evt.type = EVENT_ENEMYDESTROYED;
  Game::instance.NotifyEvent(evt);

  // Deactivate the enemy
	m_active = false;

} // Explode end

IShape2D& Enemy::GetCollisionShape()
{
  // Position the collision box based on the object position and size
  collisionShape.PlaceAt(m_position.YValue + (m_objectSize.YValue / 2), m_position.XValue - (m_objectSize.XValue / 2), 
                         m_position.YValue - (m_objectSize.YValue / 2), m_position.XValue + (m_objectSize.XValue / 2));
  return collisionShape;

} // GetCollisionShape end