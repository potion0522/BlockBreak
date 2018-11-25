#include "SceneTitle.h"
#include "Drawer.h"
#include "Image.h"
#include "Manager.h"

const char *BG_FILEPATH = "Title/BG.png";
const char *START_FONT_FILEPATH = "Title/ClickToStart.png";

SceneTitle::SceneTitle( ) :
FONT_FLASHING_RATIO( 180.0 ),
FONT_FLASHING_ALPHA( 120 ),
PI( 3.14159265 ),
_count( 0 ) {
	DrawerPtr drawer = Drawer::getTask( );
	_bg = drawer->getImage( BG_FILEPATH );
	_click_to_start_font = drawer->getImage( START_FONT_FILEPATH );

	Manager* manager = Manager::getInstance( );
	int scr_w = manager->getScreenWidth( );
	int scr_h = manager->getScreenHeight( );

	_click_to_start_font->setPos( ( int )( scr_w * 0.5f ), ( int )( scr_h * 0.75f ) );
	_click_to_start_font->setCentral( true );
}

SceneTitle::~SceneTitle( ) {
}

void SceneTitle::update( ) {
	// font ‚Ì“_–Å‚ÌŒvZ
	const int MAX_ALPHA = 255;
	_count = ( _count + 1 ) % ( int )( FONT_FLASHING_RATIO + 1 );

	int flashing = ( int )( ( sin( ( PI * 2 ) / FONT_FLASHING_RATIO * _count ) + 1 ) / 2 * FONT_FLASHING_ALPHA );
	int alpha = MAX_ALPHA - flashing;

	_click_to_start_font->setBlendMode( alpha );
}

void SceneTitle::draw( ) const {
	_bg->draw( );
	_click_to_start_font->draw( );

	Drawer::getTask( )->flip( );
}