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

using std::cout;
using std::endl;

MyNode::MyNode()
{
     max_size_ = 1;
     size_step_ = 0.01;         
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

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
     srand(time(0));

     rows_ = 50;
     cols_ = 50;

     //rows_ = 5;
     //cols_ = 5;

     frame_ = 0;

     state_ = GameOfLife_Entry;
     //state_ = Ball;
     next_state_ = state_;

     gol_timer_.reset();
     animate_timer_.reset();

     gol_ = new GOL(cols_, rows_);
     gol_->randomize();          

}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
     delete gol_;

     // close the library
     dlclose(leapglue_);     
}

void TutorialApplication::setup_Ball()
{
     mCamera->setPosition(Ogre::Vector3(0, 0 ,2000));
     
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               node = (MyNode*)(gol_->at(x,y).data());
               
               Ogre::SceneNode *scene_node;
               scene_node = node->scene_node();
               scene_node->setPosition(Ogre::Vector3(0,0,0));
               
               node->reset_ball_animate();               
          }
     }
}

void TutorialApplication::setup_GameOfLife()
{
     mCamera->setPosition(Ogre::Vector3(cols_/2*100, rows_/2*100 ,2000));
     
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;               
               node = (MyNode*)(gol_->at(x,y).data());               

               Ogre::SceneNode *scene_node;
               scene_node = node->scene_node();
               scene_node->setPosition(Ogre::Vector3(x*100,y*100,0));

               node->reset_game_of_life();
          }
     }
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
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
               ballNode->setPosition(Ogre::Vector3(c*100,r*100,0));
               //ballNode->setPosition(Ogre::Vector3(0,0,0));
               ballNode->setScale(Ogre::Vector3(1,1,1)); // Radius, in theory.
               
               MyNode *node = new MyNode();
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

void TutorialApplication::animate()
{
     for(int x = 0; x < gol_->x_width(); x++) {
          for(int y = 0; y < gol_->y_height(); y++) {
               MyNode *node;
               //Ogre::Entity * ent;
               node = (MyNode*)(gol_->at(x,y).data());
               //ent = node->entity();
               
               switch(state_) {
               case Ball:
                    node->ball_animate(animate_timer_.getMilliseconds());
                    break;
               case BeforeBang:
                    break;
               case GameOfLife:
                    cout << "Error: shouldn't happen" << endl;
                    break;
               default:
                    break;
               }
               
          }                         
     }
}
void TutorialApplication::game_of_life()
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

     if (update_gol) {
          gol_->step();
     }
}


void TutorialApplication::frame_loop()
{    
     bool hand_present = false;
     ////////////////////////////////////////////////////////////////////////
     // Handle Leap Motion Packet
     ////////////////////////////////////////////////////////////////////////
     if ((*poll_frame_)(leap_packet_)) {          
          if (leap_packet_.valid && prev_leap_packet_.valid) {               
               if (leap_packet_.hands > 0) {
                    hand_present = true;
                    
                    //double pitch_diff = leap_packet_.first.pitch;
                    //double yaw_diff = 0 - leap_packet_.first.yaw;
                    //double roll_diff = leap_packet_.first.roll;
                    //
                    //if (prev_leap_packet_.hands > 0) {
                    //     pitch_diff = leap_packet_.first.pitch - prev_leap_packet_.first.pitch;
                    //     yaw_diff = prev_leap_packet_.first.yaw - leap_packet_.first.yaw;
                    //     roll_diff = leap_packet_.first.roll - prev_leap_packet_.first.roll;                    
                    //     
                    //} 
                    //mCamera->pitch(Ogre::Radian(pitch_diff*SYLLO_PI/180.0));
                    //mCamera->yaw(Ogre::Radian(yaw_diff*SYLLO_PI/180.0));
                    //mCamera->roll(Ogre::Radian(roll_diff*SYLLO_PI/180.0));
               }
          }          

          if (leap_packet_.hands == 0 && prev_leap_packet_.hands > 0) {
               switch(state_) {
               case Ball:
                    mCamera->setPosition(Ogre::Vector3(0,0 ,2000));
                    mCamera->lookAt(Ogre::Vector3(0,0,0));
                    break;
               case BeforeBang:
                    break;
               case GameOfLife:
                    mCamera->setPosition(Ogre::Vector3(cols_/2*100, rows_/2*100 ,2000));
                    mCamera->lookAt(Ogre::Vector3(cols_/2*100, rows_/2*100,-300));
                    break;
               default:
                    break;
               }
          }

          prev_leap_packet_ = leap_packet_;
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

     if (state_ == GameOfLife) {          
          this->game_of_life();
     } else {          
          this->animate();
     }
     
     switch(state_) {
     case Ball_Entry:
          this->setup_Ball();
          next_state_ = Ball;          
          break;
     case Ball:
          this->animate();
          if (!hand_present) {
               next_state_ = GameOfLife_Entry;
          }
          break;
     case BeforeBang_Entry:
          next_state_ = BeforeBang;
          break;
     case BeforeBang:
          break;
     case BigBang_Entry:
          next_state_ = BigBang;
          break;
     case BigBang:
          break;
     case GameOfLife_Entry:
          this->setup_GameOfLife();
          next_state_ = GameOfLife;
          break;
     case GameOfLife:
          this->game_of_life();
          if (hand_present) {
               next_state_ = Ball_Entry;
          }
          break;
     default:
          break;
     }    
     state_ = next_state_;

     frame_++;              
}

double saturate(double in, double min, double max)
{
     if (in < min) {
          in = min;
          return in;
     }

     if (in > max) {
          in = max;
     }
     return in;
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
