#include "Building.h"


Building::Building() : GameObject(BUILDING)
{
  LoadImage(L"images/buildings/building1.png");
  LoadImage(L"images/buildings/building2.png");
  LoadImage(L"images/buildings/building3.png");
  LoadImage(L"images/buildings/building4.png");
  LoadImage(L"images/buildings/fuel.png");
}

void Building::Initialise(int startX, int buildingType)
{
  MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();

  m_buildingType = buildingType;
  m_refuelBuilding = false;

  // Replace with switch

  switch (m_buildingType)
  {
  case 0:
    m_imageScale = 5;
    m_objectSize = Vector2D(118, 80)*m_imageScale;
    break;
  case 1:
    m_imageScale = 5;
    m_objectSize = Vector2D(117, 55)*m_imageScale;  
    break;
  case 2:
    m_imageScale = 5;
    m_objectSize = Vector2D(121, 107)*m_imageScale;
    break;
  case 3:
    m_imageScale = 5;
    m_objectSize = Vector2D(120, 132)*m_imageScale;
    break;
  case 4:
    m_imageScale = 5;
    m_objectSize = Vector2D(120, 132)*m_imageScale;
    m_refuelBuilding = true;
    break;
  default:
    break;
  }

  m_position = Vector2D(startX, -pDrawEngine->GetScreenHeight() + (m_objectSize.YValue / 2));
} // Initialise end

void Building::Draw()
{
  MyDrawEngine *pDrawEngine = MyDrawEngine::GetInstance();

  switch (m_buildingType)
  {
  case 0:
    pDrawEngine->DrawAt(m_position, pDrawEngine->FindPicture(L"images/buildings/building1.png"), m_imageScale, m_angle);
    break;
  case 1:
    pDrawEngine->DrawAt(m_position, pDrawEngine->FindPicture(L"images/buildings/building2.png"), m_imageScale, m_angle);
    break;
  case 2:
    pDrawEngine->DrawAt(m_position, pDrawEngine->FindPicture(L"images/buildings/building3.png"), m_imageScale, m_angle);
    break;
  case 3:
    pDrawEngine->DrawAt(m_position, pDrawEngine->FindPicture(L"images/buildings/building4.png"), m_imageScale, m_angle);
    break;
  case 4:
    pDrawEngine->DrawAt(m_position, pDrawEngine->FindPicture(L"images/buildings/building4.png"), m_imageScale, m_angle);

    pDrawEngine->DrawAt(m_position+Vector2D(50,(m_objectSize.YValue/2)+50), 
                        pDrawEngine->FindPicture(L"images/buildings/fuel.png"), 4, m_angle);
    break;
  default:
    break;
  }

} // Draw end

bool Building::IsRefuel()
{
  return m_refuelBuilding;

} // IsRefuel end

void Building::SetPostion(float newXPosition)
{
  m_position.XValue = newXPosition;
  
} // SetPostion end

IShape2D& Building::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_objectSize.YValue / 2), m_position.XValue - (m_objectSize.XValue / 2), 
                         m_position.YValue - (m_objectSize.YValue / 2), m_position.XValue + (m_objectSize.XValue / 2));

  return collisionShape;
}


void Building::ProcessCollision(GameObject &other)
{
} 

Rectangle2D Building::GetShape()
{
  return collisionShape;
}


void Building::Update(float deltaTime)
{ 
}

void Building::HandleEvent(Event evt)
{
}