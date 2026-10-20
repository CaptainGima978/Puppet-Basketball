#pragma once
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "Timer.h"


class Ball;

class Player : public GameObject, public Box    /*inherits*/
{
	graphics::Brush m_brush_player;
	float m_pos_x, m_pos_y, m_velocity_x, m_velocity_y;
	bool m_on_land = true;     //for jumping
	Ball* m_heldBall = nullptr; //ball pointer used in catchBall and more methods related to the ball
	int stealkey;
	Player* opponent;  //for player colisions
	Timer m_shoot_timer = Timer(0.9f, Timer::TIMER_ONCE); // for  shoot button
  
	bool is_shoot_key_pressed = false;
	float charge_duration;
 	bool m_shoot_key_held = false; 
	
	

public:
	std::string texture = "";

	Player(const std::string name)  //Constructor
		:GameObject(name),m_pos_x(0.0f), m_pos_y(0.0f), m_velocity_x(10.0f), m_velocity_y(0.0f)
		 {}
	
	

	float getPositionX() const {  //returns position
		return m_pos_x;
	}

	float getPositionY() const {
		return m_pos_y;
	}
	void setPlayerPosition(float x, float y) {  //sets position
		m_pos_x = x;
		m_pos_y = y;
	}

	
	
	float getVelocityX() const { return m_velocity_x; }  //gets velocity 

	float getVelocityY() const { return m_velocity_y; }

	float distanceTo(Player* opponent);   //used for colisions with players and the ball 

	bool hasBall() const;   
	bool checkCrash(Ball* ball);
	bool checkCrash(Player* opponent);
	bool catchBall(float ball_pos_x, float ball_pos_y);
	
	void releaseBall();  //methods realised in cpp file 
	void catchBall(Ball* ball);
	void attemptSteal(Player* opponent);
	void shootBall();
		
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	
};
