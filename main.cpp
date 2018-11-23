#include "Manager.h"
#include "Controller.h"
#include "Drawer.h"

int main( ) {
	Manager* manager = Manager::getInstance( );

	// fundation class
	BasePtr drawer( new Drawer( "." ) );

	// now project class
	BasePtr controller( new Controller );

	
	// add
	manager->add( Controller::getTag( ), controller );
	manager->add( Drawer::getTag( ), drawer );
	return 0;
}