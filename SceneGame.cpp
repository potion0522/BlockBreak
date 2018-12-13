#include "SceneGame.h"
#include "Drawer.h"
#include "NodeManager.h"
#include "LineRecorder.h"

SceneGame::SceneGame( ) {
	_node = NodeManagerPtr( new NodeManager );
	_recorder = LineRecorderPtr( new LineRecorder );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	_recorder->record( );
	_node->calcNodePos( _recorder->getRecordingData( ) );
}

void SceneGame::draw( ) const {
	_node->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}