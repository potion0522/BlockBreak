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
}

Node::Node( NodePtr parent ) :
_parent( parent ),
_pos( ),
_speed( ) {
	_pos = parent->getPos( );
	_pos.y += RADIUS * 2;
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
		// ‹ó‚ð•Ô‚·
		return NodePtr( );
	}

	return _child;
}

void Node::move( ) {
	_pos += _speed;

	NodePtr parent = _parent.lock( );
	if ( parent ) {
		Vector adjust_y = Vector( 0, 1 );
		_pos += adjust_y * RADIUS * 0.38; // ¬”‚Í“K“–B‚‚¯‚ê‚Î‚‚¢‚Ù‚Ç‚·‚®‚Éc‚É‚È‚é

		Vector parent_pos = parent->getPos( );
		Vector child_to_parent = parent_pos - _pos;

		double length = child_to_parent.getLength( );
		double control_length = RADIUS * 2;

		double result = length - control_length;

		if ( result > 0 ) { // ‰“‚¢
			_pos += child_to_parent.normalize( ) * result;
		}
	}

	_speed = Vector( );
}