#pragma once
#include "smart_ptr.h"

PTR( Scene );

class Scene {
public:
	Scene( ) { };
	virtual ~Scene( ) { };

public:
	virtual void update( ) = 0;
	virtual void draw( ) const = 0;
};

