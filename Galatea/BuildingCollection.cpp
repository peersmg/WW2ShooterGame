#include "BuildingCollection.h"
#include "objecttypes.h"
#include "gamecode.h"

const float BuildingCollection::BUILDING_START = -3000;

BuildingCollection::BuildingCollection() : GameObject(MANAGER)
{
  m_pShip = nullptr;
} // BuildingCollection end

void BuildingCollection::Initialise(Ship *player)
{
  m_pShip = player;
  m_handleEvents = true;
  m_buildingsPassed = 0;

  m_firstBuildingIndex = 0;

  for (int i = 0; i < NUMBER_OF_BUILDINGS; i++)
  {
    if (i == 0)
    {
      m_pBuildings[i] = new Building;
      m_pBuildings[i]->Initialise(BUILDING_START, (rand() % 4) + 1);
      Game::instance.m_objects.AddItem(m_pBuildings[i], true);
    }
    else
    {
      m_pBuildings[i] = new Building;
      m_pBuildings[i]->Initialise(m_pBuildings[i - 1]->GetPosition().XValue + (m_pBuildings[i - 1]->GetSize().XValue) + (rand()%150), (rand() % 5));
      Game::instance.m_objects.AddItem(m_pBuildings[i], true);
    }
  }

  m_lastBuildingIndex = NUMBER_OF_BUILDINGS-1;
} // Initialise end

void BuildingCollection::Update(float deltaTime)
{
  if (m_pShip != nullptr)
  {
    if (m_pShip->GetPosition().XValue + BUILDING_START + -50 > m_pBuildings[m_firstBuildingIndex]->GetPosition().XValue)
    {
      // Move first building to end
      m_pBuildings[m_firstBuildingIndex]->SetPostion(m_pBuildings[m_lastBuildingIndex]->GetPosition().XValue + (m_pBuildings[m_lastBuildingIndex]->GetSize().XValue) + (rand() % 150));
      m_lastBuildingIndex = m_firstBuildingIndex;
      m_firstBuildingIndex = FindFirstBuilding();

      m_buildingsPassed++;
    }

    if (m_pShip->GetPosition().XValue - BUILDING_START + 50 < m_pBuildings[m_lastBuildingIndex]->GetPosition().XValue)
    {
      // Move first building to end
      m_pBuildings[m_lastBuildingIndex]->SetPostion(m_pBuildings[m_firstBuildingIndex]->GetPosition().XValue - (m_pBuildings[m_firstBuildingIndex]->GetSize().XValue) - (rand() % 150));
      m_firstBuildingIndex = m_lastBuildingIndex;
      m_lastBuildingIndex = FindLastBuilding();
      m_buildingsPassed--;
    }
  }
} // Update end

int BuildingCollection::GetBuildingsPassed()
{
  return m_buildingsPassed;
} // GetBuildingsPassed end

int BuildingCollection::FindLastBuilding()
{
  int highestX = m_pBuildings[0]->GetPosition().XValue;
  int highestIndex = 0;

  for (int i = 0; i < NUMBER_OF_BUILDINGS; i++)
  {
    if (m_pBuildings[i]->GetPosition().XValue > highestX)
    {
      highestX = m_pBuildings[i]->GetPosition().XValue;
      highestIndex = i;
    }
  }

  return highestIndex;
} // FindLastBuilding end

int BuildingCollection::FindFirstBuilding()
{
  int lowestX = m_pBuildings[0]->GetPosition().XValue;
  int lowestIndex = 0;

  for (int i = 0; i < NUMBER_OF_BUILDINGS; i++)
  {
    if (m_pBuildings[i]->GetPosition().XValue < lowestX)
    {
      lowestX = m_pBuildings[i]->GetPosition().XValue;
      lowestIndex = i;
    }
  }

  return lowestIndex;
} // FindFirstBuilding end

Building* BuildingCollection::GetOffscreenBuilding()
{
  Building *pBuilding = nullptr;

  for (int i = 0; i < NUMBER_OF_BUILDINGS; i++)
  {
    if (m_pBuildings[i] != nullptr)
    {
      if (m_pBuildings[i]->GetPosition().XValue > MyDrawEngine::GetInstance()->GetViewport().GetTopRight().XValue + 100)
      {
        pBuilding = m_pBuildings[i];
        break;
      }
    }
  }

  return pBuilding;

} // GetOffscreenBuilding end

void BuildingCollection::HandleEvent(Event evt)
{
  if (evt.type == EVENT_PLAYERDESTROYED)
  {
    GameOver();
  }
  else if (evt.type == EVENT_PLAYERGONE)
  {
    m_pShip = nullptr;
  }
} // HandleEvent end

void BuildingCollection::GameOver()
{
  for (int i = 0; i < NUMBER_OF_BUILDINGS; i++)
  {
    m_pBuildings[i]->Deactivate();
  }
} // GameOver end

IShape2D& BuildingCollection::GetCollisionShape()
{
  return collisionShape;

} // GetCollisionShape end

void BuildingCollection::Draw()
{
}

void BuildingCollection::ProcessCollision(GameObject &other)
{
}