#include <irrlicht.h>
#include <irrbullet.h>
#include <AI.h>

// used namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

CAIDude::CAIDude(IrrlichtDevice* GameDevice, ISceneManager* Gamesmgr, IVideoDriver* GameDriver, irrBulletWorld* GamePhysicsWorld)
{
    GDevice = GameDevice;
    Gsmgr = Gamesmgr;
    GDriver = GameDriver;
    GPhysicsWorld = GamePhysicsWorld;

    printf("AI calling constructor\n");
    printf("adding AI node\n");
    Node = Gsmgr->addAnimatedMeshSceneNode(Gsmgr->getMesh("./media/mecc.obj"));
    Node->setMaterialFlag(EMF_LIGHTING,false);
    Node->setPosition(vector3df(2900*2,255*2,2600*2));

    ColShape = new IConvexHullShape(Node, Node->getMesh(), 200);
    ColShape->setMargin(0.07);

    ColRigidBody = GPhysicsWorld->addRigidBody(ColShape);
    ColRigidBody->setGravity(vector3df(0,-10,0));

    Speed = 100;
}

CAIDude::~CAIDude()
{
    printf("AI calling destructor\n");
    Node->remove();
}

void CAIDude::removeNode()
{
    Node->remove();
}

IAnimatedMeshSceneNode* CAIDude::getMesh()
{
    return Node;
}

IAnimatedMeshSceneNode* CAIDude::getNode()
{
    return Node;
}

ICollisionShape* CAIDude::getCollisionShape()
{
    return ColShape;
}

IRigidBody* CAIDude::getRigidBody()
{
    return ColRigidBody;
}

void CAIDude::setPosition(vector3df Pos)
{
    Node->setPosition(Pos);
}

vector3df CAIDude::getPosition()
{
       return Node->getPosition();
}

void CAIDude::FaceTarget(vector3df Target)
{
    ColRigidBody->faceTarget(Target);
}

void CAIDude::MoveLocal(vector3df Velocity)
{
    matrix4 m;

    m.setRotationDegrees(Node->getRotation());

    m.transformVect(Velocity);

    ColRigidBody->setLinearVelocity(Velocity);
}

void CAIDude::TryToCrashIntoPlayer(vector3df PlayerPos)
{
    FaceTarget(PlayerPos);
    MoveLocal(vector3df(Speed,0,0));
}
