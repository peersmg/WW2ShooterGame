#include "EnemyCollection.h"
#include "BulletEnemy.h"
#include "MissileEnemy.h"
#include "MissileLauncher.h"
#include "gamecode.h"
#include "Building.h"

EnemyCollection::EnemyCollection() : GameObject(MANAGER)
{
}

void EnemyCollection::Initialise(BuildingCollection *buildingCollection)
{
  m_currentEnemyCount = 0;
  m_spawnCooldown = 1;
  m_pBuildingCollection = buildingCollection;
  m_maxEnemies = 2;
  m_handleEvents = true;

  for (int i = 0; i < m_maxEnemies; i++)
  {
    m_pEnemies[i] = nullptr;
  }

} // Initialise end

void EnemyCollection::Update(float deltaTime)
{ 
  if (m_spawnCooldown > 0)
  {
    m_spawnCooldown -= deltaTime;
  }
  else if (m_currentEnemyCount < m_maxEnemies)
  {
    // Spawn enemy

    Building* pBuilding = m_pBuildingCollection->GetOffscreenBuilding();

    for (int i = 0; i < m_maxEnemies; i++)
    {
      if (m_pEnemies[i] == nullptr)
      {
        if (rand() % 150 < 50)
        {
          m_pEnemies[i] = new BulletEnemy;
          m_pEnemies[i]->Initialise(Vector2D(MyDrawEngine::GetInstance()->GetViewport().GetTopRight().XValue + 100, rand() % 1000), this);
          Game::instance.m_objects.AddItem(m_pEnemies[i], true);
        }
        else if (rand() % 150 < 100)
        {
          m_pEnemies[i] = new MissileEnemy;
          m_pEnemies[i]->Initialise(Vector2D(MyDrawEngine::GetInstance()->GetViewport().GetTopRight().XValue + 100, (rand() % 400)+600), this);
          Game::instance.m_objects.AddItem(m_pEnemies[i], true);
        }
        else
        {
          if (pBuilding != nullptr)
          {
            m_pEnemies[i] = new MissileLauncher;

            m_pEnemies[i]->Initialise(Vector2D(pBuilding->GetPosition().XValue, pBuilding->GetPosition().YValue + (pBuilding->GetSize().YValue / 2) + ((80 * 3) / 2)), this);
            Game::instance.m_objects.AddItem(m_pEnemies[i], true);
          }
        }
        
        m_currentEnemyCount++;
        ResetCooldown();
        break;
      }
    }
  }
  else
  {
    ResetCooldown();
  }
  
} // Update end

void EnemyCollection::ResetCooldown()
{
 
  if (m_pBuildingCollection->GetBuildingsPassed() > 40)
  {
    m_maxEnemies = MAXENEMIES;
    m_spawnCooldown = ((rand() % 10) + 3.0f) / 10.0f;
  }
  else if (m_pBuildingCollection->GetBuildingsPassed() > 30)
  {
    m_maxEnemies = 15;
    m_spawnCooldown = ((rand() % 10) + 10.0f) / 10.0f;
  }
  else if (m_pBuildingCollection->GetBuildingsPassed() > 20)
  {
    m_maxEnemies = 10;
    m_spawnCooldown = ((rand() % 20) + 10.0f) / 10.0f;
  }
  else if (m_pBuildingCollection->GetBuildingsPassed() > 10)
  {
    m_maxEnemies = 5;
    m_spawnCooldown = ((rand() % 30) + 10.0f) / 10.0f;
  }
  else
  {
    m_maxEnemies = 2;
    m_spawnCooldown = ((rand()%40)+20.0f)/10.0f;
  }

} // ResetCooldown end

void EnemyCollection::RemoveEnemy(Enemy *enemy)
{
  for (int i = 0; i < m_maxEnemies; i++)
  {
    if (m_pEnemies[i] == enemy)
    {
      m_pEnemies[i]->Explode();
      m_pEnemies[i] = nullptr;
      m_currentEnemyCount--;
    }
  }

} // RemoveEnemy end

void EnemyCollection::DeactivateEnemy(Enemy *enemy)
{
  for (int i = 0; i < m_maxEnemies; i++)
  {
    if (m_pEnemies[i] == enemy)
    {
      m_pEnemies[i]->Deactivate();
      m_pEnemies[i] = nullptr;
      m_currentEnemyCount--;
    }
  }

} // DeactivateEnemy end

void EnemyCollection::HandleEvent(Event evt)
{
  if (evt.type == EVENT_PLAYERDESTROYED)
  {
    // Loop through and delete enemies
    for (int i = 0; i < m_maxEnemies; i++)
    {
      if (m_pEnemies[i])
      {
        m_pEnemies[i]->Deactivate();
        m_pEnemies[i] = nullptr;
        m_currentEnemyCount--;
      }
    }

    m_active = false;
  }

} // HandleEvent end



void EnemyCollection::Draw()
{
}

IShape2D& EnemyCollection::GetCollisionShape()
{
  return collisionShape;
}

void EnemyCollection::ProcessCollision(GameObject &other)
{
}