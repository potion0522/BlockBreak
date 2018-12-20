#pragma once
#include "smart_ptr.h"
#include "Vector.h"
#include <list>

PTR( Recorder );

class Recorder {
public:
	Recorder( );
	virtual ~Recorder( );

public:
	void record( );
	const std::list< Vector >& getNodes( ) const;

private:
	void fall( );
	void recordNewMousePos( );
	void convertNodePos( );
	void clearMousePos( );
	void deleteOnBecameInvisible( );

private:
	const double CREATE_POS_Y;

private:
	std::list< Vector > _mouse_points;
	std::list< Vector > _nodes;

	unsigned char _max_node;
};

