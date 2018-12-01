#include "Node.h"
#include "Drawer.h"
#include "Manager.h"

// debug
const float RADIUS = 30.0f;
const double RUG = 0.5;
const int MAX_STACK = 2;

Node::Node( ) :
_parent( ),
_pos( ),
_speed( ) {
	Manager* manager = Manager::getInstance( );
	int scr_w = manager->getScreenWidth( );
	int scr_h = manager->getScreenHeight( );

	_pos = Vector( scr_w * 0.5, scr_h * 0.75 );
	_stack_speed.resize( MAX_STACK );
}

Node::Node( NodePtr parent ) :
_parent( parent ),
_pos( ),
_speed( ) {
	_pos = parent->getPos( );
	_pos.y += RADIUS * 2;
	_stack_speed.resize( MAX_STACK );
}

Node::~Node( ) {
}

void Node::update( ) {
	move( );

	if ( _child ) {
		_child->update( );
	}

}

void Node::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawCircle( ( float )_pos.x, ( float )_pos.y, RADIUS, 0xffffff, true );

	if ( _child ) {
		_child->draw( );
	}
}

void Node::setSpeed( const Vector& speed ) {
	_speed = speed;
}

Vector Node::getPos( ) const {
	return _pos;
}

bool Node::isParent( ) const {
	return ( _parent.lock( ) == NodePtr( ) );
}

void Node::spawn( ) {
	if ( _child ) {
		_child->spawn( );
	} else {
		_child = NodePtr( new Node( shared_from_this( ) ) );
	}
}

NodePtr Node::destroy( ) {
	if ( !_child ) {
		// 空を返す
		return NodePtr( );
	}

	return _child;
}

void Node::move( ) {
	_pos += _speed;

	// 子に指示を出す
	instruct( );

	// 新しい命令を詰めておく
	const int LAST_ORDER = MAX_STACK - 1;
	_stack_speed[ LAST_ORDER ] = _speed;
	_speed = Vector( );
}

void Node::instruct( ) {
	const int FIRST_ORDER = 0;

	if ( _child ) {
		_child->setSpeed( _stack_speed[ FIRST_ORDER ] );
	}

	// オーダーをまわす
	for ( int i = 0; i < MAX_STACK - 1; i++ ) {
		_stack_speed[ i ] = _stack_speed[ i + 1 ];
	}
}