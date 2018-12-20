#include "SceneGame.h"
#include "Drawer.h"
#include "NodeDrawer.h"
#include "Recorder.h"

SceneGame::SceneGame( ) {
	_node_drawer = NodeDrawerPtr( new NodeDrawer );
	_recorder = RecorderPtr( new Recorder );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	_recorder->record( );
}

void SceneGame::draw( ) const {
	_node_drawer->draw( _recorder->getNodes( ) );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}