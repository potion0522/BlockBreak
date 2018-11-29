#include "SceneGame.h"
#include "Drawer.h"
#include "Player.h"

SceneGame::SceneGame( ) {
	_player = PlayerPtr( new Player );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	_player->update( );
}

void SceneGame::draw( ) const {
	_player->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}