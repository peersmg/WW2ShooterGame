
//Title     : BulletEnemy.cpp
//Purpose   : BulletEnemy Implementation.
//Author    : Matthew Peers
//Date      : 05/12/16

#include "BulletEnemy.h"
#include "Explosion.h"
#include "gamecode.h"
#include "SoundFX.h"
#include "ParticleEmitter.h"
#include "EnemyBullet.h"

BulletEnemy::BulletEnemy()
{
  // Load gunship graphics
  LoadImage(L"images/enemies/gunship.png");
  LoadImage(L"images/enemies/gunship_hurt.png");
  LoadImage(L"images/enemies/gunship_turret.png");

} // BulletEnemy end

void BulletEnemy::Initialise(Vector2D position, EnemyCollection *enemyCollection)
{
  m_position = position;
  m_imageScale = 3;
  m_objectSize = Vector2D(80, 56)*m_imageScale;
  m_health = 5;
  m_pEnemyCollection = enemyCollection;
  m_hurtTimer = 0;
  m_drawDepth = 10;
  m_turretAngle = 0;
  m_angle = 0.2;

  m_velocity = Vector2D(-200, 0);

} // Initialise end

void BulletEnemy::Update(float deltaTime)
{
  MyDrawEngine *pTheDrawEngine = MyDrawEngine::GetInstance();

  m_bulletCooldown -= deltaTime;

  // Test if a bullet can be fired (the player should be within range)
  if (m_bulletCooldown <= 0 && m_position.XValue - Game::instance.GetPlayer()->GetPosition().XValue < 2000 
      && m_position.XValue - Game::instance.GetPlayer()->GetPosition().XValue > -2000)
  {
    EnemyBullet *pBullet = new EnemyBullet;
    pBullet->Initialise(-m_turretAngle+1.57, m_position, Vector2D(0, -320));
    Game::instance.m_objects.AddItem(pBullet, true);

    m_bulletCooldown = 0.3f;

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
    pExplosion->Initialise(Vector2D(m_position.XValue + 70, m_position.YValue - 30), 
                           Vector2D(600, (rand() % 100) - 50), 0.03f);
    Game::instance.m_objects.AddItem(pExplosion, false);

    Explosion *pExplosionTwo = new Explosion;
    pExplosionTwo->Initialise(Vector2D(m_position.XValue + 50, m_position.YValue - 50), 
                              Vector2D(600, (rand() % 100) - 50), 0.03f);
    Game::instance.m_objects.AddItem(pExplosionTwo, false);
  }
  
  // Set the angle of the turret
  m_turretAngle = -(m_position - Game::instance.GetPlayer()->GetPosition()).angle()-1.57;

  // Update the position
  m_position += m_velocity*deltaTime;

} // Update end

void BulletEnemy::Draw()
{
  MyDrawEngine *pTheDrawEngine = MyDrawEngine::GetInstance();

  // Draw the gnship and turret
  if (m_imageNumber == 0)
  {
    pTheDrawEngine->DrawAt(m_position, pTheDrawEngine->FindPicture(L"images/enemies/gunship.png"), 
                           m_imageScale, m_angle);
  }
  else
  {
    pTheDrawEngine->DrawAt(m_position, pTheDrawEngine->FindPicture(L"images/enemies/gunship_hurt.png"), 
                           m_imageScale, m_angle);
  }

  pTheDrawEngine->DrawAt(m_position, pTheDrawEngine->FindPicture(L"images/enemies/gunship_turret.png"), 
                         2, m_turretAngle);

} // Draw end