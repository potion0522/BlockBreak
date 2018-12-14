#include "LineRecorder.h"

#include "Mouse.h"
#include "Manager.h"

const double MOVE_Y = 60;
const double MAX_SPEED = 120;

LineRecorder::LineRecorder( ) :
CREATE_POS_Y( Manager::getInstance( )->getScreenHeight( ) * 0.45 ) {
}

LineRecorder::~LineRecorder( ) {
}

void LineRecorder::record( ) {
	// 軌跡を全体的に下げる
	adjust( );

	// 最新座標を入力
	recordNewPos( );

	// 画面から出たものは消す
	deleteOnBecameInvisible( );
}

void LineRecorder::recordNewPos( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );

	Vector past_pos = pos;
	if ( _recorder.size( ) > 0 ) {
		past_pos = _recorder.back( );
	}

	// speed制限
	double dot = Vector( 1, 0, 0 ).dot( pos - past_pos );
	if ( dot < -MAX_SPEED || MAX_SPEED < dot ) {
		pos = past_pos + ( pos - past_pos ).normalize( ) * MAX_SPEED;
	}

	// y は毎回同じ位置から
	pos.y = CREATE_POS_Y;

	// 新しいものは後ろに入れる
	_recorder.push_back( pos );
}

void LineRecorder::adjust( ) {
	for ( Vector& pos : _recorder ) {
		pos.y += MOVE_Y;
	}
}

void LineRecorder::deleteOnBecameInvisible( ) {
	std::list< Vector >::iterator ite = _recorder.begin( );
	const int MAX_HEIGHT =  Manager::getInstance( )->getScreenHeight( );

	while ( ite != _recorder.end( ) ) {
		// debug 30.0 はNodeサイズ
		if ( ( *ite ).y - 30.0 > MAX_HEIGHT ) {
			ite = _recorder.erase( ite );
			continue;
		} else {
			break;
		}

		ite++;
	}
}

const std::list< Vector >& LineRecorder::getRecordingData( ) const {
	return _recorder;
}