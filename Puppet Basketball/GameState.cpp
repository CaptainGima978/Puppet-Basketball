#include "GameState.h"
#include "bkgnd.h"
#include "Player.h"
#include "Ball.h"
#include "baskteball_rims.h"


GameState::GameState()
{
}

void GameState::init()        //initialize all game objects
{
	m_bkgnd = new bkgnd();
	m_bkgnd->init();

	m_player1 = new Player("Giannis");
	m_player1->texture = "Giannis";
	m_player1->init();

	m_player2 = new Player("Wemby");
	m_player2->texture = "Wemby";
	m_player2->init();

	m_ball = new Ball();
	m_ball->init();

	m_basketball_rims = new basketball_rims();
	m_basketball_rims->init();



	graphics::preloadBitmaps(getAssetDir());
}

void GameState::draw()   //draw all game objects
{	


	m_bkgnd->draw();
	m_player1->draw();
	m_player2->draw();
	m_ball->draw();
	m_basketball_rims->draw();
}

void GameState::update(float dt)   //update all game objects
{

	m_player1->update(dt);
	m_player2->update(dt);
	m_bkgnd->update(dt);
	m_ball->update(dt);
	m_basketball_rims->update(dt);

	
	if (!m_player1->hasBall() && !m_player2->hasBall() &&  m_player1->checkCrash(m_ball)) {
		m_player1->catchBall(m_ball);
	}


	
	


	if (!m_player2->hasBall() && !m_player1->hasBall() &&  m_player2->checkCrash(m_ball)) {
		m_player2->catchBall(m_ball);
	}


	
	
	if (graphics::getKeyState(graphics::SCANCODE_E)) { 
		m_player1->attemptSteal(m_player2);
	}

	if (graphics::getKeyState(graphics::SCANCODE_RSHIFT)) { 
		m_player2->attemptSteal(m_player1);
	}


}

GameState* GameState::getInstance() // returns games current stage
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}

GameState::~GameState()  //destructor
{
	if (m_player1)
		delete m_player1;
	if (m_player2)
		delete m_player2;
	if (m_bkgnd)
		delete m_bkgnd;
	if (m_basketball_rims)
		delete m_basketball_rims;
}


std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}


GameState* GameState::m_unique_instance = nullptr;