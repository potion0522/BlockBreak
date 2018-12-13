#include "NodeManager.h"
#include "Drawer.h"

NodeManager::NodeManager( ) :
NODE_RADIUS( 30.0f ),
_node_num( 0x0A ) {
}

NodeManager::~NodeManager( ) {
}

void NodeManager::calcNodePos( const std::list< Vector >& line ) {
	// データの消去
	_node_pos.clear( );

	int size = ( int )line.size( );
	int max_loop = size - 1;	

	std::list< Vector >::const_iterator ite = line.begin( );

	for ( int i = 0; i < max_loop; i++ ) {
		// 点と点の間
		Vector start = *ite;
		Vector end   = *( ++ite );

		// 線をNodeサイズで分割
		Vector line = end - start;
		Vector line_dir = line.normalize( );
		int div_num = ( int )( line.getLength( ) / NODE_RADIUS );

		for ( int j = 0; j < div_num; j++ ) {
			// start + ( 方向 * i番目 * 直径 ) + 半径
			Vector node_pos = start + ( line_dir * j * NODE_RADIUS * 2 );

			_node_pos.push_back( node_pos );


			// 残機数分だけ
			if ( _node_pos.size( ) + 1 == _node_num ) {
				break;
			}
		}

		// 残機数分だけ
		if ( _node_pos.size( ) + 1 == _node_num ) {
			break;
		}
	}

	_node_pos.push_back( ( *ite ) );
}

void NodeManager::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	for ( const Vector& pos : _node_pos ) {
		drawer->drawCircle( ( float )pos.x, ( float )pos.y, NODE_RADIUS, 0xffffff, true );
	}

	drawer->drawFormatString( 20, 20, 0xff0000, "node num : %d", ( int )_node_pos.size( ) );
}