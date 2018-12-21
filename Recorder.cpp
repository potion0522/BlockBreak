#include "Recorder.h"
#include "Mouse.h"
#include "Manager.h"

#include "define.h"

const double RECORD_LINE = 0.0;
const double MAX_SPEED = 300.0;

Recorder::Recorder( ) {
}

Recorder::~Recorder( ) {
}

bool Recorder::record( ) {
	// ���W��S�̓I�ɉ�����
	fall( );

	// �ŐV���W�����
	recordNewMousePos( );

	// �}�E�X���W����m�[�h�̍��W���v�Z
	convertNodePos( );

	bool result = false;
	if ( !_create_nodes.empty( ) ) {
		result = true;
	}

	return result;
}

void Recorder::fall( ) {
	for ( Vector& point : _mouse_points ) {
		point.y += 45;
	}
}

void Recorder::recordNewMousePos( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );

	Vector past_pos = pos;
	if ( _mouse_points.size( ) > 0 ) {
		past_pos = _mouse_points.back( );
	}

	// speed����
	double dot = Vector( 1, 0, 0 ).dot( pos - past_pos );
	if ( dot < -MAX_SPEED || MAX_SPEED < dot ) {
		pos = past_pos + ( pos - past_pos ).normalize( ) * MAX_SPEED;
	}

	// y �͖��񓯂��ʒu����
	pos.y = RECORD_LINE;

	_mouse_points.push_back( pos );
}
#include "Drawer.h"
void Recorder::convertNodePos( ) {
	// ������
	_create_nodes.clear( );

	Vector line          = Vector( );
	Vector last_node_pos = _mouse_points.front( );
	Vector end           = _mouse_points.front( );

	const double PITCH = DEFAULT_NODE_RADIUS * DEFAULT_NODE_RADIUS * 4;

	// �V�����m�[�h�𐶐�����ʒu���v�Z
	std::list< Vector >::iterator ite = _mouse_points.begin( );
	ite++;

	for ( ite; ite != _mouse_points.end( ); ite++ ) {
		Vector start = ( *ite );

		line = end - start;
		line += ( line.normalize( ) * -1 * DEFAULT_NODE_RADIUS );

		// �m�[�h�T�C�Y���Z�����ł���Ύ������Z
		double length2 = line.getLength2( );
		if ( length2 < PITCH ) {
			continue;
		}

		int div_num = ( int )( length2 / PITCH );
		static int max;
		if ( div_num > max ) {
			max = div_num;
		}
		Drawer::getTask( )->drawFormatString( 0, 20, 0xff0000, "%d", max );
		// ���΍��W
		Vector create_pos = ( line.normalize( ) * -1 ) * ( DEFAULT_NODE_RADIUS * 2 );

		for ( int j = 0; j < div_num; j++ ) {
			// ���΍��W���Z�b�g
			_create_nodes.push_back( create_pos );

			// ��΍��W���v�Z
			last_node_pos += create_pos;
		}

		line = last_node_pos - start;
		end  = start;
	}


	// �}�E�X���W�̍X�V
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