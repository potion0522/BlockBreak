#pragma once
#include "smart_ptr.h"
#include "Vector.h"

PTR( Node );

class Node : public std::enable_shared_from_this< Node > {
private:
	enum TYPE {
		TYPE_PARENT,
		TYPE_CHILD,
	};

public:
	Node( );
	Node( NodePtr parent_pos );
	virtual ~Node( );

public:
	void update( );
	void draw( ) const;

public:
	void setSpeed( const Vector& speed );

public:
	Vector getPos( ) const;

	// V‚µ‚­q‚ğ¶¬
	void spawn( );

	// ©•ª‚ªíœ‚³‚ê‚é‚Æ‚«
	NodePtr destroy( );

private:
	void updateParent( );
	void updateChild( );
	void adjustY( );
	void move( );

private:
	const short ADJUST_LINE_Y;

private:
	TYPE _type;
	Vector _pos;
	Vector _speed;

	NodeWeakPtr _parent;
	NodePtr _child;
};

