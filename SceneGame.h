#pragma once
#include "Scene.h"
#include "smart_ptr.h"

PTR( SceneGame );
PTR( Player );

class SceneGame : public Scene {
public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	PlayerPtr _player;
};

