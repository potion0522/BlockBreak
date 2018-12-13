#include "SceneGame.h"
#include "Drawer.h"
#include "Node.h"

SceneGame::SceneGame( ) {
	_player = NodePtr( new Node );
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