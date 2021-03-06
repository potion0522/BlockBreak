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

	// 新しく子を生成
	void spawn( );

	// 自分が削除されるとき
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

