#include <irrlicht.h>
#include <irrbullet.h>
#include <mecc.h>

// used namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CMecc::CMecc(IrrlichtDevice* GameDevice, ISceneManager* Gamesmgr, IVideoDriver* GameDriver, irrBulletWorld* GamePhysicsWorld, MastEventReceiver& GameEReceiver)
{

    GDevice = GameDevice;
    Gsmgr = Gamesmgr;
    GDriver = GameDriver;
    GPhysicsWorld = GamePhysicsWorld;
    GReceiver = &GameEReceiver;

    printf("mecc calling constructor\n");
    printf("adding mecc node\n");
    Node = Gsmgr->addAnimatedMeshSceneNode(Gsmgr->getMesh("./media/mecc.x"));
    Node->setMaterialFlag(EMF_LIGHTING,false);
    Node->setPosition(vector3df(0, 0, 0));
    Node->setScale(vector3df(20,20,20));

    ColShape = new IConvexHullShape(Node, Node->getMesh(), 80);
    ColShape->setMargin(0.07);

    ColRigidBody = GPhysicsWorld->addRigidBody(ColShape);
    ColRigidBody->setGravity(vector3df(0,-10,0));
    ColRigidBody->setDamping(0.25,0);
    ColRigidBody->setActivationState(EAS_DISABLE_DEACTIVATION);

    TPSCam = Gsmgr->addCameraSceneNode(0, vector3df(0.0f,0.0f,0.0f) , vector3df(0.0f,0.0f,0.0f), -1);

    Speed = 10;
    curState = SIdle;
    lastState = SIdle;

    Node->setJointMode(EJUOR_CONTROL);

    Idle();
}

CMecc::~CMecc(void)
{
    printf("mecc calling destructor\n");
    Node->remove();
}

void CMecc::removeNode()
{
    printf("mecc calling removeNode\n");
    Node->remove();
}

void CMecc::setState(eState newState)
{
    printf("mecc calling setState\n");
    lastState = curState;
    curState = newState;
}

CMecc::eState CMecc::getState()
{
    printf("mecc returning state\n");
    return curState;
}

void CMecc::setPosition(vector3df Pos)
{
    Node->setPosition(Pos);
}

vector3df CMecc::getPosition()
{
    return Node->getPosition();
}

IAnimatedMeshSceneNode* CMecc::getMesh()
{
    printf("mecc calling getMesh\n");
    return Node;
}

ICollisionShape* CMecc::getCollisionShape()
{
    printf("mecc calling getCollisionShape\n");
    return ColShape;
}

IRigidBody* CMecc::getRigidBody()
{
    return ColRigidBody;
}

ICameraSceneNode* CMecc::getCamera()
{
    return TPSCam;
}

void CMecc::gotoDestination(vector3df Destin)
{
    printf("mecc calling goto\n");

}

void CMecc::Move()
{
    lastVelocity = ColRigidBody->getLinearVelocity();
    Velocity = vector3df(0,0,0);
    matrix4 m;
    m.setRotationDegrees(Node->getRotation());
    /*m.transformVect(lastVelocity);
    m.transformVect(Velocity);
*/
//check for key input, move mecc when certain keys are pressed
    if(GReceiver->keyDown(KEY_KEY_W))
    {
        Velocity.X = Speed;
        Run();
    }
    else if(GReceiver->keyDown(KEY_KEY_S))
    {
        Velocity.X = -Speed;
        Run();
    }
/*
    else
    {
        lastVelocity.X = 0;
        m.transformVect(lastVelocity);
    }
*/
    if(GReceiver->keyDown(KEY_KEY_D))
    {
        Velocity.Z = -Speed;
        Run();
    }
    else if(GReceiver->keyDown(KEY_KEY_A))
    {
        Velocity.Z = Speed;
        Run();
    }
/*
    else
    {
        lastVelocity.Z = 0;
        m.transformVect(lastVelocity);
    }

    ColRigidBody->setLinearVelocity(lastVelocity);
*/
    MoveLocal(Velocity);
}

void CMecc::CameraControl()
{
    position2df cursorPos = GDevice->getCursorControl()->getRelativePosition();
    vector3df cameraPos = TPSCam->getAbsolutePosition();

    float change_x = ( cursorPos.X - 0.5 ) * 256.0f;
    float change_y = ( cursorPos.Y - 0.5 ) * 256.0f;
    CamDirection += change_x;
    CamZDirection -= change_y;
    if( CamZDirection <- 90)
        CamZDirection = -90;
    else
    if(CamZDirection > 90)
        CamZDirection = 90;
    GDevice->getCursorControl()->setPosition( 0.5f, 0.5f );

    printf("change_x: %5.1f change y: %5.1f CamD: %5.1f CamZD: %5.1f\n", change_x, change_y, CamDirection, CamZDirection);

    vector3df playerPos = Node->getPosition();

    float xf = playerPos.X - cos(CamDirection * PI / 180.0f) * 64.0f;
    float yf = playerPos.Y - sin(CamZDirection * PI / 180.0f) * 64.0f;
    float zf = playerPos.Z + sin(CamDirection * PI / 180.0f) * 64.0f;

    TPSCam->setPosition(vector3df(xf, yf, zf ));
    TPSCam->setTarget(vector3df(playerPos.X, playerPos.Y + 25.0f, playerPos.Z));
    matrix4 mat;
    mat.setRotationDegrees(vector3df(0,CamDirection,0));
    mat.setTranslation(Node->getPosition());
    ColRigidBody->setWorldTransform(mat);
}

void CMecc::Attack()
{
    printf("mecc calling Attack\n");
    setState(SAttack);
}

void CMecc::Run()
{
    printf("mecc calling Run\n");
    setState(SRun);
}

void CMecc::JetPack()
{
    printf("mecc calling Jetpack\n");
    setState(SJetPack);
}

void CMecc::Idle()
{
    printf("mecc calling Idle\n");
    setState(SIdle);
}

void CMecc::Fall()
{
    printf("mecc calling Fall\n");
    setState(SFall);
}

void CMecc::MoveLocal(vector3df velocity)
{
    matrix4 m;

    m.setRotationDegrees(Node->getRotation());

    m.transformVect(velocity);

    ColRigidBody->applyCentralImpulse(velocity);

}
