
//Title     : MissileEnemy.cpp
//Purpose   : MissileEnemy Implementation.
//Author    : Matthew Peers
//Date      : 05/12/16

#include "MissileEnemy.h"
#include "Explosion.h"
#include "gamecode.h"
#include "SoundFX.h"
#include "ParticleEmitter.h"
#include "Bomb.h"

MissileEnemy::MissileEnemy()
{
  // Load the bomber graphics
  LoadImage(L"images/enemies/missileship.png");
  LoadImage(L"images/enemies/missileship_hurt.png");

} // MissileEnemy end

void MissileEnemy::Initialise(Vector2D position, EnemyCollection *enemyCollection)
{
  m_position = position;
  m_imageScale = 3;
  m_objectSize = Vector2D(80, 43)*m_imageScale;
  m_health = 5;
  m_pEnemyCollection = enemyCollection;
  m_bombCooldown = 1.0f;

  m_velocity = Vector2D(-200, 0);

} // Initialise end

void MissileEnemy::Update(float deltaTime)
{

  m_bombCooldown -= deltaTime;

  // Test if a bomb can be fired (the player should be within range and in front of the player)
  if (m_bombCooldown <= 0 && m_position.XValue - Game::instance.GetPlayer()->GetPosition().XValue < 2000 && m_position.XValue - Game::instance.GetPlayer()->GetPosition().XValue > 0)
  {
    Bomb *pBomb = new Bomb;
    pBomb->Initialise(0, m_position);
    Game::instance.m_objects.AddItem(pBomb, true);

    m_bombCooldown = 1.0f;
  }

  // If the enemy is off the screen silently remove it
  if (m_position.XValue < MyDrawEngine::GetInstance()->GetViewport().GetTopLeft().XValue - 200)
  {
    m_pEnemyCollection->DeactivateEnemy(this);
  }

  // If the enemy runs out of health destroy it
  if (m_health <= 0)
  {
    m_pEnemyCollection->RemoveEnemy(this);
  }

  // Reduce the hurt timer by delta time
  if (m_hurtTimer > 0)
  {
    m_hurtTimer -= deltaTime;
  }
  else
  {
    m_imageNumber = 0;
  }

  // Create trail
  if (rand() % 100 < 90)
  {
    Explosion *pExplosion = new Explosion;
    pExplosion->Initialise(Vector2D(m_position.XValue+100, m_position.YValue), Vector2D(600, (rand() % 100) - 50), 0.05f);
    Game::instance.m_objects.AddItem(pExplosion, false);
  }

  // Update the position
  m_position += m_velocity*deltaTime;

} // Update end