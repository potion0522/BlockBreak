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
	// �O�Ղ�S�̓I�ɉ�����
	adjust( );

	// �ŐV���W�����
	recordNewPos( );

	// ��ʂ���o�����̂͏���
	deleteOnBecameInvisible( );
}

void LineRecorder::recordNewPos( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );

	Vector past_pos = pos;
	if ( _recorder.size( ) > 0 ) {
		past_pos = _recorder.back( );
	}

	// speed����
	double dot = Vector( 1, 0, 0 ).dot( pos - past_pos );
	if ( dot < -MAX_SPEED || MAX_SPEED < dot ) {
		pos = past_pos + ( pos - past_pos ).normalize( ) * MAX_SPEED;
	}

	// y �͖��񓯂��ʒu����
	pos.y = CREATE_POS_Y;

	// �V�������̂͌��ɓ����
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
		// debug 30.0 ��Node�T�C�Y
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