#pragma once
#include "smart_ptr.h"
#include "Vector.h"

#include <list>

PTR( NodeManager );

class NodeManager {
public:
	NodeManager( );
	virtual ~NodeManager( );

public:
	void calcNodePos( const std::list< Vector >& line );
	void draw( ) const;

private:
	const float NODE_RADIUS;

private:
	std::list< Vector > _node_pos;

	unsigned char _node_num;
};

