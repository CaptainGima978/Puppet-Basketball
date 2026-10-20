#pragma once
#include <string>
#include <sgg/graphics.h>


class GameState
{
private:
	std::string m_asset_path = "assets\\";  

	float m_canvas_width = 8.0f;
	float m_canvas_height = 8.0f;

	int m_player1_score = 0;
	int m_player2_score = 0;


	static GameState* m_unique_instance; //return a unique instance of the game

	GameState();

	class Player* m_player1 = 0;   //all game objects
	class Player* m_player2 = 0;
	class bkgnd* m_bkgnd = 0;
	class Ball* m_ball = 0;
	class basketball_rims* m_basketball_rims = 0;


public:

	bool m_debugging = false;

	void init();                
	void draw();
	void update(float dt);
	void incrementPlayer1Score() { m_player1_score++; }   //count scoring
	void incrementPlayer2Score() { m_player2_score++; }
	void resetPlayer1Score() {m_player1_score=0;}
	void resetPlayer2Score() {m_player2_score=0;}

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return m_canvas_width; }    //return canvas width/height used for coordinates and sizes
	float getCanvasHeight() { return m_canvas_height; } 

	int getPlayer1Score() const { return m_player1_score; }   //returns each player's score used in game loop ending
	int getPlayer2Score() const { return m_player2_score; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer1() { return m_player1; }
	class Player* getPlayer2() { return m_player2; }
	class Ball* getBall() { return m_ball; }
	class basketball_rims* getBasketballRims()  { return m_basketball_rims; }

	
};