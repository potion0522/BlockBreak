#include "Controller.h"
#include "Manager.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "Drawer.h"

ControllerPtr Controller::getTask( ) {
	return std::dynamic_pointer_cast< Controller >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Controller::Controller( ) {
}

Controller::~Controller( ) {
}

void Controller::initialize( ) {
	changeScene( SCENE_TITLE );
}

void Controller::changeScene( SCENE scene ) {
	switch ( scene ) {
	case SCENE_TITLE:
		_play_scene = SceneTitlePtr( new SceneTitle );
		break;

	case SCENE_GAME:
		_play_scene = SceneGamePtr( new SceneGame );
		break;
	}
}

void Controller::update( ) {
	// update
	_play_scene->update( );

	// draw
	_play_scene->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawCircle( 0, 0, 100, 0xffffff, true );
	drawer->flip( );
}