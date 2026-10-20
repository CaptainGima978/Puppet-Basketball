#pragma once
#include <sgg/graphics.h>
#include "GameObject.h"
#include "box.h"
#include "Player.h"
#include "bkgnd.h"


class Ball : public GameObject, public Box      //Inherits
{
private:
	float m_ball_pos_x;   
	float m_ball_pos_y;
	float m_ball_radius;
	float m_ballvelocity_x;
	float m_ballvelocity_y;
    bool is_Grounded = false;
	


	graphics::Brush m_brush_ball;   


	Player* m_heldBy = nullptr;   


public:

	Ball( std::string name = "Ball");

	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	void setPosition(float x, float y) {    //Sets ball position used in caught ball or even after a poit is scored
		m_ball_pos_x = x;
		m_ball_pos_y = y;
	}

	void setVelocity(float vx, float vy) {   //Sets ball velocity  used after colisions or after the ball is shot
		m_ballvelocity_x = vx; 
	    m_ballvelocity_y = vy;
	}
	void release();    //used  after the ball is shot

	void setHeldBy(Player* player);   //sets player holding it

	float getRadius() const { return m_ball_radius; }   //returns ball's size

	float getPositionX() const {   // returns ball position
		return m_pos_x;
	}

	float getPositionY() const {
		return m_pos_y;
	}
	
	float getVelocityX() const { return m_ballvelocity_x; }  // returns ball velocity

	float getVelocityY()const { return m_ballvelocity_y; }
};  
