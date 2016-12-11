
//Title     : MissileLauncher.cpp
//Purpose   : MissileLauncher Implementation.
//Author    : Matthew Peers
//Date      : 05/12/16

#include "MissileLauncher.h"
#include "Explosion.h"
#include "gamecode.h"
#include "SoundFX.h"
#include "ParticleEmitter.h"
#include "EnemyCollection.h"
#include "Missile.h"

MissileLauncher::MissileLauncher()
{
  // Load the missile launcher graphics
  LoadImage(L"images/enemies/missilelauncher.png");
  LoadImage(L"images/enemies/missilelauncher_hurt.png");

} // MissileLauncher end

void MissileLauncher::Initialise(Vector2D position, EnemyCollection *enemyCollection)
{
  m_position = position;
  m_imageScale = 3;
  m_objectSize = Vector2D(80, 80)*m_imageScale;
  m_health = 6;
  m_imageNumber = 0;
  m_pEnemyCollection = enemyCollection;
  m_missileCooldown = 0.4f;
  m_siloFireCount = 3;
  m_siloCooldown = 0.0f;

} // Initialise end

void MissileLauncher::Update(float deltaTime)
{
  // Reduce cooldowns by deltaTime
  m_missileCooldown -= deltaTime;
  m_siloCooldown -= deltaTime;

  // Test if the launcher can fire a volley
  if (m_siloFireCount > 0 && m_siloCooldown <= 0)
  {
    // Test if the launcher can fire a single missile (player needs to be in range)
    if (m_missileCooldown <= 0 && m_position.XValue - Game::instance.GetPlayer()->GetPosition().XValue < 2000 
        && m_position.XValue - Game::instance.GetPlayer()->GetPosition().XValue > 0)
    {
      Missile *pMissile = new Missile;
      pMissile->Initialise(0, m_position);
      Game::instance.m_objects.AddItem(pMissile, true);

      m_siloFireCount--;
      m_missileCooldown = 0.4f;

      if (m_siloFireCount <= 0)
      {
        m_siloFireCount = 3;
        m_siloCooldown = 3.0f;
      }
    }
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

} // Update end