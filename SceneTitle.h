#pragma once
#include "Scene.h"
#include "smart_ptr.h"

PTR( SceneTitle );
PTR( Image );

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );

public:
	void update( );
	void draw( ) const;

private:
	const double FONT_FLASHING_RATIO;
	const int FONT_FLASHING_ALPHA;
	const double PI;
	int _count;

	ImagePtr _bg;
	ImagePtr _click_to_start_font;
};

