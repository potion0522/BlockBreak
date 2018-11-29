#pragma once
#include "smart_ptr.h"
#include "Vector.h"

PTR( Player );
PTR( Image );
PTR( Node );

class Player {
public:
	Player( );
	virtual ~Player( );

public:
	void update( );
	void draw( ) const;

	// デバッグ用
	void drawDebug( ) const;

private:
	void updatePlayerPos( );
	void adjustY( );
	void move( );

private:
	const double MAX_SPEED;
	const double DETECT_ADJUST_RANCE;
	const double Y_ADJUST_SPEED;

private:
	float _base_y;
	Vector _speed;
	Vector _pos;

	ImagePtr _player_image;
	NodePtr _node;
};

