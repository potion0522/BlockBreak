#include "Node.h"
#include "Drawer.h"
#include "Manager.h"

// debug
const float RADIUS = 30.0f;

Node::Node( ) :
_parent( ),
_pos( ) {
	Manager* manager = Manager::getInstance( );
	int scr_w = manager->getScreenWidth( );
	int scr_h = manager->getScreenHeight( );

	_pos = Vector( scr_w * 0.5, scr_h * 0.75 );
}

Node::Node( NodePtr parent ) :
_parent( parent ) {
	_pos = parent->getPos( );
	_pos.y += RADIUS;
}

Node::~Node( ) {
}

void Node::update( ) {
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

std::shared_ptr< Node > Node::destroy( ) {
	if ( !_child ) {
		// ‹ó‚ð•Ô‚·
		return NodePtr( );
	}

	return _child;
}