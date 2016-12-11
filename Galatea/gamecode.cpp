// GameCode.cpp		


// Version  13.03	Draw Engine no longer requires a height / width
// Version 13.0   Update to wchar_t and wstring

//Version 11			5/3/08	
// These three functions form the basis of a game loop in the window created in the
// wincode.cpp file

#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "ObjectManager.h"
#include "entities.h"
#include <time.h>

#include "GameManager.h"
#include "SoundFX.h"

ErrorType Game::Main()
// Called repeatedly - the game loop
{
	// Flip and clear the back buffer
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();	
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err;

	switch(m_currentState)
	{
	case MENU:

		err= MainMenu();

		break;
	case PAUSED:

		err = PauseMenu();
		break;
	case RUNNING:


		err= Update();
		break;
  case LEVELUP:
    err = LevelUp();
    break;

	case GAMEOVER:

		err = FAILURE;
	default:
		// Not a valid state
		err = FAILURE;
	}

  
	return err;
}

void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	case MENU:

		break;
	case PAUSED:

		break;
	case RUNNING:

		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	case MENU:

		break;
	case PAUSED:

		break;
	case RUNNING:

		break;
	}
}

ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
// Called once before entering game loop. 
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}

void Game::Shutdown()
// Called once before entering game loop. 
{
	m_objects.DeleteAllObjects();

	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}
// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************




ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu
  m_objects.DrawAll();
	MyDrawEngine::GetInstance()->WriteText(450,220, L"Paused", MyDrawEngine::WHITE, 1);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour, 1);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)
		{
			ChangeState(RUNNING);
		}
		if(m_menuOption ==1)
		{
			EndOfGame();
			ChangeState(MENU);
		}

	}

	return SUCCESS;
}

ErrorType Game::LevelUp()
{
  // Code for a basic pause menu
  m_objects.DrawAll();

  MyDrawEngine::GetInstance()->WriteText(900, 50, L"LEVEL UP!", MyDrawEngine::WHITE, 3);

  MyDrawEngine::GetInstance()->WriteText(900, 520, L"Select Upgrade", MyDrawEngine::WHITE, 2);

  MyInputs* pInputs = MyInputs::GetInstance();

  pInputs->SampleKeyboard();

  const int NUMOPTIONS = 5;
  wchar_t upgrades[5][50] = { L"SURVIVOR\nIncrease Max Health", L"MACHINE\nIncrease Fire Rate", L"KAMIKAZE\nReduce Collision Damage", L"TANKER\nIncrease Max Fuel", L"GUNNER\nIncrease Max Ammo" };

  static int optionOne = rand() % NUMOPTIONS;
  static int optionTwo = rand() % NUMOPTIONS;

  if (optionOne == optionTwo)
  {
    optionTwo++;

    if (optionTwo >= NUMOPTIONS)
    {
      optionTwo = 0;
    }
  }

  int colour = MyDrawEngine::DARKGREEN;
  if (m_menuOption == 0)
  {
    colour = MyDrawEngine::GREEN;
  }
  MyDrawEngine::GetInstance()->WriteText(300, 500, upgrades[optionOne], colour, 2);

  colour = MyDrawEngine::DARKGREEN;

  if (m_menuOption == 1)
  {
    colour = MyDrawEngine::GREEN;
  }
  MyDrawEngine::GetInstance()->WriteText(1300, 500, upgrades[optionTwo], colour, 2);

  if (pInputs->NewKeyPressed(DIK_LEFT))
  {
    m_menuOption--;
  }
  if (pInputs->NewKeyPressed(DIK_RIGHT))
  {
    m_menuOption++;
  }
  if (m_menuOption<0)
  {
    m_menuOption = 0;
  }
  else if (m_menuOption >= NUMOPTIONS)
  {
    m_menuOption = NUMOPTIONS - 1;
  }

  if (pInputs->NewKeyPressed(DIK_RETURN))
  {
    // APPLY UPGRADE
    int optionSelected;

    if (m_menuOption == 0)
    {
      optionSelected = optionOne;
    }
    else
    {
      optionSelected = optionTwo;
    }

    switch (optionSelected)
    {
    case 0: // Increase max health
      m_pPlayer->IncreseMaxHealth();
      break;
    case 1: // Increase fire rate
      m_pPlayer->ReduceBulletCooldown();
      break;
    case 2: // Reduce collision damage
      m_pPlayer->ReduceCollisionDamage();
      break;
    case 3: // Increase max fuel
      m_pPlayer->IncreaseMaxFuel();
      break;
    case 4: // Increase max ammo
      m_pPlayer->IncreaseMaxAmmo();
      break;
    default:
      break;
    }

    optionOne = rand() % NUMOPTIONS;
    optionTwo = rand() % NUMOPTIONS;

    if (optionOne == optionTwo)
    {
      optionTwo++;

      if (optionTwo >= NUMOPTIONS)
      {
        optionTwo = 0;
      }
    }

    //
    ChangeState(RUNNING);
  }

  return SUCCESS;
}

ErrorType Game::MainMenu()
{
	// Code for a basic main menu

  MyDrawEngine::GetInstance()->DrawAt(Vector2D(0, -100), MyDrawEngine::GetInstance()->LoadPicture(L"images/oldPaper.png"), 0.9f);

  MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(0, 0));

  float deltaTime = m_gt.mdFrameTime;

  // Draw credits
  //Fighter bomber Worksheet
  MyDrawEngine::GetInstance()->WriteText(1200, 600, L"Credits: ", MyDrawEngine::GetInstance()->DARKBLUE, 6);
  MyDrawEngine::GetInstance()->WriteText(1200, 600 + 30 * 1, L"Player Plane - Metalslug - spritebf.smackjeeves.com", MyDrawEngine::GetInstance()->DARKBLUE, 6);
  MyDrawEngine::GetInstance()->WriteText(1200, 600 + 30 * 2, L"Enemies - Metalslug - spriters-resource.com", MyDrawEngine::GetInstance()->DARKBLUE, 6);
  MyDrawEngine::GetInstance()->WriteText(1200, 600 + 30 * 3, L"Buildings - Santa Claus Express - spritedatabase.net", MyDrawEngine::GetInstance()->DARKBLUE, 6);
  MyDrawEngine::GetInstance()->WriteText(1200, 600 + 30 * 4, L"Background - Animated Pixel Wallpaper - wallpapersafari.com", MyDrawEngine::GetInstance()->DARKBLUE, 6);
  MyDrawEngine::GetInstance()->WriteText(1200, 600 + 30 * 5, L"Menu Background - Paper Texture - pixelmator.com", MyDrawEngine::GetInstance()->DARKBLUE, 6);
  MyDrawEngine::GetInstance()->WriteText(1200, 600 + 30 * 6, L"Thrust sound - freesound.org", MyDrawEngine::GetInstance()->DARKBLUE, 6);

	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][15] = {L"I accept", L"Go Fullscreen",L"Quit"};

	if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
	{
		wcscpy_s( options[1], 15, L"Go Windowed");
	}

	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
      colour = MyDrawEngine::DARKGREEN;
		}
		MyDrawEngine::GetInstance()->WriteText(600,400+70*i, options[i], colour, 1);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)
		{
			StartOfGame();
			ChangeState(RUNNING);
		}

		if(m_menuOption ==1)
		{
			if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
			{
				MyDrawEngine::GetInstance()->GoWindowed();
			}
			else
			{
				MyDrawEngine::GetInstance()->GoFullScreen();
			}
		}
		if(m_menuOption ==2)
		{
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}

ErrorType Game::StartOfGame()
{
	// Code to set up your game
  MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();
  SoundFX::instance.LoadSounds();

  m_gt.mark();
  m_gt.mark();

  srand(time(NULL));

  m_pGameManager = new GameManager;
  m_pGameManager->Initialise();
  m_objects.AddItem(m_pGameManager, false);

	return SUCCESS;
}

ErrorType Game::Update()
{
	m_objects.UpdateAll();
	m_objects.ProcessCollisions();
	m_objects.DrawAll();

  m_gt.mark();

  MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance();


	// Garbage collect any objects. Possibly slow
	m_objects.DeleteInactiveItems();

	// Check for entry to pause menu
	static bool escapepressed = true;
	if(KEYPRESSED(VK_ESCAPE))
	{
		if(!escapepressed)
			ChangeState(PAUSED);
		escapepressed=true;
	}
	else
		escapepressed=false;

	// Any code here to run the game,
	// but try to do this within a game object if possible

	return SUCCESS;
}

Ship* Game::GetPlayer()
{
  return m_pPlayer;
}

void Game::SetPlayer(Ship *ship)
{
  m_pPlayer = ship;
}

ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
	// Add code here to tidy up ********************************
	
	
	
	
	
	
	
	
	
	m_objects.DeleteAllObjects();

	return SUCCESS;
}

Game::Game()
{
	// No-op
}

Game::~Game()
{
	// No-op
}


void Game::NotifyEvent(Event evt)
{
	m_objects.HandleEvent(evt);
}

Game Game::instance;