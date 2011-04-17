
/// ==================================================================================================
/// MastEventReceiver code is © (Copyright) Robert E. Demarest, AKA Mastiff or Mastiff Odit
/// This file may be used in any non-commercial or commercial project as long as the following conditions are met:
/// You may not claim this code as being your own.
/// You may not use this code for any harmful, malicious or otherwise damaging programs.
///
/// This is version 1.2a of the class.
/// This class is designed for use with the Irrlicht Engine, it was written for version 1.3 of the engine.
/// ==================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// To use this Class just add  #include "MastEventReceiver.cpp"  to the end of your includes list. (or add the class in-line into your program)
// Then create an instance of it like so: MastEventReceiver eventReceiver;
// Then call the initialization fucntion like so: eventReceiver.init();
// Then inside your Main Game Loop place "eventReceiver.endEventProcess();" in the beginning of your game loop, before anything -
// that would require input, then put "eventReceiver.startEventProcess();" at the very end of your Main Game Loop.
// yeah I know it's confusing, but it makes alot more sense in the internals of the class.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Change this to the path where your Irrlicht Header Files are.
#include <irrlicht.h>
#include <MastEventReceiver.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/// ==============================
/// MastEventReceiver
/// ==============================
bool MastEventReceiver::OnEvent(const SEvent& event)
{
    bool eventprocessed = false;
    if (event.EventType == EET_KEY_INPUT_EVENT)
    {
        if (processState == STARTED)
        {
            if (event.KeyInput.PressedDown == true)
            {
                if (keyState[event.KeyInput.Key] != DOWN)
                {
                    keyState[event.KeyInput.Key] = PRESSED; // Set to Pressed
                }
                else
                {
                    keyState[event.KeyInput.Key] = DOWN; // Set to Down
                }
            }
            else
            {
                if (keyState[event.KeyInput.Key] != UP)
                {
                     keyState[event.KeyInput.Key] = RELEASED; // Set to Released
                }
            }
        }
        eventprocessed = true;
    }
    if (event.EventType == EET_MOUSE_INPUT_EVENT)
    {
        if (processState == STARTED)
        {
            if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
            {
                mouse.Y = event.MouseInput.Y;
                mouse.X = event.MouseInput.X;
            }
            if (event.MouseInput.Event == EMIE_MOUSE_WHEEL)
            {
                mouse.wheel += event.MouseInput.Wheel;
            }
            if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
            {
                if (mouseButtonState[0] == UP || mouseButtonState[0] == RELEASED)
                {
                    mouseButtonState[0] = PRESSED;
                }
                else
                {
                    mouseButtonState[0] = DOWN;
                }
            }
            if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
            {
                if (mouseButtonState[0] != UP)
                {
                    mouseButtonState[0] = RELEASED;
                }
            }
            if (event.MouseInput.Event == EMIE_MMOUSE_PRESSED_DOWN)
            {
                if (mouseButtonState[1] == UP || mouseButtonState[1] == RELEASED)
                {
                    mouseButtonState[1] = PRESSED;
                }
                else
                {
                    mouseButtonState[1] = DOWN;
                }
            }
            if (event.MouseInput.Event == EMIE_MMOUSE_LEFT_UP)
            {
                if (mouseButtonState[1] != UP)
                {
                    mouseButtonState[1] = RELEASED;
                }
            }
            if (event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
            {
                if (mouseButtonState[2] == UP || mouseButtonState[2] == RELEASED)
                {
                    mouseButtonState[2] = PRESSED;
                }
                else
                {
                    mouseButtonState[2] = DOWN;
                }
            }
            if (event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP)
            {
                if (mouseButtonState[2] != UP)
                {
                    mouseButtonState[2] = RELEASED;
                }
            }
        }
        eventprocessed = true;
    }
    return eventprocessed;
}

float MastEventReceiver::mouseWheel()
{
    return mouse.wheel;
}

int MastEventReceiver::mouseX()
{
    return mouse.X;
}

int MastEventReceiver::mouseY()
{
    return mouse.Y;
}

bool MastEventReceiver::leftMouseReleased()
{
    if (mouseButtonState[0] == RELEASED)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool MastEventReceiver::leftMouseUp()
{
    if (mouseButtonState[0] == RELEASED || mouseButtonState[0] == UP)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::leftMousePressed()
{
    if (mouseButtonState[0] == PRESSED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::leftMouseDown()
{
    if (mouseButtonState[0] == PRESSED || mouseButtonState[0] == DOWN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::middleMouseReleased()
{
    if (mouseButtonState[1] == RELEASED)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool MastEventReceiver::middleMouseUp()
{
    if (mouseButtonState[1] == RELEASED || mouseButtonState[1] == UP)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::middleMousePressed()
{
    if (mouseButtonState[1] == PRESSED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::middleMouseDown()
{
    if (mouseButtonState[1] == PRESSED || mouseButtonState[1] == DOWN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::rightMouseReleased()
{
    if (mouseButtonState[2] == RELEASED)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool MastEventReceiver::rightMouseUp()
{
    if (mouseButtonState[2] == RELEASED || mouseButtonState[2] == UP)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::rightMousePressed()
{
    if (mouseButtonState[2] == PRESSED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::rightMouseDown()
{
    if (mouseButtonState[2] == PRESSED || mouseButtonState[2] == DOWN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::keyPressed(char keycode)
{
    if (keyState[keycode] == PRESSED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::keyDown(char keycode)
{
    if (keyState[keycode] == DOWN || keyState[keycode] == PRESSED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::keyUp(char keycode)
{
    if (keyState[keycode] == UP || keyState[keycode] == RELEASED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MastEventReceiver::keyReleased(char keycode)
{
    if (keyState[keycode] == RELEASED)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void MastEventReceiver::endEventProcess()
{
    processState = ENDED;
}
void MastEventReceiver::startEventProcess()
{

    processState = STARTED;
    for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
    {
        if (keyState[i] == RELEASED)
        {
            keyState[i] = UP;
        }
        if (keyState[i] == PRESSED)
        {
            keyState[i] = DOWN;
        }
    }
    for (int i = 0; i <= 2; i++)
    {
        if (mouseButtonState[i] == RELEASED)
        {
            mouseButtonState[i] = UP;
        }

        if (mouseButtonState[i] == PRESSED)
        {
            mouseButtonState[i] = DOWN;
        }
    }
        mouse.wheel = 0.0f;

}

void MastEventReceiver::init()
{
    for (int i = 0; i <= KEY_KEY_CODES_COUNT; i++)
    {
        keyState[i] = UP;
    }
    for (int i = 0; i <= 2; i++)
    {
        mouseButtonState[i] = UP;
    }
    mouse.X = 0;
    mouse.Y = 0;
    mouse.wheel = 0.0f;
}



/// ==========================================
/// END OF MastEventReceiver
/// ==========================================

