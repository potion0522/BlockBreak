#include "SceneGame.h"
#include "Drawer.h"

SceneGame::SceneGame( ) {
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
}

void SceneGame::draw( ) const {
	Drawer::getTask( )->flip( );
}