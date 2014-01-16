/*
  -----------------------------------------------------------------------------
  Filename:    MyBigBangApp.h
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
#ifndef __MyBigBangApp_h_
#define __MyBigBangApp_h_

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

typedef enum State {
     Ball_Entry, // rename to Ball_Entry
     Ball,      // rename to Ball
     BeforeBang_Entry,
     BeforeBang, // 
     BigBang_Entry,
     BigBang,
     GameOfLife_Entry,
     GameOfLife    
}State_t;
     

class MyNode
{
public:
     MyNode();     
     Ogre::SceneNode *scene_node() { return scene_node_; }
     void set_scene_node(Ogre::SceneNode *scene_node) { scene_node_ = scene_node; }
     Ogre::Entity *entity() { return ent_; }
     void set_entity(Ogre::Entity *ent) { ent_ = ent; }
     
     void reset_ball_animate();
     void ball_animate(int time);
     void before_bang(int time);
     
     void reset_game_of_life();
     void game_of_life(int time);          
     

     void kill() { dying_ = true; }
     bool is_dead() { if (x_size_ <= -size_step_) { return true; } else {return false;}}

protected:
     
     Ogre::Entity *ent_;
     Ogre::SceneNode *scene_node_;
     
     double x_size_;
     double y_size_;
     double z_size_;

     double max_size_;
     double size_step_;

     Ogre::Vector3 pos_;
     double x_phase_;
     double y_phase_;
     double z_phase_;

     double x_amp_;
     double y_amp_;
     double z_amp_;

     double x_freq_;
     double y_freq_;
     double z_freq_;

     bool dying_;

private:
};

class MyBigBangApp : public BaseApplication
{
public:
     MyBigBangApp(void);
     virtual ~MyBigBangApp(void);

     Ogre::RenderWindow * getWindow(void) { return mWindow; }
     OIS::Mouse * getMouse(void) { return mMouse; }
     OIS::Keyboard * getKeyboard(void) { return mKeyboard; }

protected:
     
     State_t state_;
     State_t next_state_;

     virtual void createScene(void);
     virtual void frame_loop();
     void game_of_life();
     void animate();

     void setup_GameOfLife();
     void setup_Ball();
     
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

#endif // #ifndef __MyBigBangApp_h_
