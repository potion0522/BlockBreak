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

public:
	Vector getPos( ) const;
	bool isParent( ) const;

	// 新しく子を生成
	void spawn( );

	// 自分が削除されるとき
	NodePtr destroy( );

private:
	Vector _pos;

	NodeWeakPtr _parent;
	NodePtr _child;
};

