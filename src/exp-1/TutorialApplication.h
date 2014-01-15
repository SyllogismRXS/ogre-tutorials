/*
  -----------------------------------------------------------------------------
  Filename:    TutorialApplication.h
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
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include <iostream>
#include <BaseApplication/BaseApplication.h>
#include <LeapGlue/LeapGlue.h>
#include <gol/GOL.h>

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

using std::cout;
using std::endl;

#define SYLLO_PI 3.14159265359
#define COLOR_STEP 0.05
#define COLOR_RAND_MAX ((int)(1.0/COLOR_STEP))

class MyNode
{
public:
     MyNode();     
     Ogre::SceneNode *scene_node() { return scene_node_; }
     void set_scene_node(Ogre::SceneNode *scene_node) { scene_node_ = scene_node; }
     Ogre::Entity *entity() { return ent_; }
     void set_entity(Ogre::Entity *ent) { ent_ = ent; }
     void step_animate(int time);
     void reset();

     void kill() { dying_ = true; }
     bool is_dead() { if (x_size_ <= -size_step_) { return true; } else {return false;}}

protected:
     
     Ogre::Entity *ent_;
     Ogre::SceneNode *scene_node_;
     //std::string color_name_;

     double x_size_;
     double y_size_;
     double z_size_;

     double max_size_;
     double size_step_;

     Ogre::Vector3 pos_;
     double x_phase_;
     double y_phase_;
     double z_phase_;

     bool dying_;

private:
};

class TutorialApplication : public BaseApplication
{
public:
     TutorialApplication(void);
     virtual ~TutorialApplication(void);

     Ogre::RenderWindow * getWindow(void) { return mWindow; }
     Ogre::Timer * getTimer(void) { return mTimer; }
     OIS::Mouse * getMouse(void) { return mMouse; }
     OIS::Keyboard * getKeyboard(void) { return mKeyboard; }
protected:
     virtual void createScene(void);
     virtual void frame_loop();
     Ogre::Timer *mTimer;

     int rows_;
     int cols_;

     GOL *gol_;
     Ogre::Timer gol_timer_;
     Ogre::Timer animate_timer_;

     std::map<std::string,Ogre::MaterialPtr> colors_;
     
     int frame_;

     double pitch_;

     void *leapglue_;
     typedef bool (*poll_frame_t)(LeapPacket_t&);
     poll_frame_t poll_frame_;
     LeapPacket_t leap_packet_;
     LeapPacket_t prev_leap_packet_;
     
};

std::string color_number(double r, double g, double b);

#endif // #ifndef __TutorialApplication_h_
