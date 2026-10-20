#pragma once

#include "GameObject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "Ball.h"

class basketball_rims : public GameObject, public Box /*inherits*/
{
private:
	graphics::Brush m_brush_left;
	graphics::Brush m_brush_right;
    

	float m_center_x;/*coordinates for the picture of each basket*/
	float m_center_y;
	float m_left_x;
	float m_left_y;
	float m_right_x;
	float m_right_y;
	float m_width;
	float m_height;

	Box m_rimBoxLeft;/*boxes for the rims*/
	Box m_rimBoxRight;
	Box m_rimBoxULeft;
	Box m_rimBoxURight;
	Box m_rimBoxDLeft;
	Box m_rimBoxDRight;
	Box m_rimBoxBLeft;
	Box m_rimBoxBRight;	

public:
	basketball_rims(const std::string& name = "basketball_rims"); /*Constructor*/
	~basketball_rims();   /*Destructor*/

	virtual void init() override;
	virtual void draw() override;
	virtual void update(float dt) override;

	Box getRimBoxLeft() const;/*Gets the correspondxing box (u=up,b=back,d=down)*/
	Box getRimBoxRight() const;
	Box getRimBoxULeft() const;
	Box getRimBoxURight() const;
	Box getRimBoxDLeft() const;
	Box getRimBoxDRight() const;
	Box getRimBoxBLeft() const;
	Box getRimBoxBRight() const;

};