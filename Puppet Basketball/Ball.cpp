#include "Ball.h"
#include "GameState.h"
#include "Player.h"
#include "box.h"
#include "bkgnd.h"
#include "baskteball_rims.h"


Ball::Ball(std::string name) //constructor
    :GameObject(name), m_ball_pos_x(0.0f), m_ball_pos_y(0.0f), m_ball_radius(0.3f), m_ballvelocity_x(0.0f), m_ballvelocity_y(-60.0f)
{}



void Ball::update(float dt)    // sets up variables necessary for ball movement  
{
    float delta_time = dt / 1000.0f;

    const float gravity = 300.0f;

    const float friction = 0.7f;



    if (m_heldBy) {  // position changed to the player's one once ball is caught
        
        m_ball_pos_x = m_heldBy->getPositionX();
        m_ball_pos_y = m_heldBy->getPositionY() - 0.5f; 
        m_ballvelocity_x = 0.0f;
        m_ballvelocity_y = 0.0f;
        return;  
    }

    m_ballvelocity_y += gravity * delta_time;


    m_ball_pos_x += m_ballvelocity_x * delta_time;
    m_ball_pos_y += m_ballvelocity_y * delta_time;

    Box ballBox(m_ball_pos_x, m_ball_pos_y, m_ball_radius * 2, m_ball_radius * 2);   //ballbox for colisions

    Player* player1 = m_state->getPlayer1();
    Player* player2 = m_state->getPlayer2();


    if (player1 && player1->isActive()) {    //ball interction with player if not caught
        Box player1Box(player1->getPositionX(), player1->getPositionY(), 1.0f, 1.0f);
        if (ballBox.intersect(player1Box)) {           
                float comparablePosX = m_ball_pos_x - player1->getPositionX();
                float comparablePosY = m_ball_pos_y - player1->getPositionY();

                float angle = atan2(comparablePosY, comparablePosX);
                float speed = sqrt(m_ballvelocity_x * m_ballvelocity_x + m_ballvelocity_y * m_ballvelocity_y);

                m_ballvelocity_x = cos(angle) * speed * 1.5f;
                m_ballvelocity_y = sin(angle) * speed * 1.0f;

                m_ballvelocity_x = m_ballvelocity_x * friction;
                m_ballvelocity_y = m_ballvelocity_y * friction;


                player1->catchBall(this);

            
        }
    }

    if (player2 && player2->isActive()) {
        Box player2Box(player2->getPositionX(), player2->getPositionY(), 1.0f, 1.0f);
        if (ballBox.intersect(player2Box)) {
             
                float comparablePosX = m_ball_pos_x - player2->getPositionX();
                float comparablePosY = m_ball_pos_y - player2->getPositionY();

                float angle = atan2(comparablePosY, comparablePosX);
                float speed = sqrt(m_ballvelocity_x * m_ballvelocity_x + m_ballvelocity_y * m_ballvelocity_y);

                m_ballvelocity_x = cos(angle) * speed * 1.5f;
                m_ballvelocity_y = sin(angle) * speed * 1.0f;

                m_ballvelocity_x = m_ballvelocity_x * friction;
                m_ballvelocity_y = m_ballvelocity_y * friction;

                player2->catchBall(this);

        }
    }
    
    basketball_rims* rims = m_state->getBasketballRims();  //imports baskets 
    if (rims) {
        Box rimLeftBox = rims->getRimBoxLeft();
        Box rimRightBox = rims->getRimBoxRight();
        Box rimLeftUBox = rims->getRimBoxULeft();
        Box rimRightUBox = rims->getRimBoxURight();
        Box rimLeftDBox = rims->getRimBoxDLeft();
        Box rimRightDBox = rims->getRimBoxDRight();
        Box rimLeftBBox = rims->getRimBoxBLeft();
        Box rimRightBBox = rims->getRimBoxBRight();
        Box ballBox(m_ball_pos_x, m_ball_pos_y, m_ball_radius * 2, m_ball_radius * 2);

        if (ballBox.intersect(rimLeftBox)) { // fixes ball velocity after each colision with each part of each basket
                                            // and plays designated sound for ball colision
            m_ballvelocity_y = -m_ballvelocity_y ;

            m_ballvelocity_x = -m_ballvelocity_x ;
            graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);


        }
        else if (ballBox.intersect(rimRightBox)) {

            m_ballvelocity_y = -m_ballvelocity_y ;

            m_ballvelocity_x = -m_ballvelocity_x ;
            graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);


        }

        
            if (ballBox.intersect(rimLeftUBox)) {
                m_ballvelocity_y = -m_ballvelocity_y * friction;

                m_ballvelocity_x = -m_ballvelocity_x * friction;
               
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
                if ( m_ballvelocity_x <= 5.0f && m_ballvelocity_x >= -5.0f){
                    m_ballvelocity_x = -15.0f;
                }
            }
            else if (ballBox.intersect(rimRightUBox)) {

                m_ballvelocity_y = -m_ballvelocity_y * friction;

                m_ballvelocity_x = -m_ballvelocity_x * friction;

                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
                if ( m_ballvelocity_x <= 5.0f && m_ballvelocity_x >= -5.0f){
                    m_ballvelocity_x = 15.0f;
                }
            }
            if (ballBox.intersect(rimLeftDBox)) {
                if ( m_ballvelocity_y< 0.0f)
                    m_ballvelocity_y = 20.0f;
                else 
                    m_ballvelocity_y =-m_ballvelocity_y * friction ;

                m_ballvelocity_x = -m_ballvelocity_x * friction;

                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
            }
            else if (ballBox.intersect(rimRightDBox)) {

                if ( m_ballvelocity_y< 0.0f)
                    m_ballvelocity_y = 20.0f;
                else 
                    m_ballvelocity_y =-m_ballvelocity_y * friction ;

                m_ballvelocity_x = -m_ballvelocity_x * friction;
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
            }
            if (ballBox.intersect(rimLeftBBox)) {

                m_ballvelocity_y = -m_ballvelocity_y * friction;

                m_ballvelocity_x = -m_ballvelocity_x * friction;
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);

            }
            else if (ballBox.intersect(rimRightBBox)) {

                m_ballvelocity_y = -m_ballvelocity_y * friction;

                m_ballvelocity_x = -m_ballvelocity_x * friction;
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
            }
                //when a basket is scored , player score is incremented and designated sound is played

            if (m_ball_pos_x > 0.16f && m_ball_pos_x < 1.05f && m_ball_pos_y > 2.90f && m_ball_pos_y < 3.20f ) {
                m_state->incrementPlayer2Score();
                graphics::playSound(m_state->getFullAssetPath("crowd_cheering.mp3"), 0.2f);
                player2->setPlayerPosition(6.0f, m_state->getCanvasHeight() - 1.0f);
                player1->setPlayerPosition(2.0f, m_state->getCanvasHeight() - 1.0f);
                m_ball_pos_x = player1->getPositionX();
                m_ball_pos_y = player1->getPositionY();
            }


            if (m_ball_pos_x < 7.84f && m_ball_pos_x > 6.95f && m_ball_pos_y > 2.90f && m_ball_pos_y < 3.20f ) {        
                m_state->incrementPlayer1Score();
                graphics::playSound(m_state->getFullAssetPath("crowd_cheering.mp3"), 0.2f);
                player1->setPlayerPosition(2.0f, m_state->getCanvasHeight() - 1.0f);
                player2->setPlayerPosition(6.0f, m_state->getCanvasHeight() - 1.0f);
                m_ball_pos_x = player2->getPositionX();
                m_ball_pos_y = player2->getPositionY();

            }

                // when ball intersects with canvas edges changes direction and velocity in order to stay in and sound is played
            if (m_ball_pos_x < 0.5f) {
                m_ball_pos_x = 0.5f;
                m_ballvelocity_x = -m_ballvelocity_x * friction;
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
                
            }

            if (m_ball_pos_x > m_state->getCanvasWidth() - 0.5f) {
                m_ball_pos_x = m_state->getCanvasWidth() - 0.5f;
                m_ballvelocity_x = -m_ballvelocity_x * friction;
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
            }

            if (m_ball_pos_y < 0.5f ) {
                
                m_ball_pos_y = 0.5f;
                m_ballvelocity_y = -m_ballvelocity_y * friction;
                    
                    
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
            }
               
    }
        
        if (m_ball_pos_y <= m_state->getCanvasHeight() - 0.5 ){
            is_Grounded=false;
            
        }

        if (m_ball_pos_y > m_state->getCanvasHeight() - 0.5f) {
            m_ball_pos_y = m_state->getCanvasHeight() - 0.5f;
            m_ballvelocity_y = -m_ballvelocity_y * friction;
            if  (is_Grounded==false) {  //cheks if ball is constantly on the ground so that the sound is not played repetedly
                graphics::playSound(m_state->getFullAssetPath("basketball bouncing.mp3"), 1.0f);
                is_Grounded= true;
                 
            }
        }
     
    
}

void Ball::init()  //initialization and drawing of the ball
{
	m_brush_ball.fill_opacity = 1.0f;
	m_brush_ball.outline_opacity = 0.0f;

	m_brush_ball.texture = m_state->getFullAssetPath("basketball.png");

	m_ball_pos_x= m_state->getCanvasWidth() / 2.0f;
	m_ball_pos_y= m_state->getCanvasHeight() /2.0f;
}

void Ball::draw()
{
    graphics::drawRect(m_ball_pos_x , m_ball_pos_y, m_ball_radius * 2, m_ball_radius * 2, m_brush_ball);
}

void Ball::setHeldBy(Player* player) {  //sets which player holds it
    m_heldBy = player;

    setPosition(player->getPositionX(), player->getPositionY() - 0.5f);

    setVelocity(0.0f, 0.0f);
}



void Ball::release() {  // ball position stops being the same one as the players
    m_heldBy = nullptr;
}
