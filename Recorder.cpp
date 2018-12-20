#include "Recorder.h"

#include "Mouse.h"
#include "Manager.h"

const double MOVE_Y = 60;
const double MAX_SPEED = 100;
const double NODE_RADIUS = 30;

Recorder::Recorder( ) :
CREATE_POS_Y( Manager::getInstance( )->getScreenHeight( ) * 0.45 ),
_max_node( 0x0a ) {
	// 初期地点
	Manager* manager = Manager::getInstance( );
	_nodes.push_back( Vector( manager->getScreenWidth( ) * 0.5, CREATE_POS_Y ) );
}

Recorder::~Recorder( ) {
}

void Recorder::record( ) {
	// 下に下げる
	fall( );

	// 最新座標を入力
	recordNewMousePos( );

	// マウス座標からノードの座標を計算
	convertNodePos( );

	// マウスの座標を更新
	clearMousePos( );

	// 画面から出たものは消す
	deleteOnBecameInvisible( );
}

void Recorder::fall( ) {
	// mouse の軌跡を下げる
	for ( Vector& pos : _mouse_points ) {
		pos.y += MOVE_Y;
	}

	// node を全体的に下げる
	for ( Vector& pos : _nodes ) {
		pos.y += MOVE_Y;
	}
}

void Recorder::recordNewMousePos( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );

	Vector past_pos = pos;
	if ( _mouse_points.size( ) > 0 ) {
		past_pos = _mouse_points.back( );
	}

	// speed制限
	double dot = Vector( 1, 0, 0 ).dot( pos - past_pos );
	if ( dot < -MAX_SPEED || MAX_SPEED < dot ) {
		pos = past_pos + ( pos - past_pos ).normalize( ) * MAX_SPEED;
	}

	// y は毎回同じ位置から
	pos.y = CREATE_POS_Y;

	_mouse_points.push_back( pos );
}

void Recorder::convertNodePos( ) {
	std::list< Vector >::reverse_iterator mouse_iterator = _mouse_points.rbegin( );

	Vector line = Vector( );
	Vector end   = _nodes.back( );

	for ( mouse_iterator; mouse_iterator != _mouse_points.rend( ); mouse_iterator++ ) {
		Vector start = ( *mouse_iterator );

		line += end - start;
		end = start;

		// ノードサイズより短い線であれば次を加算
		if ( line.getLength2( ) < NODE_RADIUS * NODE_RADIUS * 4 ) {
			continue;
		}

		// 新規作成場所を計算
		Vector create_pos = ( line.normalize( ) * -1 ) * ( NODE_RADIUS * 2 ) + _nodes.back( );
		_nodes.push_back( create_pos );

		// 最後の位置を更新
		end = create_pos;
		line = Vector( );
	}
}

void Recorder::clearMousePos( ) {
	// 最後のノードより下にあるポイントは削除
	std::list< Vector >::iterator ite = _mouse_points.begin( );
	Vector last_pos = _nodes.back( );

	while ( ite != _mouse_points.end( ) ) {
		if ( ( *ite ).y > last_pos.y ) {
			ite = _mouse_points.erase( ite );
			continue;
		}
		ite++;
	}
}

void Recorder::deleteOnBecameInvisible( ) {
	std::list< Vector >::iterator ite = _nodes.begin( );
	const int MAX_HEIGHT =  Manager::getInstance( )->getScreenHeight( );

	while ( ite != _nodes.end( ) ) {
		if ( ( *ite ).y - NODE_RADIUS > MAX_HEIGHT ) {
			ite = _nodes.erase( ite );
			continue;
		} else {
			break;
		}

		ite++;
	}
}

const std::list< Vector >& Recorder::getNodes( ) const {
	return _nodes;
}