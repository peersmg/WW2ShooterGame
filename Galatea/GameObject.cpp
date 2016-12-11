#include "GameObject.h"
#include "myinputs.h"


GameObject::GameObject(ObjectType type): TYPE(type)
{
	m_active=true;
	m_imageNumber = -1;
	m_imageScale=1.0;
	m_angle=0;
	m_handleEvents = false;
	m_drawDepth = 0;
  m_sceneNumber = 0;
}

int GameObject::GetDrawDepth() const
{
	return m_drawDepth;
}

Vector2D GameObject::GetPosition() const
{
  return m_position;
}

Vector2D GameObject::GetSize() const
{
  return m_objectSize;
}

GameObject::~GameObject()
{

}

void GameObject::HandleEvent(Event evt)
{
	// no-op
}

ObjectType GameObject::GetType() const
{
	return TYPE;
}

void GameObject::Deactivate()
{
	m_active = false;
}

void GameObject::LoadImage(wchar_t* filename)
{
	m_images.push_back( MyDrawEngine::GetInstance()->LoadPicture(filename));
	if(m_imageNumber<0)
		m_imageNumber=0;
}

bool GameObject::HasCollided( GameObject& otherObject) 
{
	return(    m_active && otherObject.m_active && GetCollisionShape().Intersects(otherObject.GetCollisionShape())    );
}

void GameObject::Draw()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();


	if(m_imageNumber>=0 && m_imageNumber<int(m_images.size())) 
	{
		pDE->DrawAt( m_position, m_images[m_imageNumber], m_imageScale, -m_angle);
	}
	else
	{
		pDE->WriteText(m_position, L"No image", pDE->LIGHTGREEN, 0);
	}
}

// Returns the number of the scene that this GameObject belongs to
int GameObject::GetSceneNumber() const
{
  return m_sceneNumber;
}

// Sets the scene number of the object. Only objects in the current scene will be drawn or updated.
void GameObject::SetSceneNumber(int sceneNumber)
{
  m_sceneNumber = sceneNumber;
}