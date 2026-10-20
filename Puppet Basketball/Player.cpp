#include "Player.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include <sgg/scancodes.h>
#include "Ball.h"
#include "timer.h"


void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;    // sets up variables necessary for player movement and jumping

	const float gravity = 300.0f;       

	const float jump = -70.0f;

	const float max_height_of_jump = m_state->getCanvasHeight() - 3.5f;
	

	Ball* ball = m_state->getBall();

	Player* opponent = m_state->getPlayer1();
	if (this == opponent) {
		opponent = m_state->getPlayer2();
	}
	checkCrash(opponent);


	if (texture == "Giannis") {        //assign keyboard buttons for each player's function
 

		if (graphics::getKeyState(graphics::SCANCODE_A)) // left-right movement,stealing , shooting and jumping
			m_pos_x -= m_velocity_x * delta_time;

		if (graphics::getKeyState(graphics::SCANCODE_D))
			m_pos_x += m_velocity_x * delta_time;
			
				
			
		if(graphics::getKeyState(graphics::SCANCODE_E))  
			attemptSteal(opponent);
		

	}
	else if (texture == "Wemby") {

		if (graphics::getKeyState(graphics::SCANCODE_LEFT)) 
				m_pos_x -= m_velocity_x * delta_time;
				

		if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) 
				m_pos_x += m_velocity_x * delta_time;
				
				
		



		if (graphics::getKeyState(graphics::SCANCODE_RSHIFT))
			attemptSteal(opponent);

	}

		if (m_on_land) {
			if (texture == "Giannis") {
				if (graphics::getKeyState(graphics::SCANCODE_W))
					m_velocity_y = jump;    // changes vertical velocity in order to take off from the ground
				m_on_land = false;


			}
			else if (texture == "Wemby") {
				if (graphics::getKeyState(graphics::SCANCODE_UP))
					m_velocity_y = jump;
				m_on_land = false;

			}
		}
		else {
			m_velocity_y += gravity * delta_time;   // overturns velocity so that the player lands
		}

		if (m_pos_y + m_velocity_y * delta_time < max_height_of_jump) {
			m_velocity_y = 0.0f;
		}

		m_pos_y += m_velocity_y * delta_time;


		if (m_pos_y >= m_state->getCanvasHeight() - 1.5f) {   
			m_pos_y = m_state->getCanvasHeight() - 1.0f;
			m_velocity_y = 0.0f;
			m_on_land = true;
		}


		 //checks limits so players don't go outide of the canva
		if (m_pos_x < 0.5f)
			m_pos_x = 0.5f;
		if (m_pos_x > m_state->getCanvasWidth() - 0.5f)
			m_pos_x = m_state->getCanvasWidth() - 0.5f;
		if (m_pos_y < 0.5f)
			m_pos_y = 0.5f;
		if (m_pos_y > m_state->getCanvasHeight() - 0.5f)
			m_pos_y = m_state->getCanvasHeight() - 0.5f;
		
	if (texture == "Giannis") {    
		if (m_pos_x <= 7.0f)  // can't shoot from certain positions to avoid scoring on player's own basket
        		is_shoot_key_pressed = graphics::getKeyState(graphics::SCANCODE_F);
	}
	else if (texture == "Wemby") {
		if (m_pos_x >= 1.0f){
			is_shoot_key_pressed = graphics::getKeyState(graphics::SCANCODE_SPACE);
		}
    }

    
    if (is_shoot_key_pressed) {  // shoot procedure using a timer in order to be able to adjust shot power
        if (!m_shoot_key_held) {   
            m_shoot_key_held = true;
            m_shoot_timer.start(); 
        }
    } else {
        if (m_shoot_key_held) {
            m_shoot_key_held = false;
			charge_duration = (float)m_shoot_timer;
			m_shoot_timer.stop();
             
            
			graphics::playSound(m_state->getFullAssetPath("male_grunt.mp3"), 0.5f); //shooting sound
            shootBall();

			
        }
    }

        


		checkCrash(ball);   //colision with ball checked and if true ball gets caught
		

		if (m_heldBall == nullptr && checkCrash(ball)) {
			catchBall(ball);
		}
		

		if (m_heldBall != nullptr) {  //sets caught ball's position according to the player's one
			m_heldBall->setPosition(this->getPositionX(), this->getPositionY() - 0.5f);
		}


		GameObject::update(dt);	
}
	void Player::init()
	{

		m_brush_player.fill_opacity = 1.0f;   //give corresponding picture to each player
		m_brush_player.outline_opacity = 0.0f;

		if (this->texture == "Giannis")
		{
			m_brush_player.texture = m_state->getFullAssetPath("giannis antentokoumpo.png");
			m_pos_x = 2.0f;
			m_pos_y = m_state->getCanvasHeight() - 1.0f;
			

		}
		else if (this->texture == "Wemby")
		{
			m_brush_player.texture = m_state->getFullAssetPath("victor wemby.png");
			m_pos_x = m_state->getCanvasWidth() - 2.0f;
			m_pos_y = m_state->getCanvasHeight() - 1.0f;
		
		   

		}
	}
	
	

	void Player::draw()
	{

		graphics::drawRect(m_pos_x,m_pos_y, 1.0f, 1.0f, m_brush_player);  // draw player 
		
	}
	//initialisation of each method
	void Player::catchBall(Ball* ball)  
	{
			
			if  (!hasBall()) { 
				m_heldBall = ball;
				ball->setHeldBy(this);
			}
		
	}

	bool Player::checkCrash(Ball* ball)  
	{
		if (!ball) return false;

		float center_x = m_pos_x + m_width / 2.0f;
		float center_y = m_pos_y + m_height / 2.0f;

		float distance_x = abs(center_x - ball->getPositionX());
		float distance_y = abs(center_y - ball->getPositionY());

		const float crash_boundary_x = (m_width / 2.0f + ball->getRadius());
		const float crash_boundary_y = (m_width / 2.0f + ball->getRadius());


		return (distance_x < crash_boundary_x && distance_y < crash_boundary_y);

	}
		

	bool Player::hasBall()const {
		return m_heldBall != nullptr;
	}
	
	void Player::shootBall() {
		if (m_heldBall != nullptr) {				

				float shoot_velocity_x;
				float shoot_velocity_y = -60.0f;
				m_heldBall->release();

				if (texture == "Giannis") {

					shoot_velocity_x = 25.0f *2.5 *  charge_duration ; 
				}

				else if (texture == "Wemby") {

					shoot_velocity_x = -25.0f* 2.5 * charge_duration ;

				}
				
				m_heldBall->setVelocity(shoot_velocity_x, shoot_velocity_y);

				
		}
		m_heldBall = nullptr;
	}

	    

	void Player::attemptSteal(Player* opponent) {

		if (this !=opponent) {
			if (checkCrash(opponent) && distanceTo(opponent) < 1.05f) {
				if (opponent->hasBall()) {
					opponent->releaseBall();
					catchBall(m_state->getBall());
					graphics::playSound(m_state->getFullAssetPath("shouting-yeah-7043.mp3"), 0.3f);
				}

			}
			
		}
	}

	bool Player::checkCrash(Player* opponent) {

		if (!opponent) return false;

		float distance_x = abs(m_pos_x - opponent->getPositionX());
		float distance_y = abs(m_pos_y - opponent->getPositionY());

		const float crash_boundary_x = (m_width + opponent->m_width) / 2.0f;
		const float crash_boundary_y = (m_height + opponent->m_height) / 2.0f;

		if (distance_x < crash_boundary_x && distance_y < crash_boundary_y) {

			float overlap_x = crash_boundary_x - distance_x;
			float overlap_y = crash_boundary_y - distance_y;

			if (distance_x > distance_y) {
				if (m_pos_x > opponent->m_pos_x) {
					m_pos_x += overlap_x / 2.0f;
					opponent->m_pos_x -= overlap_x / 2.0f;
				}
				else {
					m_pos_x -= overlap_x / 2.0f;
					opponent->m_pos_x += overlap_x / 2.0f;
				}
			}
			else {
				if (m_pos_y > opponent->m_pos_y) {
					m_pos_y += overlap_y / 2.0f;
					opponent->m_pos_y -= overlap_y / 2.0f;
				}
				else {
					m_pos_y -= overlap_y / 2.0f;
					opponent->m_pos_y += overlap_y / 2.0f;
				}
			}
			return true;
		}
		return true;
	}
		
	void Player::releaseBall() {
		if (m_heldBall) {
			m_heldBall->release();
			m_heldBall = nullptr;
		}
	}
	float Player::distanceTo(Player* opponent) {
		return sqrt(pow(m_pos_x - opponent->getPositionX(), 2) + pow(m_pos_y - opponent->getPositionY(), 2));
	}
	
	
	