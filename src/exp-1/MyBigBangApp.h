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
#include <syllo_serial/serialib.h>

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

using std::cout;
using std::endl;

#define SYLLO_PI 3.14159265359
#define DEG_2_RAD (SYLLO_PI/180.0)
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
     GameOfLife,
     BlackHole_Entry,
     BlackHole
}State_t;
     
#define NUM_ROWS 50
#define NUM_COLS 50

#define BALL_ORIENT    (Ogre::Vector3(0,0,0))
#define BALL_POSITION  (Ogre::Vector3(0,0,1000))

#define BEFORE_BANG_ORIENT (Ogre::Vector3(0,0,0))
#define BEFORE_BANG_POSITION (Ogre::Vector3(0,0,1000))

#define BIGBANG_ORIENT (Ogre::Vector3(10,-10,0))
#define BIGBANG_POSITION (Ogre::Vector3(0,0,1000))

#define GOL_ORIENT (Ogre::Vector3(0,0,0))
#define GOL_POSITION (Ogre::Vector3(NUM_COLS/2*100, NUM_ROWS/2*100,3000))

#define BLACKHOLE_ORIENT (Ogre::Vector3(-30,45,-15))
#define BLACKHOLE_POSITION (Ogre::Vector3(-500,-500,1000))

class MyNode
{
public:
     MyNode();     
     Ogre::SceneNode *scene_node() { return scene_node_; }
     void set_scene_node(Ogre::SceneNode *scene_node) { scene_node_ = scene_node; }
     Ogre::Entity *entity() { return ent_; }
     void set_entity(Ogre::Entity *ent) { ent_ = ent; }
     
     void reset_ball_animate();
     void reset_beforebang_animate();
     void ball_animate(int time);
     void before_bang(int time);
     
     void reset_game_of_life();
     void game_of_life(int time, double gol_time_step);          
     

     void kill() { dying_ = true; }
     bool is_dead() { if (x_size_ <= -size_step_) { return true; } else {return false;}}

     void set_move_to_goal(bool move) { moving_to_goal_ = move; }
     void set_goal(Ogre::Vector3 goal) { goal_ = goal; }
     void move_to_goal_animate(int speed);
     bool goal_reached(int threshold);
     void breath(int time);
     
     void set_init_position(Ogre::Vector3 pos) { init_pos_ = pos; }
     Ogre::Vector3 init_position() { return init_pos_; }

protected:
     
     Ogre::Entity *ent_;
     Ogre::SceneNode *scene_node_;
     
     double x_size_;
     double y_size_;
     double z_size_;

     double max_size_;
     double size_step_;

     Ogre::Vector3 init_pos_;
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

     Ogre::Vector3 goal_;
     bool moving_to_goal_;        
     
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
     
     void set_cam_orient_goal(Ogre::Vector3 goal) { cam_orient_goal_ = goal; }
     void set_cam_pos_goal(Ogre::Vector3 goal) { cam_pos_goal_ = goal; }
     void set_cam_move_to_goal(bool enable) { cam_moving_to_goal_ = enable; cam_orienting_to_goal_ = enable; }
     void cam_move_to_goal_animate(double look_speed, int pos_speed);
     bool cam_goal_reached(int look_thresh, int pos_thresh);

     //Ogre::Vector3 getLookAt();

     void led_control(int num, bool enable);

protected:
 
     unsigned int gol_time_step_;
     int two_hands_missing_count_;

     serialib serial_;
     char txBuf[8];
     char rxBuf[8];
     bool serial_enable_;

     Ogre::Vector3 cam_lookat_goal_;
     Ogre::Vector3 cam_pos_goal_;
     Ogre::Vector3 cam_cur_lookat_;

     bool cam_moving_to_goal_;
     //bool cam_looking_at_goal_;

     Ogre::Vector3 cam_orient_goal_; //yaw, pitch, roll
     bool cam_orienting_to_goal_;

     State_t state_;
     State_t next_state_;

     virtual void createScene(void);
     virtual void frame_loop();
     void game_of_life();
     void animate();
     bool blackhole_complete();
     void setup_GameOfLife();
     void setup_BeforeBang();
     void setup_Ball();
     void setup_BigBang();
     void setup_BlackHole();

     int rows_;
     int cols_;

     GOL *gol_;
     Ogre::Timer gol_timer_;
     Ogre::Timer animate_timer_;

     Ogre::Timer state_timer_;

     std::map<std::string,Ogre::MaterialPtr> colors_;
     
     int frame_;

     double pitch_;

     void *leapglue_;
     typedef bool (*poll_frame_t)(LeapPacket_t&);
     poll_frame_t poll_frame_;
     LeapPacket_t leap_packet_;
     LeapPacket_t prev_leap_packet_;
     bool prev_hand_present_;
     bool prev_two_hands_present_;

};

std::string color_number(double r, double g, double b);

#endif // #ifndef __MyBigBangApp_h_
