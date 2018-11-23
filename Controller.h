#pragma once
#include "smart_ptr.h"
#include "Base.h"
#include <string>

PTR( Controller );
PTR( Scene );

class Controller : public Base {
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_GAME
	};

public:
	static ControllerPtr getTask( );
	static std::string getTag( ) { return "CONTROLLER"; }

public:
	Controller( );
	virtual ~Controller( );

public:
	void update( );
	void initialize( );

public:
	void changeScene( SCENE scene );

private:
	ScenePtr _play_scene;
};

