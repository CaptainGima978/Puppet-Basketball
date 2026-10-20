#pragma once
#include "GameObject.h"
#include "Box.h"
#include "Ball.h"
#include "sgg/graphics.h"
class bkgnd : public GameObject  /*inherits*/
{
	graphics::Brush m_brush_bkgnd;
	graphics::Brush textBrush;
	graphics::Brush winBrush;
	
	
	float m_center_x = 5.0f;   //set's up necessary values
	float m_center_y = 5.0f;

	std::vector<GameObject*> m_static_object;
	

public:
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	
	
	bkgnd(const std::string& name = "background");
	~bkgnd();

};