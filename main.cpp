#include "Manager.h"
#include "Controller.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Keyboard.h"

int main( ) {
	Manager* manager = Manager::getInstance( );

	// fundation class
	BasePtr drawer( new Drawer( "Resources/" ) );
	BasePtr mouse( new Mouse );
	BasePtr keyboard( new Keyboard );

	// now project class
	BasePtr controller( new Controller );

	
	// add
	manager->add( Controller::getTag( ), controller );
	manager->add( Drawer::getTag( ), drawer );
	manager->add( Mouse::getTag( ), mouse );
	manager->add( Keyboard::getTag( ), keyboard );
	return 0;
}