/*
  -----------------------------------------------------------------------------
  Filename:    TutorialApplication.cpp
  -----------------------------------------------------------------------------

  This source file is part of the
  ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
  //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
  / \_// (_| | | |  __/  \  /\  /| |   <| |
  \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
  |___/                              
  Tutorial Framework
  http://www.ogre3d.org/tikiwiki/
  -----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"
#include <OgreSphere.h>


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#   include <macUtils.h>
#   include "AppDelegate.h"
#endif

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
     mTimer = OGRE_NEW Ogre::Timer();
     mTimer->reset();
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
     mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
     
     //Ogre::Entity* ogreHead2 = mSceneMgr->createEntity( "Head2", "ogrehead.mesh" );
     //Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "HeadNode2", Ogre::Vector3( 100, 0, 0 ) );
     //headNode2->attachObject( ogreHead2 );     
     
     Ogre::Light* light = mSceneMgr->createLight( "MainLight" );
     light->setPosition(20, 80, 50);
     
     int rows = 50;
     int cols = 50;
     for (int r = 0; r < rows; r++) {
          for (int c = 0 ; c < cols; c++) {
               std::stringstream ss_r, ss_c;
               ss_r << r;
               ss_c << c;

               std::string name = "mySphere" + ss_r.str() + "_" + ss_c.str();
               Ogre::Entity * mBall = mSceneMgr->createEntity(name, Ogre::SceneManager::PT_SPHERE);
               Ogre::SceneNode *ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

               //mBall->setMaterialName("Examples/Ice");
               ballNode->attachObject(mBall);
               ballNode->setPosition(Ogre::Vector3(c*100,r*100,0));
               ballNode->setScale(Ogre::Vector3(1,1,1)); // Radius, in theory.
          }
     }         

     ////Ogre::Sphere* sphere(Ogre::Vector3( 100, 100, 0 ), 50);
     //Ogre::Entity* sphereEntity = mSceneMgr->createEntity("mySphere", Ogre::SceneManager::PT_SPHERE);
     //Ogre::SceneNode* sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
     //sphereNode->attachObject(sphereEntity);     
     //
     //double radius = sphereEntity->getBoundingRadius(); 
     ////sphereNode->scale(radius*10, radius*10, radius*10);
     //sphereNode->scale(100, 100, 100);
     //
     ////Ogre::Materiaal * material = Ogre::MaterialManager::create("SphereMaterial", "group");
     //Ogre::MaterialPtr RobotMaterialPtr = Ogre::MaterialManager::getSingleton().create("RobotSphereMaterial","group"); 
     ////RobotMaterialPtr->setSelfIllumination(1,0,0); 
     ////sphereEntity->setMaterialName("RobotSphereMaterial"); 
     //
     //
     ////Ogre::SceneNode* sphereNode = mSceneMgr->create
     ////createEntity(Ogre::Vector3( 100, 100, 0 ), 50);
}

void TutorialApplication::frame_loop()
{
     Ogre::Entity * ent = mSceneMgr->getEntity("mySphere5_5");
     Ogre::Node * node = ent->getParentNode();
     Ogre::Vector3 pos = node->getPosition();
     node->setPosition(pos.x, pos.y, pos.z+1);
}
