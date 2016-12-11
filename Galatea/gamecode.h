//  *********************************************************************************
#pragma once
#include "errortype.h"
#include "windows.h"
#include "ObjectManager.h"
#include "event.h"
#include "Ship.h"
#include "objecttypes.h"
#include "GameManager.h"

// For reading keyboard
#define KEYPRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)




class Game
{
private:
  
	GameState m_currentState;
	
	int m_menuOption;
	Game();
	~Game();
	Game(Game& other);
  GameTimer m_gt;
  Ship *m_pPlayer;
  GameManager *m_pGameManager;

public:
	static Game instance;
	ObjectManager m_objects;
	ErrorType Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance);
	void Shutdown();
	ErrorType Main();
  Ship* GetPlayer();
  void SetPlayer(Ship *ship);

  void ChangeState(GameState newState);
  ErrorType LevelUp();
	ErrorType PauseMenu();
	ErrorType MainMenu();
	ErrorType StartOfGame();
	ErrorType Update();
	ErrorType EndOfGame();
	void NotifyEvent(Event evt);
};




