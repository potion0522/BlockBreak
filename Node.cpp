#include "Node.h"
#include "Drawer.h"
#include "Manager.h"
#include "Mouse.h"

// debug
const float RADIUS = 30.0f;
const double RUG = 0.5;
const int MAX_STACK = 2;
const float LINE_ADJUST_RATIO = 0.3f;
const double MAX_SPEED = 95.0;

Node::Node( ) :
_parent( ),
_pos( ),
_speed( ),
_type( TYPE_PARENT ),
ADJUST_LINE_Y( Manager::getInstance( )->getScreenHeight( ) / 2 ) {
	Manager* manager = Manager::getInstance( );
	int scr_w = manager->getScreenWidth( );
	int scr_h = manager->getScreenHeight( );

	_pos = Vector( scr_w * 0.5, scr_h * 0.75 );
}

Node::Node( NodePtr parent ) :
_parent( parent ),
_pos( ),
_speed( ),
_type( TYPE_CHILD ),
ADJUST_LINE_Y( Manager::getInstance( )->getScreenHeight( ) / 2 ) {
	_pos = parent->getPos( );
	_pos.y += RADIUS * 2;
}

Node::~Node( ) {
}

void Node::update( ) {
	switch ( _type ) {
	case TYPE_PARENT: updateParent( ); break;
	case TYPE_CHILD : updateChild( ) ; break;
	default: break;
	}

	// ˆê’è’l‚æ‚èã‚És‚©‚È‚¢
	adjustY( );

	// speed •ª“®‚©‚·
	move( );

	if ( _child ) {
		_child->update( );
	}
}

void Node::updateParent( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector mouse_pos = mouse->getPoint( );

	double dot = Vector( 1, 0 ).dot( ( mouse_pos - _pos ) );
	_speed += Vector( 1, 0 ) * dot;

	// ã‚Éi‚Ý‘±‚¯‚é
	_speed += Vector( 0, -RADIUS * 0.5 );
}

void Node::updateChild( ) {
	NodePtr parent = _parent.lock( );
	if ( !parent ) {
		_type = TYPE_PARENT;
		return;
	}

	// ‰º‚ÉL‚Ñ‚é‚æ‚¤‚É‚·‚é
	Vector adjust_y = Vector( 0, 1 );
	_pos += adjust_y * RADIUS * LINE_ADJUST_RATIO;

	Vector parent_pos = parent->getPos( );
	Vector child_to_parent = parent_pos - _pos;

	double length = child_to_parent.getLength( );
	double control_length = RADIUS * 2;

	double result = length - control_length;

	// e‚Æ‚Ì‹——£‚ª’¼Œa‚æ‚è‰“‚¯‚ê‚Î‹ß‚Ã‚¯‚é
	if ( result > 0 ) {
		_speed = child_to_parent.normalize( ) * result;
	}
}

void Node::adjustY( ) {
	double over_distance = ( double )ADJUST_LINE_Y - _pos.y;
	if ( over_distance > 0 ) {
		_speed.y += over_distance;
	}
}

void Node::move( ) {
	if ( _speed.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		_speed = _speed.normalize( ) * MAX_SPEED;
	}

	_pos += _speed;
	_speed = Vector( );
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