#include "bkgnd.h"
#include "GameState.h"
#include "Player.h"
#include "Ball.h"
#include "box.h"
#include <sgg/graphics.h>




void bkgnd::update(float dt)  //get players to appear in front of the backround
{


	if (m_state->getPlayer1()->isActive())
		m_state->getPlayer1()->update(dt);

	if (m_state->getPlayer2()->isActive())
		m_state->getPlayer2()->update(dt);


	Ball* ball = m_state->getBall();  // ball to appear as well

	if (m_state->getPlayer1Score() >= 15) {

		graphics::playSound(m_state->getFullAssetPath("mixkit-basketball-buzzer-1647.mp3"), 1.0f);
		m_state->resetPlayer1Score();
		m_state->resetPlayer2Score();



	}
	if (m_state->getPlayer2Score() >= 15) {

		graphics::playSound(m_state->getFullAssetPath("mixkit-basketball-buzzer-1647.mp3"), 1.0f);
		m_state->resetPlayer1Score();
		m_state->resetPlayer2Score();


	}
	
}

void bkgnd::init()
{
    m_brush_bkgnd.outline_opacity = 0.0f;
    m_brush_bkgnd.texture = m_state->getFullAssetPath("basketball_court.png");  //load backround picture


	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	graphics::setFont(m_state->getFullAssetPath("CursedTimerUlil-Aznm.ttf"));

	graphics::playMusic(m_state->getFullAssetPath("bkgnd_song.mp3"), 0.1f, true,4000);


	
}

void bkgnd::draw()
{

	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float x = w / 2.0f;
	float y = h / 2.0f;


	graphics::drawRect(x, y, 2.5f * w, h, m_brush_bkgnd);



	if (m_state->getPlayer1()->isActive())
		m_state->getPlayer1()->draw();

	if (m_state->getPlayer2()->isActive())
		m_state->getPlayer2()->draw();

	graphics::Brush textBrush;

	char score1[40];                          //scoreboard
	sprintf_s(score1, "Player 1_Score: % d", m_state->getPlayer1Score());
	graphics::drawText(m_state->getCanvasWidth() / 12.0f, m_state->getCanvasHeight() / 12.0f, 0.3f, score1, textBrush);

	char score2[40];
	sprintf_s(score2, "Player 2_Score: % d", m_state->getPlayer2Score());

	graphics::drawText(m_state->getCanvasWidth() / 1.7f, m_state->getCanvasHeight() / 12.0f, 0.3f, score2, textBrush);

}




bkgnd::bkgnd(const std::string& name) 
    : GameObject(name) 
{}


bkgnd::~bkgnd()
{

}

