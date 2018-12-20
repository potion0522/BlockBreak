#pragma once
#include "Scene.h"
#include "smart_ptr.h"

PTR( SceneGame );
PTR( NodeDrawer );
PTR( Recorder );

class SceneGame : public Scene {
public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	NodeDrawerPtr _node_drawer;
	RecorderPtr _recorder;
};

