#include "SceneTitle.h"
#include "Drawer.h"
#include "Image.h"
#include "Manager.h"
#include "Button.h"
#include "Controller.h"
#include "Vector.h"

const char* BG_FILEPATH = "Title/TitleBG.png";
const char* START_FONT_FILEPATH = "Title/ClickToStart.png";

SceneTitle::SceneTitle( ) :
FONT_FLASHING_RATIO( 180.0 ),
FONT_FLASHING_ALPHA( 120 ),
PI( 3.14159265 ),
_count( 0 ) {
	DrawerPtr drawer = Drawer::getTask( );
	_bg = drawer->getImage( BG_FILEPATH );

	Manager* manager = Manager::getInstance( );
	int scr_w = manager->getScreenWidth( );
	int scr_h = manager->getScreenHeight( );

	_click_to_start_font = ButtonPtr( new Button );
	_click_to_start_font->setDefaultImage( START_FONT_FILEPATH );
	_click_to_start_font->setPushImage( START_FONT_FILEPATH );
	_click_to_start_font->setPos( Vector( scr_w * 0.5, scr_h * 0.75 ) );
}

SceneTitle::~SceneTitle( ) {
}

void SceneTitle::update( ) {
	// 点滅計算
	updateFontFlash( );

	// ボタンアクション
	updateButton( );
}

void SceneTitle::updateFontFlash( ) {
	const int MAX_ALPHA = 255;
	_count = ( _count + 1 ) % ( int )( FONT_FLASHING_RATIO + 1 );

	int flashing = ( int )( ( sin( ( PI * 2 ) / FONT_FLASHING_RATIO * _count ) + 1 ) / 2 * FONT_FLASHING_ALPHA );
	int alpha = MAX_ALPHA - flashing;

	_click_to_start_font->setAlpha( alpha );
}

void SceneTitle::updateButton( ) {
	_click_to_start_font->update( );

	if ( !_click_to_start_font->isClicked( ) ) {
		return;
	}

	Controller::getTask( )->changeScene( Controller::SCENE_GAME );
}

void SceneTitle::draw( ) const {
	_bg->draw( );
	_click_to_start_font->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}