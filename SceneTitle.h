#pragma once
#include "Scene.h"
#include "smart_ptr.h"

PTR( SceneTitle );

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );

public:
	void update( );
	void draw( ) const;
};

