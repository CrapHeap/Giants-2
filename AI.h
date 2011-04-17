#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

// include headers
#include <irrlicht.h>
#include <irrbullet.h>
#include <MastEventReceiver.h>

//using namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CAIDude
{
private:
    IrrlichtDevice* GDevice;
    ISceneManager* Gsmgr;
    IVideoDriver* GDriver;
    irrBulletWorld* GPhysicsWorld;
    MastEventReceiver* GReceiver;

    int Speed;
    IAnimatedMeshSceneNode* Node;
    ICollisionShape* ColShape;
    IRigidBody* ColRigidBody;
public:

    CAIDude(IrrlichtDevice* GameDevice, ISceneManager* Gamesmgr, IVideoDriver* GameDriver, irrBulletWorld* GamePhysicsWorld);
    ~CAIDude();

    void removeNode();

    IAnimatedMeshSceneNode* getMesh();
    IAnimatedMeshSceneNode* getNode();
    ICollisionShape* getCollisionShape();
    IRigidBody* getRigidBody();
    void setPosition(vector3df Pos);
    vector3df getPosition();

    void FaceTarget(vector3df Destin);
    void MoveLocal(vector3df Velocity);
    void TryToCrashIntoPlayer(vector3df PlayerPos);
};

#endif // AI_H_INCLUDED
