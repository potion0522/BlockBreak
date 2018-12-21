#pragma once
#include "smart_ptr.h"
#include "Vector.h"

#include <list>

PTR( NodeManager );
PTR( Recorder );

class NodeManager {
public:
	NodeManager( );
	virtual ~NodeManager( );

public:
	void update( );
	void draw( ) const;

private:
	void createNewNodes( );
	void adjustNodesPos( );
	void adjustNodesNum( );

private:
	const double ADJUST_LINE;

private:
	std::list< Vector > _nodes;
	unsigned char _max_node;

	RecorderPtr _recorder;
};

