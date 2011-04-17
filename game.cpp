// include headers
#include <irrlicht.h>
#include <irrbullet.h>
#include <driverChoice.h>
#include "mecc.h"
#include "AI.h"
#include "MastEventReceiver.h"
#include <game.h>
#include<d3d8.h>
#include<gl.h>

//using namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CGame::CGame()
{
    GDriver = EDT_SOFTWARE;
    resHeight = 480;
    resWidth = 640;
    Bits = 32;
    Fullscreen = false;
    StencilBuffer = false;
    VSync = false;

}

CGame::~CGame()
{

}
void CGame::setDriverType(E_DRIVER_TYPE Driver)
{
    GDriver = Driver;
}

E_DRIVER_TYPE CGame::getDriverType()
{
    return GDriver;
}

void CGame::setHeight(int Height)
{
    resHeight = Height;
}

int CGame::getHeight()
{
    return resHeight;
}

void CGame::setWidth(int Width)
{
    resWidth = Width;
}

int CGame::getWidth()
{
    return resWidth;
}

void CGame::setBits(u32 uBits)
{
    Bits = uBits;
}

u32 CGame::getBits()
{
    return Bits;
}

void CGame::setFullScreen(bool Full)
{
    Fullscreen = Full;
}

bool CGame::getFullScreen()
{
    return Fullscreen;
}

void CGame::setStencilBuffer(bool Stencil)
{
    StencilBuffer = Stencil;
}

bool CGame::getStencilBuffer()
{
    return StencilBuffer;
}

void CGame::setVSync(bool Sync)
{
    VSync = Sync;
}

bool CGame::getVSync()
{
    return VSync;
}


void CGame::run()
{

    printf("executing game.run\n");
    setup();
    MastEventReceiver EReceiver;
    EReceiver.init();
    IrrlichtDevice* Gdevice = createDevice(GDriver,dimension2d<u32>(resWidth, resHeight),Bits,Fullscreen,StencilBuffer,VSync,&EReceiver);
// create physics world
	irrBulletWorld* GPhysicsWorld = createIrrBulletWorld(Gdevice,true,true);
// check for rendering device
	if (!Gdevice)
		return;

// pointers to driver, scenemanager and gui
	IVideoDriver* Gdriver = Gdevice->getVideoDriver();
	ISceneManager* Gsmgr = Gdevice->getSceneManager();
	IGUIEnvironment* Ggui = Gdevice->getGUIEnvironment();

// draw physics debug-things
    GPhysicsWorld->setDebugMode(EPDM_DrawAabb | EPDM_DrawContactPoints);

// add terrain
    IMeshSceneNode* MainTerrain = Gsmgr->addMeshSceneNode(Gsmgr->getMesh("./media/Terrain.obj"));
    MainTerrain->setPosition(vector3df(5400,300,5200));
    MainTerrain->setScale(vector3df(400, 400, 400));

    MainTerrain->setMaterialFlag(EMF_LIGHTING, false);
    MainTerrain->setMaterialTexture(0,Gdriver->getTexture("./media/Terraintexture.jpg"));
    MainTerrain->setMaterialTexture(1,Gdriver->getTexture("./media/Terraindetailmap.jpg"));


    printf("adding shape");
    ICollisionShape* TerrainShape = new IBvhTriangleMeshShape(MainTerrain, MainTerrain->getMesh(), 0);
    TerrainShape->setMargin(0.07);

    printf("adding body");
    IRigidBody* TerrainBody = GPhysicsWorld->addRigidBody(TerrainShape);
    TerrainBody->setGravity(vector3df(0,0,0));

    printf("collisionflags");
    TerrainBody->setCollisionFlags(ECF_STATIC_OBJECT);

// it's baz! (aka add a mecc)
    CMecc* MBazz;
    MBazz = new CMecc(Gdevice,Gsmgr,Gdriver, GPhysicsWorld, EReceiver);

    MBazz->setPosition(vector3df(2700*2,255*2,2600*2));

// add an AI
    CAIDude* ADude;
    ADude = new CAIDude(Gdevice,Gsmgr,Gdriver, GPhysicsWorld);

    ADude->setPosition(vector3df(2700*2,255*2,2600*2));

// define timer
    u32 TimeStamp = Gdevice->getTimer()->getTime(), DeltaTime = 0;
    ICameraSceneNode* Cam =Gsmgr->addCameraSceneNodeFPS();
// render loop
	while(Gdevice->run())
	{

        EReceiver.endEventProcess();

        //MBazz->CameraControl();
        //MBazz->Move();
		Gdriver->beginScene(true, true, SColor(255,100,101,140));

		//ADude->TryToCrashIntoPlayer(MBazz->getPosition());

// get time elapsed since last frame
		DeltaTime = Gdevice->getTimer()->getTime() - TimeStamp;

// get current time
        TimeStamp = Gdevice->getTimer()->getTime();

// update scene according to physics
        GPhysicsWorld->stepSimulation(DeltaTime*0.001f, 120);

// draw debug things
        GPhysicsWorld->debugDrawWorld(true);

// draw some more debug things
        GPhysicsWorld->debugDrawProperties(true);

        Gsmgr->setActiveCamera(Cam);
		Ggui->drawAll();
        Gsmgr->drawAll();

		EReceiver.startEventProcess();

		printf("AI position: %d %d %d \n", int(ADude->getPosition().X), int(ADude->getPosition().Y), int(ADude->getPosition().Z));
		printf("MBazz position: %d %d %d \n", int(MBazz->getPosition().X), int(MBazz->getPosition().Y), int(MBazz->getPosition().Z));
        printf("terrain position: %d %d %d \n", int(MainTerrain->getPosition().X), int(MainTerrain->getPosition().Y), int(MainTerrain->getPosition().Z));

	}
// delete rendering and physics devices
	delete GPhysicsWorld;
	Gdevice->drop();
    return;
}

void CGame::setup()
{
    IrrlichtDevice* SDevice = createDevice(EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,false, false, false, 0);
    IGUIEnvironment* GUIEnv = SDevice->getGUIEnvironment();
    IVideoDriver* SDriver = SDevice->getVideoDriver();

    GUIEnv->addImage(SDriver->getTexture("./media/setup.tga"), position2d<s32>(0,0));

    IGUIListBox* DriverList = GUIEnv->addListBox(recti(10,10,220,210));
    DriverList->addItem(L"OpenGL 1.5");
	DriverList->addItem(L"Direct3D 8.1");
	DriverList->addItem(L"Direct3D 9.0c");
	DriverList->addItem(L"Burning's Video 0.44");
	DriverList->addItem(L"Irrlicht Software Renderer 1.0");

	IGUIListBox* ResList = GUIEnv->addListBox(recti(230,10,460,210));
	ResList->addItem(L"640*480");
	ResList->addItem(L"800*600");
	ResList->addItem(L"1024*768");
	ResList->addItem(L"1280*720");

	IGUIListBox* BitList = GUIEnv->addListBox(recti(10,220,100,260));
	BitList->addItem(L"8");
    BitList->addItem(L"16");
    BitList->addItem(L"32");

    IGUICheckBox* FullCheck = GUIEnv->addCheckBox(0,recti(110,220,130,240));
    IGUICheckBox* StencilCheck = GUIEnv->addCheckBox(0,recti(110,250,130,270));
    IGUICheckBox* VSyncCheck = GUIEnv->addCheckBox(0,recti(110,280,130,300));

	while(SDevice->run())
	{
	    SDriver->beginScene(true, true, SColor(255,100,101,140));
        GUIEnv->drawAll();

        SDriver->endScene();
    }
    switch(DriverList->getSelected())
    {
        case 0:
            GDriver = EDT_OPENGL;
            break;
        case 1:
            GDriver = EDT_DIRECT3D8;
            break;
        case 2:
            GDriver = EDT_DIRECT3D9;
            break;
        case 3:
            GDriver = EDT_BURNINGSVIDEO;
            break;
        case 4:
            GDriver = EDT_SOFTWARE;
            break;
    }
    switch(ResList->getSelected())
    {
        case 0:
            resWidth = 640;
            resHeight = 480;
            break;
        case 1:
            resWidth = 800;
            resHeight = 600;
            break;
        case 2:
            resWidth = 1024;
            resHeight = 768;
            break;
        case 3:
            resWidth = 1280;
            resHeight = 720;
            break;
    }
    switch(BitList->getSelected())
    {
        case 0:
            Bits = 8;
            break;
        case 1:
            Bits = 16;
            break;
        case 2:
            Bits = 32;
            break;
    }

    Fullscreen = FullCheck->isChecked();
    StencilBuffer = StencilCheck->isChecked();
    VSync = VSyncCheck->isChecked();
}

