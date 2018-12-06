#pragma once
#include "smart_ptr.h"
#include "Vector.h"

PTR( Node );

class Node : public std::enable_shared_from_this< Node > {
public:
	Node( );
	Node( NodePtr parent_pos );
	virtual ~Node( );

public:
	void update( );
	void draw( ) const;

public: // setter
	void setSpeed( const Vector& speed );


public: // getter
	Vector getPos( ) const;
	bool isParent( ) const;

	// V‚µ‚­q‚ğ¶¬
	void spawn( );

	// ©•ª‚ªíœ‚³‚ê‚é‚Æ‚«
	NodePtr destroy( );

private:
	void move( );

private:
	Vector _pos;
	Vector _speed;

	NodeWeakPtr _parent;
	NodePtr _child;
};

