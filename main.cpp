#include "Manager.h"
#include "Controller.h"
#include "Drawer.h"
#include "Mouse.h"

int main( ) {
	Manager* manager = Manager::getInstance( );

	// fundation class
	BasePtr drawer( new Drawer( "Resources/" ) );
	BasePtr mouse( new Mouse );

	// now project class
	BasePtr controller( new Controller );

	
	// add
	manager->add( Controller::getTag( ), controller );
	manager->add( Drawer::getTag( ), drawer );
	manager->add( Mouse::getTag( ), mouse );
	return 0;
}