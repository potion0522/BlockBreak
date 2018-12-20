#include "NodeDrawer.h"
#include "Drawer.h"

const double NODE_RADIUS = 30.0;

NodeDrawer::NodeDrawer( ) {
}

NodeDrawer::~NodeDrawer( ) {
}

void NodeDrawer::draw( const std::list< Vector >& nodes ) const {
	DrawerPtr drawer = Drawer::getTask( );
	for ( const Vector& pos : nodes ) {
		drawer->drawCircle( ( float )pos.x, ( float )pos.y, NODE_RADIUS, 0xffffff, true );
	}
}