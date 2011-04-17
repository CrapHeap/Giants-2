// main.cpp

// include headers
#include <irrlicht.h>
#include <irrbullet.h>
#include "mecc.h"
#include "AI.h"
#include "MastEventReceiver.h"
#include <game.h>

// used namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// link with library
#pragma comment(lib, "irrBullet.lib")
#pragma comment(lib, "BulletSoftBody.lib") 
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "LinearMath.lib")
#pragma comment(lib, "Irrlicht.lib")

// main function
int main()
{
// create rendering device
    CGame* Game;
    Game = new CGame();
    Game->run();
    Game->~CGame();
// exit to OS
	return 0;
}
