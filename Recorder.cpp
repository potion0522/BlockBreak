#include "Recorder.h"
#include "Mouse.h"
#include "Manager.h"

#include "define.h"

const double RECORD_LINE = 0.0;

Recorder::Recorder( ) :
MAX_DECAY_RATIO( 0.3 ),
_fall_speed( DEFAULT_FALL_SPEED ) {
}

Recorder::~Recorder( ) {
}

bool Recorder::record( ) {
	// 座標を全体的に下げる
	fall( );

	// 最新座標を入力
	recordNewMousePos( );

	// マウス座標からノードの座標を計算
	convertNodePos( );

	bool result = false;
	if ( !_create_nodes.empty( ) ) {
		result = true;
	}

	return result;
}

void Recorder::fall( ) {
	for ( Vector& point : _mouse_points ) {
		point.y += _fall_speed;
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
		dot = MAX_SPEED;
	}

	// 横のspeedによって縦のspeedを下げる
	double ratio = 1.0 - fabs( dot ) / MAX_SPEED;
	if ( ratio < MAX_DECAY_RATIO ) {
		ratio = MAX_DECAY_RATIO;
	}
	_fall_speed = DEFAULT_FALL_SPEED * ratio;

	// y は毎回同じ位置から
	pos.y = RECORD_LINE;

	_mouse_points.push_back( pos );
}

void Recorder::convertNodePos( ) {
	// 初期化
	_create_nodes.clear( );

	Vector line          = Vector( );
	Vector last_node_pos = _mouse_points.front( );
	Vector end           = _mouse_points.front( );

	const double PITCH = DEFAULT_NODE_RADIUS * DEFAULT_NODE_RADIUS * 4;

	// 新しくノードを生成する位置を計算
	std::list< Vector >::iterator ite = _mouse_points.begin( );
	ite++;

	for ( ite; ite != _mouse_points.end( ); ite++ ) {
		Vector start = ( *ite );

		line = end - start;

		// ノードサイズより短い線であれば次を加算
		double length2 = line.getLength2( );
		if ( length2 < PITCH ) {
			continue;
		}

		int div_num = ( int )sqrt( length2 / PITCH );

		// 相対座標
		Vector create_pos = ( line.normalize( ) * -1 ) * ( DEFAULT_NODE_RADIUS * 2 );

		for ( int j = 0; j < div_num; j++ ) {
			// 相対座標をセット
			_create_nodes.push_back( create_pos );

			// 絶対座標を計算
			last_node_pos += create_pos;
		}

		line = last_node_pos - start;
		end  = start;
	}


	// マウス座標の更新
	ite = _mouse_points.begin( );
	while ( ite != _mouse_points.end( ) ) {
		if ( ( *ite ).y >= last_node_pos.y ) {
			ite = _mouse_points.erase( ite );
			continue;
		}
		break;
	}
	_mouse_points.push_front( last_node_pos );
}

const std::list< Vector >& Recorder::getNewNodes( ) const {
	return _create_nodes;
}