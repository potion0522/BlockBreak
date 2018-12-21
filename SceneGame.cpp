#include "SceneGame.h"
#include "Drawer.h"
#include "NodeManager.h"

SceneGame::SceneGame( ) {
	_node_manager = NodeManagerPtr( new NodeManager );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	_node_manager->update( );
}

void SceneGame::draw( ) const {
	_node_manager->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}