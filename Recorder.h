#pragma once
#include "smart_ptr.h"
#include "Vector.h"
#include <list>

PTR( Recorder );

/*

�}�E�X�̋O�Ղ�ۑ����ċN���擪�m�[�h�̍��W����Ɍv�Z����N���X

*/

class Recorder {
public:
	Recorder( );
	virtual ~Recorder( );

public:
	bool record( );
	const std::list< Vector >& getNewNodes( ) const;

private:
	void fall( );
	void recordNewMousePos( );
	void convertNodePos( );

private:
	std::list< Vector > _create_nodes;
	std::list< Vector > _mouse_points;
};

