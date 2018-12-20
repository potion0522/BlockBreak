#pragma once
#include "smart_ptr.h"
#include "Vector.h"

#include <list>

PTR( NodeDrawer );

class NodeDrawer {
public:
	NodeDrawer( );
	virtual ~NodeDrawer( );

public:
	void draw( const std::list< Vector >& nodes ) const;
};

