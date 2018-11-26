#include "Player.h"
#include "Keyboard.h"
#include "Image.h"
#include "Drawer.h"
#include "Manager.h"

const char* KEY_LEFT_MOVE = "a";
const char* KEY_RIGHT_MOVE = "d";

const char* PLAYER_FILEPATH = "Game/Player.png";

Player::Player( ) :
_pos( ),
_speed( 10.0f ) {
	DrawerPtr drawer = Drawer::getTask( );
	_player_image = drawer->getImage( PLAYER_FILEPATH );

	Manager* manager = Manager::getInstance( );
	int scr_w = manager->getScreenWidth( );
	int scr_h = manager->getScreenHeight( );

	_player_image->setCentral( true );
	_pos = Vector( scr_w * 0.5, scr_h * 0.75 );
}

Player::~Player( ) {
}

void Player::update( ) {
	updatePlayerPos( );
}

void Player::updatePlayerPos( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );

	Vector dir;

	// debug

	// ‰E
	if ( keyboard->getKeyState( KEY_RIGHT_MOVE ) ) {
		dir = Vector( 1, 0 );
	}

	// ¶
	if ( keyboard->getKeyState( KEY_LEFT_MOVE ) ) {
		dir = Vector( -1, 0 );
	}

	_pos += dir * _speed;
}

void Player::draw( ) const {
	_player_image->setPos( ( int )_pos.x, ( int )_pos.y );
	_player_image->draw( );

}