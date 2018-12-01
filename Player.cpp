#include "Player.h"
#include "Keyboard.h"
#include "Image.h"
#include "Drawer.h"
#include "Manager.h"
#include "Mouse.h"
#include "Node.h"

const char* PLAYER_FILEPATH = "Game/Player.png";

Player::Player( ) :
MAX_SPEED( 75 ),
DETECT_ADJUST_RANCE( 1.0 ),
Y_ADJUST_SPEED( 15.0 ),
_pos( ),
_speed( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_player_image = drawer->getImage( PLAYER_FILEPATH );

	Manager* manager = Manager::getInstance( );
	int scr_w = manager->getScreenWidth( );
	int scr_h = manager->getScreenHeight( );

	_player_image->setCentral( true );

	// 初期地点
	_base_y = scr_h / 2.0f;
	_pos = Vector( scr_w * 0.5, scr_h * 0.75 );

	// debug
	_node = NodePtr( new Node );
}

Player::~Player( ) {
}

void Player::update( ) {
	updatePlayerPos( );
	adjustY( );

	// debug
	if ( Mouse::getTask( )->isClickDownLeft( ) ) {
		_speed += Vector( 0, 60 );
		_node->spawn( );
	}
	_node->update( );
	// !debug

	move( );
}

void Player::updatePlayerPos( ) {
	MousePtr mouse = Mouse::getTask( );

	Vector mouse_pos = mouse->getPoint( );
	Vector player_to_mouse = mouse_pos - _pos;

	double dot = Vector( 1, 0, 0 ).normalize( ).dot( player_to_mouse );

	_speed += Vector( dot, 0 );
}

void Player::adjustY( ) {
	double length = fabs( _base_y - _pos.y );
	if ( length < DETECT_ADJUST_RANCE ) {
		return;
	}

	// 設定されたYに戻そうとする
	Vector pos = Vector( _pos.x, _pos.y - _base_y );
	double cross = Vector( 1, 0 ).cross2D( pos );

	float dir = 0;
	if ( cross < 0 ) {
		dir =  1;
	} else {
		dir = -1;
	}

	double adjust = Y_ADJUST_SPEED;
	if ( adjust > length ) {
		adjust = length;
	}

	_speed += Vector( 0, dir * adjust );
}

void Player::move( ) {
	if ( _speed.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		_speed = _speed.normalize( ) * MAX_SPEED;
	}

	_pos += _speed;

	_node->setSpeed( _speed );

	_speed = Vector( );
}

void Player::draw( ) const {
	//_player_image->setPos( ( int )_pos.x, ( int )_pos.y );
	//_player_image->draw( );

	// debug
	_node->draw( );
	// !debug
}

void Player::drawDebug( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	// ベース線 y
	Manager* manager = Manager::getInstance( );
	Vector start = Vector( 0, _base_y );
	Vector end   = Vector( manager->getScreenWidth( ), _base_y );
	drawer->drawFormatString( 0, _base_y - 20, 0xff0000, "_base_line : y = %.2lf", _base_y );
	drawer->drawLine( ( float )start.x, ( float )start.y, ( float )end.x, ( float )end.y, 0xff0000 );
}