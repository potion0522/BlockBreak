#include "NodeManager.h"
#include "Drawer.h"
#include "Manager.h"
#include "Mouse.h"

#include "Recorder.h"
#include "define.h"

NodeManager::NodeManager( ) :
ADJUST_LINE( Manager::getInstance( )->getScreenHeight( ) * 0.5 ),
_max_node( 0x10 ) {
	_recorder = RecorderPtr( new Recorder );

	// 初期地点に1つ生成
	MousePtr mouse = Mouse::getTask( );
	Vector mouse_point = mouse->getPoint( );
	_nodes.push_back( Vector( mouse_point.x, ADJUST_LINE ) );
}

NodeManager::~NodeManager( ) {
}

void NodeManager::update( ) {
	// マウスの座標記録 & 先頭ノードの更新
	if ( _recorder->record( ) ) {
		createNewNodes( );
	}

	// ノード数の調整
	adjustNodesNum( );

	// 先頭のY, 画面内の調整
	adjustNodesPos( );
}

void NodeManager::createNewNodes( ) {
	const std::list< Vector >& new_nodes = _recorder->getNewNodes( );
	for ( const Vector& pos : new_nodes ) {
		// 相対座標なので足し算
		_nodes.push_back( _nodes.back( ) + pos );
	}
}

void NodeManager::adjustNodesPos( ) {
	// y を調整
	double gap = ADJUST_LINE - _nodes.back( ).y;
	for ( Vector& node : _nodes ) {
		node.y += gap;
	}
}

void NodeManager::adjustNodesNum( ) {
	int delete_num = ( int )_nodes.size( ) - _max_node;
	for ( int i = 0; i < delete_num; i++ ) {
		_nodes.erase( _nodes.begin( ) );
	}
}

void NodeManager::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );

	for ( const Vector& node : _nodes ) {
		drawer->drawCircle( ( float )node.x, ( float )node.y, DEFAULT_NODE_RADIUS, 0xffffff, true );
	}
}