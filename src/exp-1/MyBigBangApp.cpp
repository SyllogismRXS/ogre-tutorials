/*
  -----------------------------------------------------------------------------
  Filename:    MyBigBangApp.cpp
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
#include "MyBigBangApp.h"
#include <OgreSphere.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#   include <macUtils.h>
#   include "AppDelegate.h"
#endif

using std::cout;
using std::endl;

double angle_360(double angle)
{
     if (angle >= 360) {
          angle -= 360*floor(angle/360.0);
     }

     if (angle < 0) {
          angle += 360*ceil(abs(angle)/360.0);
     }
     return angle;
}


MyNode::MyNode()
{
     max_size_ = 1;
     size_step_ = 0.01;         
     moving_to_goal_ = false;
}

void MyNode::reset_ball_animate()
{    
     dying_ = false;

     x_size_ = 0;
     y_size_ = 0;
     z_size_ = 0;

     pos_ = scene_node_->getPosition();     
     
     //x_amp_ = (rand() % max_amp) - max_amp / 2.0;
     //y_amp_ = (rand() % max_amp) - max_amp / 2.0;
     //z_amp_ = (rand() % max_amp) - max_amp / 2.0;     
          
     //x_freq_ = (rand() % max_freq);
     //y_freq_ = (rand() % max_freq);
     //z_freq_ = (rand() % max_freq);     
    
     // Types of early entities:
     // 1. Perfect circles
     //    same phases, same amps, same freq
     // 2. Ellipses
     //    same phases, different amps, same freq
     // 3. Crazy entities
     //    different phases, amps, freqs
     
     int max_amp = 500;
     int max_freq = 1;
     //double freq = 0.2;

     int type = rand() % 100 + 1;    
     if (type >= 95  && type <= 100) {
          // Crazy entities          
          x_phase_ = (rand() % 314) / 100.0;
          y_phase_ = (rand() % 314) / 100.0;
          z_phase_ = (rand() % 314) / 100.0;
     
          x_amp_ = (rand() % max_amp) - max_amp / 2.0;
          y_amp_ = (rand() % max_amp) - max_amp / 2.0;
          z_amp_ = (rand() % max_amp) - max_amp / 2.0;
     
          x_freq_ = rand() % (max_freq*5);
          y_freq_ = rand() % (max_freq*5);
          z_freq_ = rand() % (max_freq*5);
     } else if (type >= 80 && type <= 90) {
          // Ellipses          
          // Perfect circle
          x_phase_ = (rand() % 314) / 100.0;
          y_phase_ = x_phase_;
          z_phase_ = x_phase_;
     
          double amp_multi = 2;
          x_amp_ = (rand() % max_amp*amp_multi) - max_amp*amp_multi / 2.0;
          y_amp_ = (rand() % max_amp*amp_multi) - max_amp*amp_multi / 2.0;;
          z_amp_ = (rand() % max_amp*amp_multi) - max_amp*amp_multi / 2.0;

          //x_freq_ = rand() % max_freq;
          x_freq_ = (rand() % 300) / 100.0 - 1.5;
          y_freq_ = x_freq_;
          z_freq_ = x_freq_;
     } else {          
          // Perfect circle
          x_phase_ = (rand() % 314) / 100.0;
          y_phase_ = x_phase_;
          z_phase_ = x_phase_;
     
          x_amp_ = (rand() % max_amp) - max_amp / 2.0;
          y_amp_ = x_amp_;
          z_amp_ = (rand() % max_amp) - max_amp / 2.0;

          //x_freq_ = rand() % max_freq;
          x_freq_ = (rand() % 200) / 100.0 - 1.0;
          y_freq_ = x_freq_;
          z_freq_ = x_freq_;
     }      
     
     //double color_r = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     //double color_g = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     //double color_b = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     ent_->setMaterialName(color_number(0,0,1.0));
     //scene_node_->setScale(Ogre::Vector3(max_size_,max_size_,max_size_));
     //ent_->setVisible(true);
}

void MyNode::reset_beforebang_animate()
{    
     scene_node_->setScale(Ogre::Vector3(max_size_,max_size_,max_size_));
     ent_->setVisible(true);
}

void MyNode::reset_game_of_life()
{    
     dying_ = false;

     x_size_ = 0;
     y_size_ = 0;
     z_size_ = 0;

     pos_ = scene_node_->getPosition();
               
     x_phase_ = (rand() % 314) / 100.0;
     y_phase_ = (rand() % 314) / 100.0;
     z_phase_ = (rand() % 314) / 100.0;
     
     x_amp_ = (rand() % 100) / 100.0 - 0.5;
     y_amp_ = (rand() % 100) / 100.0 - 0.5;
     z_amp_ = (rand() % 100) / 100.0 - 0.5;

     //x_freq_ = rand() % max_freq;
     x_freq_ = (rand() % 200) / 100.0 - 1.0;
     y_freq_ = x_freq_;
     z_freq_ = x_freq_;
     
     //double color_r = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     //double color_g = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     //double color_b = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     ent_->setMaterialName(color_number(0,0,1.0));
     scene_node_->setScale(Ogre::Vector3(max_size_,max_size_,max_size_));
     ent_->setVisible(true);
}


void MyNode::game_of_life(int time)
{
     if (dying_) {
          if (x_size_ > -size_step_) {
               x_size_ -= size_step_*3;
               y_size_ -= size_step_*3;
               z_size_ -= size_step_*3;
          }
     } else {
          if (x_size_ < max_size_) {
               x_size_ += size_step_;
               y_size_ += size_step_;
               z_size_ += size_step_;          
          }
     }
     scene_node_->setScale(Ogre::Vector3(x_size_,y_size_,z_size_));
     
     double t = (time % 1000) / 1000.0;
     pos_.x += 0.4*sin(2*SYLLO_PI*t + x_phase_);
     pos_.y += 0.5*sin(2*SYLLO_PI*t + y_phase_);     
     pos_.z += 0.4*sin(2*SYLLO_PI*t + z_phase_);
     //double t = time / 1000.0;     
     //pos_.x += x_amp_*sin(2*SYLLO_PI*x_freq_*t + x_phase_);
     //pos_.y += y_amp_*cos(2*SYLLO_PI*y_freq_*t + y_phase_);
     //pos_.z += z_amp_*sin(2*SYLLO_PI*z_freq_*t + z_phase_);
     scene_node_->setPosition(pos_.x, pos_.y, pos_.z);
}

void MyNode::breath(int time)
{
     double t = (time % 1000) / 1000.0;
     pos_.x += 0.4*sin(2*SYLLO_PI*t + x_phase_);
     pos_.y += 0.5*sin(2*SYLLO_PI*t + y_phase_);     
     pos_.z += 0.4*sin(2*SYLLO_PI*t + z_phase_);
     //double t = time / 1000.0;     
     //pos_.x += x_amp_*sin(2*SYLLO_PI*x_freq_*t + x_phase_);
     //pos_.y += y_amp_*cos(2*SYLLO_PI*y_freq_*t + y_phase_);
     //pos_.z += z_amp_*sin(2*SYLLO_PI*z_freq_*t + z_phase_);
     scene_node_->setPosition(pos_.x, pos_.y, pos_.z);
}

void MyNode::ball_animate(int time)
{
     //double t = (time % 1000) / 1000.0;     
     //double t = (time % 1000) / 1000.0;
     double t = time / 1000.0;
     //double t = (time % 1000) / 10.0;     
     //double t = time;
     //pos_.x += x_amp_*sin(2*SYLLO_PI*x_freq_*t + x_phase_);
     //pos_.y += y_amp_*sin(2*SYLLO_PI*y_freq_*t + y_phase_);
     //pos_.z += z_amp_*sin(2*SYLLO_PI*z_freq_*t + z_phase_);
     pos_.x = x_amp_*sin(2*SYLLO_PI*x_freq_*t + x_phase_);
     pos_.y = y_amp_*cos(2*SYLLO_PI*y_freq_*t + y_phase_);
     pos_.z = z_amp_*sin(2*SYLLO_PI*z_freq_*t + z_phase_);
     scene_node_->setPosition(pos_.x, pos_.y, pos_.z);     
}

void MyNode::move_to_goal_animate(int speed)
{
     Ogre::Vector3 diff_vec = goal_ - pos_;
     double dist_to_goal = pos_.distance(goal_);

     Ogre::Vector3 unit_vec;
     if (dist_to_goal > 0.1) {
          unit_vec = diff_vec / dist_to_goal;
     } else {
          unit_vec = Ogre::Vector3(0,0,0);
          pos_ = goal_;
     }
     
     pos_ += unit_vec*speed;
     scene_node_->setPosition(pos_);
}

bool MyNode::goal_reached(int threshold)
{
     if (!moving_to_goal_) { return true; }
     
     if (pos_.distance(goal_) < threshold) {
          moving_to_goal_ = false;
          return true;
     }
     return false;
}

//-------------------------------------------------------------------------------------
MyBigBangApp::MyBigBangApp(void)
{
     srand(time(NULL));
     
     two_hands_missing_count_ = 0;

     // connect to Arduino
     if (serial_.Open("/dev/ttyACM0", 115200) != 1) {
          cout << "Failed to open serial port!" << endl;
          serial_enable_ = false;
     }
     serial_.FlushReceiver();
     
     serial_enable_ = true;
     int try_count = 0;
     rxBuf[0] = 0;    
     while (rxBuf[0] != 'A') {
          if(try_count >= 20) {
               cout << "Failed to communicate with LED controller" << endl;
               serial_enable_ = false;
               break;
          }
          
          txBuf[0] = 'a';     
          if (serial_.Write(txBuf,1) != 1) {
               cout << "Failed during write" << endl;
          }
          if (serial_.ReadChar(rxBuf,0) != 1) {
               cout << "Failed during read" << endl;
          }
          if (rxBuf[0] != 'A') {
               cout << "Failed to receive Acknowledge" << endl;
          }
          try_count++;
          serial_.FlushReceiver();                    
     }

     led_control(0,false);
     led_control(1,false);
     
     rows_ = NUM_ROWS;
     cols_ = NUM_COLS;

     frame_ = 0;

     state_ = Ball_Entry;
     next_state_ = state_;

     gol_timer_.reset();
     animate_timer_.reset();

     gol_ = new GOL(cols_, rows_);
     gol_->randomize();          
}
//-------------------------------------------------------------------------------------
MyBigBangApp::~MyBigBangApp(void)
{
     delete gol_;

     // close the library
     dlclose(leapglue_);     
}

void MyBigBangApp::led_control(int num, bool enable)
{
     if (!serial_enable_) {
          return;
     }
     
     if (num == 0) {
          if (enable) {
               txBuf[0] = 'q';
          } else {
               txBuf[0] = 'a';
          }                    
     } else if (num == 1) {
          if (enable) {
               txBuf[0] = 'w';
          } else {
               txBuf[0] = 's';
          }
     }
     
     if (serial_.Write(txBuf,1) != 1) {
          cout << "Failed during write" << endl;
     }
     if (serial_.ReadChar(rxBuf,1000) != 1) {
          cout << "Failed during read" << endl;
     }
}

void MyBigBangApp::setup_Ball()
{
     //mCamera->setPosition(Ogre::Vector3(0, 0 ,2000));
     
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               node = (MyNode*)(gol_->at(x,y).data());
               
               //Ogre::SceneNode *scene_node;
               //scene_node = node->scene_node();
               //scene_node->setPosition(Ogre::Vector3(0,0,0));
               node->set_goal(Ogre::Vector3(0,0,0));               
               node->set_move_to_goal(true);
               node->reset_ball_animate();               
          }
     }

     set_cam_orient_goal(BALL_ORIENT);
     set_cam_pos_goal(BALL_POSITION);
     set_cam_move_to_goal(true);
}

void MyBigBangApp::setup_BlackHole()
{
     //mCamera->setPosition(Ogre::Vector3(0, 0 ,2000));
     
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               node = (MyNode*)(gol_->at(x,y).data());
               
               //Ogre::SceneNode *scene_node;
               //scene_node = node->scene_node();
               //scene_node->setPosition(Ogre::Vector3(0,0,0));
               node->set_goal(Ogre::Vector3(0,0,0));               
               node->set_move_to_goal(true);
               node->reset_ball_animate();               
          }
     }

     //set_cam_orient_goal(Ogre::Vector3(cols_/2*100, rows_/2*100,-300));
     set_cam_orient_goal(BLACKHOLE_ORIENT);
     set_cam_pos_goal(BLACKHOLE_POSITION);
     set_cam_move_to_goal(true);
}


int sign(int x) {
    return (x > 0) - (x < 0);
}

void MyBigBangApp::setup_BeforeBang()
{
     //mCamera->setPosition(Ogre::Vector3(0, 0 ,2000));
     
     int radius = 1000;
     int inner_radius = 500;
     int thickness = radius - inner_radius;
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               node = (MyNode*)(gol_->at(x,y).data());
               
               //Ogre::SceneNode *scene_node;
               //scene_node = node->scene_node();
               //scene_node->setPosition(Ogre::Vector3(0,0,0));
               
               double x_goal = ((rand() % (thickness*2)) - thickness);// + inner_radius;
               double y_goal = ((rand() % (thickness*2)) - thickness);// + inner_radius;
               double z_goal = ((rand() % (thickness*2)) - thickness);// + inner_radius;

               x_goal += sign(x_goal)*inner_radius;
               y_goal += sign(y_goal)*inner_radius;
               z_goal += sign(z_goal)*inner_radius;               

               node->set_goal(Ogre::Vector3(x_goal, y_goal, z_goal));
               node->set_move_to_goal(true);
               node->reset_beforebang_animate();
               //node->reset_ball_animate();               
          }
     }
     
     //set_cam_orient_goal(BEFORE_BANG_ORIENT);
     //set_cam_pos_goal(BEFORE_BANG_POSITION);
     //set_cam_move_to_goal(true);     

     //set_cam_orient_goal(Ogre::Vector3(0,0,0));
     //set_cam_pos_goal(Ogre::Vector3(0,0,1200));
     //set_cam_move_to_goal(true);     
}

void MyBigBangApp::setup_BigBang()
{
     //mCamera->setPosition(Ogre::Vector3(0, 0 ,2000));
     
     int distance = 7000;
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               node = (MyNode*)(gol_->at(x,y).data());
               
               Ogre::SceneNode *scene_node;
               scene_node = node->scene_node();
               //scene_node->setPosition(Ogre::Vector3(0,0,0));
               Ogre::Vector3 cur_pos = scene_node->getPosition();

               double x_goal = ((rand() % (distance*2)) - distance);
               double y_goal = ((rand() % (distance*2)) - distance);
               double z_goal = ((rand() % (distance*2)) - distance);

               x_goal += cur_pos.x + sign(x_goal);
               y_goal += cur_pos.y + sign(y_goal);
               z_goal += cur_pos.z + sign(z_goal);

               node->set_goal(Ogre::Vector3(x_goal, y_goal, z_goal));
               node->set_move_to_goal(true);
               //node->reset_ball_animate();               
          }
     }
     state_timer_.reset();


     //set_cam_orient_goal(BIGBANG_ORIENT);
     //set_cam_pos_goal(BIGBANG_POSITION);
     //set_cam_move_to_goal(true);          
}

void MyBigBangApp::setup_GameOfLife()
{
     //mCamera->setPosition(Ogre::Vector3(cols_/2*100, rows_/2*100 ,2000));
     
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;               
               node = (MyNode*)(gol_->at(x,y).data());               

               //Ogre::SceneNode *scene_node;
               //scene_node = node->scene_node();
               //scene_node->setPosition(Ogre::Vector3(x*100,y*100,0));
               node->set_goal(node->init_position());
               node->reset_game_of_life();
          }
     }
     state_timer_.reset();

     set_cam_orient_goal(GOL_ORIENT);
     set_cam_pos_goal(GOL_POSITION);
     set_cam_move_to_goal(true);
}

//-------------------------------------------------------------------------------------
void MyBigBangApp::createScene(void)
{
     // Create map of colors:
     for(double r = 0; r <= 1.05; r += COLOR_STEP) {
          for(double g= 0; g <= 1.05; g += COLOR_STEP) {
               for(double b = 0; b <= 1.05; b += COLOR_STEP) {
                    std::string name = color_number(r,g,b);

                    if (colors_.count(name) == 0) {                          
                         cout << name << endl;
                         Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                         mat->setDiffuse(Ogre::ColourValue(r,g,b));               
                         colors_[name] = mat;
                    }
               }
          }
     }

     mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1f, 0.1f, 0.1f));
     
     Ogre::Light* light = mSceneMgr->createLight( "MainLight" );
     light->setPosition(20, 80, 50);
     
     Ogre::Light* light_second = mSceneMgr->createLight( "SecondLight" );
     light_second->setPosition(cols_/2*100, rows_/2*100,1000);          
     
     mCamera->lookAt(Ogre::Vector3(0,0,0));
     mCamera->setPosition(Ogre::Vector3(0, 0 ,2000));
          
     for (int r = 0; r < rows_; r++) {
          for (int c = 0 ; c < cols_; c++) {
               std::stringstream ss_r, ss_c;
               ss_r << r;
               ss_c << c;
               
               std::string name = "mySphere" + ss_r.str() + "_" + ss_c.str();
               Ogre::Entity * mBall = mSceneMgr->createEntity(name, Ogre::SceneManager::PT_SPHERE);
               Ogre::SceneNode *ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                              
               mBall->setMaterialName(color_number(0,0,1.0));               
               ballNode->attachObject(mBall);
               //ballNode->setPosition(Ogre::Vector3(c*100,r*100,0));
               ballNode->setPosition(Ogre::Vector3(0,0,0));
               ballNode->setScale(Ogre::Vector3(1,1,1)); // Radius, in theory.
               
               MyNode *node = new MyNode();
               node->set_init_position(Ogre::Vector3(c*100,r*100,0));
               node->set_entity(mBall);
               node->set_scene_node(ballNode);
               gol_->at(c,r).set_data((void*)node);
               //node->reset_ball_animate();               
               //node->reset_game_of_life();
          }
     } 
     
     // load the LeapGlue Library
     leapglue_ = dlopen("../lib/libLeapGlue.so", RTLD_LAZY);
     if (!leapglue_) {
          std::cerr << "Cannot load library: " << dlerror() << '\n';
          return ;
     }

     // reset errors
     dlerror();         
     
     poll_frame_ = (poll_frame_t) dlsym(leapglue_, "poll_frame");
     const char *dlsym_error = dlerror();
     if (dlsym_error) {
          std::cerr << "Cannot load symbol 'poll_frame': " << dlsym_error <<
               '\n';
          dlclose(leapglue_);
          return;
     }             
}

void MyBigBangApp::animate()
{
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               //Ogre::Entity * ent;
               node = (MyNode*)(gol_->at(x,y).data());
               //ent = node->entity();
               
               switch(state_) {
               case Ball:
                    if (node->goal_reached(200)) {
                         node->ball_animate(animate_timer_.getMilliseconds());
                    } else {
                         node->move_to_goal_animate(3);
                    }
                    break;                    
               case BeforeBang:
                    if (node->goal_reached(20)) {
                         node->breath(animate_timer_.getMilliseconds());
                    } else {
                         node->move_to_goal_animate(7);
                    }                                        
                    break;
               case BigBang:
                    node->move_to_goal_animate(5);
                    node->breath(animate_timer_.getMilliseconds());
                    break;
               case GameOfLife:
                    cout << "Error: shouldn't happen" << endl;
                    break;
               case BlackHole:
                    if (node->goal_reached(200)) {
                         node->ball_animate(animate_timer_.getMilliseconds());
                    } else {
                         node->move_to_goal_animate(3);
                    }
               default:
                    break;
               }
               
          }                         
     }
}

bool MyBigBangApp::blackhole_complete()
{
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               //Ogre::Entity * ent;
               //ent = node->entity();
               node = (MyNode*)(gol_->at(x,y).data());
               
               if (!node->goal_reached(200)) {
                    return false;
               }
          }
     }
     return true;
}

void MyBigBangApp::game_of_life()
{
     bool update_gol = false;
     if (gol_timer_.getMilliseconds() > 4000) {
          gol_timer_.reset();
          update_gol = true;
     }

     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               Ogre::Entity * ent;
               node = (MyNode*)(gol_->at(x,y).data());
               ent = node->entity();
               
               if (!node->goal_reached(15)) {
                    node->move_to_goal_animate(15);
                    update_gol = false;
               } else {
                    node->game_of_life(animate_timer_.getMilliseconds());

                    if (update_gol) {                    
                         if (gol_->at(x,y).grid_type() == 1) {
                              ent->setVisible(true);
                              if (gol_->at(x,y).is_new()) {
                                   node->reset_game_of_life();
                              }
                         } else {
                              node->kill();    
                              ent->setMaterialName(color_number(1.0,0,0));                         
                         }                    
                    }
               
                    if (node->is_dead()) {
                         ent->setVisible(false);
                    }
               }
          }                         
     }

     if (update_gol) {
          gol_->step();
     }
}

//Ogre::Vector3 MyBigBangApp::getLookAt()
//{
//     //Ogre::Vector3 result;     
//     //result = mCamera->getPosition() + mCamera->getDirection() * 10;
//     //result.z = 0;     
//     //return result;
//     return mCamera->getPosition() + mCamera->getDirection() * 10;               
//}

void MyBigBangApp::cam_move_to_goal_animate(double look_speed, int pos_speed)
{
     if (cam_moving_to_goal_) {
          // Position "move to" logic
          Ogre::Vector3 pos_diff = cam_pos_goal_ - mCamera->getPosition();     
          double dist_to_goal = mCamera->getPosition().distance(cam_pos_goal_);
     
          Ogre::Vector3 pos_unit_vec;
          if (dist_to_goal > 0.1) {
               pos_unit_vec = pos_diff / dist_to_goal;
          } else {
               pos_unit_vec = Ogre::Vector3(0,0,0);
               mCamera->setPosition(cam_pos_goal_);
          }
          mCamera->setPosition(mCamera->getPosition() + pos_unit_vec*pos_speed);
     }

     if (cam_orienting_to_goal_) {
          Ogre::Quaternion quat = mCamera->getOrientation();
                    
          double gain = 1.0 / 20.0;

          double yaw_curr = quat.getYaw().valueDegrees();
          double yaw_goal = cam_orient_goal_.x;          
          double yaw_step = gain * abs((yaw_curr) - (yaw_goal));
          if (((int)(angle_360(yaw_curr) - angle_360(yaw_goal) + 360) % 360) < 180) {
               yaw_step *= -1;
          }

          double pitch_curr = quat.getPitch().valueDegrees();
          double pitch_goal = cam_orient_goal_.y;          
          double pitch_step = gain * abs((pitch_curr) - (pitch_goal));
          if (((int)(angle_360(pitch_curr) - angle_360(pitch_goal) + 360) % 360) < 180) {
               pitch_step *= -1;
          }

          double roll_curr = quat.getRoll().valueDegrees();
          double roll_goal = cam_orient_goal_.z;          
          double roll_step = gain * abs((roll_curr) - (roll_goal));
          if (((int)(angle_360(roll_curr) - angle_360(roll_goal) + 360) % 360) < 180) {
               roll_step *= -1;
          }
          
          mCamera->yaw(Ogre::Radian(yaw_step*SYLLO_PI/180.0));
          mCamera->pitch(Ogre::Radian(pitch_step*SYLLO_PI/180.0));          
          mCamera->roll(Ogre::Radian(roll_step*SYLLO_PI/180.0));
          
          if (yaw_step < 0.01 && pitch_step < 0.01 && roll_step < 0.01) {
               cam_orienting_to_goal_ = false;
          }

     }          
}

bool MyBigBangApp::cam_goal_reached(int look_thresh, int pos_thresh)
{
     if (cam_moving_to_goal_) {
          if ((mCamera->getPosition().distance(cam_pos_goal_)) < pos_thresh) {
               cam_moving_to_goal_ = false;
          }
     }
          
     return !cam_moving_to_goal_ && !cam_orienting_to_goal_;
}

void MyBigBangApp::frame_loop()
{    
     bool hand_present = false;
     bool two_hands_present = false;

     double pitch_diff = 0;
     double yaw_diff = 0;
     double roll_diff = 0;
     double move_diff = 0;
     
     int fingers_required = 2;

     ////////////////////////////////////////////////////////////////////////
     // Handle Leap Motion Packet
     ////////////////////////////////////////////////////////////////////////
     if ((*poll_frame_)(leap_packet_)) {          
          if (leap_packet_.valid && prev_leap_packet_.valid) {               
               //if (leap_packet_.hands >= 1) {
               if (leap_packet_.first.fingers >= fingers_required) {
                    hand_present = true;
                              
                    pitch_diff = leap_packet_.first.pitch;
                    yaw_diff = 0 - leap_packet_.first.yaw;
                    roll_diff = leap_packet_.first.roll;
                    
                    //if (prev_leap_packet_.hands > 0) {
                    if (prev_leap_packet_.first.fingers >= fingers_required) {
                         pitch_diff = leap_packet_.first.pitch - prev_leap_packet_.first.pitch;
                         yaw_diff = prev_leap_packet_.first.yaw - leap_packet_.first.yaw;
                         roll_diff = leap_packet_.first.roll - prev_leap_packet_.first.roll;                    
                         
                         //mCamera->pitch(Ogre::Radian(pitch_diff*SYLLO_PI/180.0));
                         //mCamera->yaw(Ogre::Radian(yaw_diff*SYLLO_PI/180.0));
                         //mCamera->roll(Ogre::Radian(roll_diff*SYLLO_PI/180.0));
                    } 
                    if (leap_packet_.hands > 1) {
                         if (leap_packet_.second.avg_pos.z > 40) {
                              move_diff = 5;
                         } else if (leap_packet_.second.avg_pos.z < -40) {
                              move_diff = -5;
                         }
                    }
               }               

               if (leap_packet_.first.fingers >= fingers_required && leap_packet_.second.fingers >= fingers_required) {
                    two_hands_present = true;
               }
          }          
     }     

     if (hand_present != prev_hand_present_) {
          if (hand_present) {
               led_control(0,true);
          } else {
               led_control(0,false);
          }
     }

     if (two_hands_present != prev_two_hands_present_) {
          if (two_hands_present) {
               led_control(1,true);
          } else {
               led_control(1,false);
          }
     }
     
     // REALLY COOL ROTATION EFFECT!
     //if ((*poll_frame_)(leap_packet_)) {          
     //     if (leap_packet_.hands > 0) {
     //          pitch_ = 0;
     //          //cout << "Pitch: " << leap_packet_.first.pitch << endl;               
     //          //mCamera->pitch(Ogre::Radian(leap_packet_.first.pitch*SYLLO_PI/180.0));
     //     }
     //}
     ////mCamera->pitch(Ogre::Radian(pitch_*SYLLO_PI/180.0));
     //mCamera->roll(Ogre::Radian(pitch_*SYLLO_PI/180.0));     

     //if (state_ == GameOfLife) {          
     //     this->game_of_life();
     //} else {          
     //     this->animate();
     //}
     
     bool allow_hand_look = false;

     switch(state_) {
     case Ball_Entry:
          this->setup_Ball();
          next_state_ = Ball;          
          break;
     case Ball:                    
          this->animate();          
          
          if (hand_present) {
               next_state_ = BeforeBang_Entry;
          }           
          break;
          
     case BeforeBang_Entry:
          this->setup_BeforeBang();
          next_state_ = BeforeBang;
          break;
          
     case BeforeBang:          
          this->animate();

          if (!hand_present) {               
               next_state_ = Ball_Entry;
          }
          if (two_hands_present) {               
               next_state_ = BigBang_Entry;
          }
          break;

     case BigBang_Entry:
          this->setup_BigBang();
          next_state_ = BigBang;
          break;

     case BigBang:                    
          this->animate();
          if (!two_hands_present) {
               two_hands_missing_count_++;
               if (two_hands_missing_count_ >= 20) {
                    two_hands_missing_count_ = 0;
                    next_state_ = BeforeBang_Entry;
               }
          } else {
               two_hands_missing_count_ = 0;
          }

          if (state_timer_.getMilliseconds() > 1000*10) {
               next_state_ = GameOfLife_Entry;
          }
          break;
     case GameOfLife_Entry:
          this->setup_GameOfLife();
          next_state_ = GameOfLife;
          break;
     case GameOfLife:                              
          this->game_of_life();
          if (state_timer_.getMilliseconds() > 1000*100) {
               next_state_ = BlackHole_Entry;
          }

          if(!hand_present && prev_hand_present_) {
               set_cam_move_to_goal(true);
          }

          if(hand_present && !prev_hand_present_) {
               set_cam_move_to_goal(false);
          }          

          break;
     case BlackHole_Entry:
          this->setup_BlackHole();
          next_state_ = BlackHole;
          break;

     case BlackHole:          
          this->animate();          
          
          if (blackhole_complete()) {
               next_state_ = Ball_Entry;
          }

          if(!hand_present && prev_hand_present_) {
               set_cam_move_to_goal(true);
          }

          if(hand_present && !prev_hand_present_) {
               set_cam_move_to_goal(false);
          }

          break;
     default:
          break;
     }    

     if (!cam_goal_reached(1, 10)) {
          cam_move_to_goal_animate(10,10);
     } else {
          allow_hand_look = true;
     }

     state_ = next_state_;
     prev_leap_packet_ = leap_packet_;     
     prev_hand_present_ = hand_present;     
     prev_two_hands_present_ = two_hands_present;

     if (allow_hand_look && hand_present) {
          mCamera->pitch(Ogre::Radian(pitch_diff*SYLLO_PI/180.0));
          mCamera->yaw(Ogre::Radian(yaw_diff*SYLLO_PI/180.0));
          mCamera->roll(Ogre::Radian(roll_diff*SYLLO_PI/180.0));
          mCamera->moveRelative(Ogre::Vector3(0,0, move_diff));
     }

     frame_++;              
}



double saturate(double input, const double &min, const double &max)
{
     if (min > max) {
          cout << "saturate(): Invalid Min / Max Combo" << endl;
          return 0;
     } else if (input < min) {
          input = min;
     } else if(input > max) {
          input = max;
     }
     return input;
}

double normalize(double input, const double &in_min, const double &in_max,
                 const double &out_min, const double &out_max)
{
     input = saturate(input, in_min, in_max);

     if (in_min >= in_max || out_min >= out_max) {
          cout << "normalize(): Invalid Min / Max Combo" << endl;
          return 0;
     }

     double ratio = input / (in_max - in_min);
     return ratio * (out_max - out_min);

     return input;
}

std::string color_number(double r, double g, double b)
{     
     std::stringstream ss_r, ss_g, ss_b;
     ss_r << std::setprecision(3) << saturate(r,0,1);
     ss_g << std::setprecision(3) << saturate(g,0,1);
     ss_b << std::setprecision(3) << saturate(b,0,1);
     std::string name = "RGB:" + ss_r.str() + "," + ss_g.str() + "," + ss_b.str();
                    
     return name;
}
