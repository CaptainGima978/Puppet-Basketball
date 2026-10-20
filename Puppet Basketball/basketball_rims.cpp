#include "baskteball_rims.h"
#include "GameState.h"
#include <sgg/graphics.h>
#include <iostream>


basketball_rims::basketball_rims(const std::string& name)
	:GameObject(name),m_center_x(4.0f),m_center_y(7.0f),m_width(2.0f),m_height(0.2f)
{}

basketball_rims::~basketball_rims()
{
}

void basketball_rims::init()
{
	m_brush_left.outline_opacity = 0.0f;
	m_brush_right.outline_opacity = 0.0f;

	m_brush_left.texture = m_state->getFullAssetPath("basketball_rim.png");   /*load designated picture on each basket*/
	m_brush_right.texture = m_state->getFullAssetPath("basketball_rim.png");

	float w = m_state->getCanvasWidth();    /*fix coordinates and size in accordance with the canvas*/
	float h = m_state->getCanvasHeight();

	m_width = w * 0.25f;
	m_height = h * 0.15f;
   
	m_left_x = m_width *0.3f;
	m_left_y = h * 0.38f;

	m_right_x = w-m_width * 0.3f;
	m_right_y = m_left_y;


	
}

void basketball_rims::update(float dt)
{
	m_rimBoxLeft = Box( 1.1f, 3.2f, 0.01f , 0.8f );    /*initialize boxes*/
	m_rimBoxRight = Box(6.9f, 3.2f, 0.01f, 0.8f );
	m_rimBoxULeft= Box( 1.1, 2.80f, 0.1f , 0.2f );
	m_rimBoxURight= Box(6.9f, 2.80f, 0.1f, 0.2f); 
	m_rimBoxDLeft= Box( m_left_x, 3.60f, 1.25f , 0.01f);
	m_rimBoxDRight= Box(m_right_x, 3.60f, 1.25f , 0.01f);
	m_rimBoxBLeft= Box( 0.15f, 2.80f, 0.1f , 0.2f );
	m_rimBoxBRight= Box(7.85f, 2.80f, 0.1f, 0.2f);
}

Box basketball_rims::getRimBoxLeft() const {     /*initialize getbox methodes*/
	return m_rimBoxLeft;
}

Box basketball_rims::getRimBoxRight() const {
	return m_rimBoxRight;
}
Box basketball_rims::getRimBoxULeft() const {
	return m_rimBoxULeft;
}

Box basketball_rims::getRimBoxURight() const {
	return m_rimBoxURight;
}
Box basketball_rims::getRimBoxDLeft() const {
	return m_rimBoxDLeft;
}

Box basketball_rims::getRimBoxDRight() const {
	return m_rimBoxDRight;
}
Box basketball_rims::getRimBoxBLeft() const {
	return m_rimBoxBLeft;
}

Box basketball_rims::getRimBoxBRight() const {
	return m_rimBoxBRight;
}


        
    


void basketball_rims::draw()
{		
	graphics::drawRect(m_left_x, m_left_y, m_width, m_height, m_brush_left); /*draw baskets */
	graphics::drawRect(m_right_x, m_right_y, m_width, m_height, m_brush_right);
	
}


	
	
