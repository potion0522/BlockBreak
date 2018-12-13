#pragma once
#include "Scene.h"
#include "smart_ptr.h"

PTR( SceneGame );
PTR( NodeManager );
PTR( LineRecorder );

class SceneGame : public Scene {
public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	NodeManagerPtr _node;
	LineRecorderPtr _recorder;
};

