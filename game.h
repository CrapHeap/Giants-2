#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

// include headers
#include <irrlicht.h>
#include <irrbullet.h>
#include "MastEventReceiver.h"

//using namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CGame
{
private:
    E_DRIVER_TYPE GDriver;
    int resHeight;
    int resWidth;
    u32 Bits;
    bool Fullscreen;
    bool StencilBuffer;
    bool VSync;

public:
    CGame();
    ~CGame();

    void setDriverType(E_DRIVER_TYPE Driver);
    E_DRIVER_TYPE getDriverType();

    void setHeight(int Height);
    int getHeight();

    void setWidth(int Width);
    int getWidth();

    void setBits(u32 uBits);
    u32 getBits();\

    void setFullScreen(bool Full);
    bool getFullScreen();

    void setStencilBuffer(bool Stencil);
    bool getStencilBuffer();

    void setVSync(bool Sync);
    bool getVSync();

    void run();
    void setup();

    void setTerrainBmp(char bmpPath);
    ITerrainSceneNode* getTerrainBmp();
};

#endif // GAME_H_INCLUDED
