//KANTERAKIS VASILEIOS-MARIOS p3230063
//MARINOS GEORGIOS p3230121

#include "sgg/graphics.h"
#include "GameState.h"


void draw() // method that draws game objects used in every class
{	
	GameState::getInstance()->draw();	
	
}

void update(float dt) // method used to change and update each game obejects state
{

	GameState::getInstance()->update(dt);
	
}


void init() // method used to initialize game objects
{

	GameState::getInstance()->init();

}


int main(int argc, char** argv)  // the game programm's main method
{
	graphics::createWindow(800, 800 , "puppet Basketball");

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(),
		GameState::getInstance()->getCanvasHeight());

	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();

	return 0;
}