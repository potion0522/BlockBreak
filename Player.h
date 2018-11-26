#pragma once
#include "smart_ptr.h"
#include "Vector.h"

PTR( Player );
PTR( Image );

class Player {
public:
	Player( );
	virtual ~Player( );

public:
	void update( );
	void draw( ) const;

private:
	void updatePlayerPos( );

private:
	float _speed;
	Vector _pos;

	ImagePtr _player_image;
};

