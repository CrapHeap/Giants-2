// mecc.h
#ifndef MECC_H_INCLUDED
#define MECC_H_INCLUDED

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

// class containing mecc character data
class CMecc
{
private:
    IrrlichtDevice* GDevice;
    ISceneManager* Gsmgr;
    IVideoDriver* GDriver;
    irrBulletWorld* GPhysicsWorld;
    MastEventReceiver* GReceiver;
    ICameraSceneNode* TPSCam;
    float CamDirection;
    float CamZDirection;

    int Speed;
    vector3df Velocity;
    vector3df lastVelocity;
    IAnimatedMeshSceneNode* Node;
    ICollisionShape* ColShape;
    IRigidBody* ColRigidBody;
    enum eState
    {
        SRun, SJetPack, SIdle, SAttack, SFall
    };
    eState curState;
    eState lastState;
public:
    CMecc(IrrlichtDevice* GDevice, ISceneManager* Gsmgr, IVideoDriver* GDriver, irrBulletWorld* GPhysicsWorld, MastEventReceiver& GameEReceiver);
    ~CMecc();

    void removeNode();

    void setState(eState newState);
    eState getState();

    IAnimatedMeshSceneNode* getMesh();
    IAnimatedMeshSceneNode* getNode();
    ICollisionShape* getCollisionShape();
    IRigidBody* getRigidBody();
    void setPosition(vector3df Pos);
    vector3df getPosition();
    ICameraSceneNode* getCamera();

    void gotoDestination(vector3df Destin);

    void Move();
    void CameraControl();

    void Idle();
    void Attack();
    void Run();
    void JetPack();
    void Fall();

    void MoveLocal(vector3df Velocity);
};
#endif // MECC_H_INCLUDED
