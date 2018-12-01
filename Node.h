#pragma once
#include "smart_ptr.h"
#include "Vector.h"
#include <vector>

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

	// 新しく子を生成
	void spawn( );

	// 自分が削除されるとき
	NodePtr destroy( );

private:
	void move( );
	void instruct( );

private:
	std::vector< Vector > _stack_speed;
	Vector _pos;
	Vector _speed;

	NodeWeakPtr _parent;
	NodePtr _child;
};

