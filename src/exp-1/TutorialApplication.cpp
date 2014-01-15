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
     
     //this->reset();
     //x_size_ = ((rand() % 9)+1) / 10.0;
     //y_size_ = x_size_;
     //z_size_ = x_size_;
     //cout << x_size_ << endl;
}

void MyNode::reset()
{    
     dying_ = false;

     x_size_ = 0;
     y_size_ = 0;
     z_size_ = 0;

     pos_ = scene_node_->getPosition();
     
     x_phase_ = (rand() % 314) / 100.0;
     y_phase_ = (rand() % 314) / 100.0;
     z_phase_ = (rand() % 314) / 100.0;
     
     
     //double color_r = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     //double color_g = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     //double color_b = (rand() % COLOR_RAND_MAX) * COLOR_STEP;
     ent_->setMaterialName(color_number(0,0,1.0));
}

void MyNode::step_animate(int time)
{
     //int t = (time % 1000);
     //x_size_ = sin(t);
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
     pos_.y += 0.6*sin(2*SYLLO_PI*t + y_phase_);
     pos_.x += 0.6*sin(2*SYLLO_PI*t + x_phase_);
     pos_.z += 0.4*sin(2*SYLLO_PI*t + z_phase_);
     scene_node_->setPosition(pos_.x, pos_.y, pos_.z);
}

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
     srand(time(0));

     rows_ = 50;
     cols_ = 50;

     frame_ = 0;

     gol_timer_.reset();
     animate_timer_.reset();

     gol_ = new GOL(cols_, rows_);
     gol_->randomize();          

     mTimer = OGRE_NEW Ogre::Timer();
     mTimer->reset();     
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
     delete gol_;

     // close the library
     dlclose(leapglue_);     
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{    
     mCamera->setPosition(Ogre::Vector3(cols_/2*100, rows_/2*100 ,2000));
     //Ogre::ColourValue fadeColour(0.05, 0.05, 0.05);
     //Ogre::ColourValue fadeColour2(0.9, 0.9, 0.9);
     //mWindow->getViewport(0)->setBackgroundColour(fadeColour);
     //mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour2, 0, 1000, 2000);

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
     //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
     //mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
     
     Ogre::Light* light = mSceneMgr->createLight( "MainLight" );
     light->setPosition(20, 80, 50);
     
     Ogre::Light* light_second = mSceneMgr->createLight( "SecondLight" );
     light_second->setPosition(cols_/2*100, rows_/2*100,1000);     
     //std::map<std::string,Ogre::MaterialPtr>::iterator it;
     //it = colors_.begin();
     
     for (int r = 0; r < rows_; r++) {
          for (int c = 0 ; c < cols_; c++) {
               std::stringstream ss_r, ss_c;
               ss_r << r;
               ss_c << c;
               
               std::string name = "mySphere" + ss_r.str() + "_" + ss_c.str();
               Ogre::Entity * mBall = mSceneMgr->createEntity(name, Ogre::SceneManager::PT_SPHERE);
               Ogre::SceneNode *ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                              
               mBall->setMaterialName(color_number(0,0,1.0));
               //mBall->setMaterialName("RGB:0.95,0,0");
               //mBall->setMaterialName("Examples/Ice");
               //mBall->setMaterialName((*it).first);               

               ballNode->attachObject(mBall);
               ballNode->setPosition(Ogre::Vector3(c*100,r*100,0));
               ballNode->setScale(Ogre::Vector3(1,1,1)); // Radius, in theory.
               
               MyNode *node = new MyNode();
               node->set_entity(mBall);
               node->set_scene_node(ballNode);
               gol_->at(c,r).set_data((void*)node);
               node->reset();

               //if (it != colors_.end()) {
               //     it++;
               //} else {
               //     it = colors_.begin();
               //}
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

void TutorialApplication::frame_loop()
{      
     if ((*poll_frame_)(leap_packet_)) {          
          if (leap_packet_.valid && prev_leap_packet_.valid) {               
               if (leap_packet_.hands > 0) {
                    double pitch_diff = leap_packet_.first.pitch;
                    double yaw_diff = 0 - leap_packet_.first.yaw;
                    double roll_diff = leap_packet_.first.roll;
                    
                    if (prev_leap_packet_.hands > 0) {
                         pitch_diff = leap_packet_.first.pitch - prev_leap_packet_.first.pitch;
                         yaw_diff = prev_leap_packet_.first.yaw - leap_packet_.first.yaw;
                         roll_diff = leap_packet_.first.roll - prev_leap_packet_.first.roll;                    
                         
                    } 
                    mCamera->pitch(Ogre::Radian(pitch_diff*SYLLO_PI/180.0));
                    mCamera->yaw(Ogre::Radian(yaw_diff*SYLLO_PI/180.0));
                    mCamera->roll(Ogre::Radian(roll_diff*SYLLO_PI/180.0));
               }
          }          

          if (leap_packet_.hands == 0 && prev_leap_packet_.hands > 0) {
               mCamera->setPosition(Ogre::Vector3(cols_/2*100, rows_/2*100 ,2000));
               mCamera->lookAt(Ogre::Vector3(cols_/2*100, rows_/2*100,-300));
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

               node->step_animate(animate_timer_.getMilliseconds());

               if (update_gol) {                    
                    if (gol_->at(x,y).grid_type() == 1) {
                         ent->setVisible(true);
                         if (gol_->at(x,y).is_new()) {
                              node->reset();
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
     frame_++;
     
     /// ////Ogre::SceneNode::ObjectIterator object_it = ((Ogre::SceneNode *)mSceneMgr->getRootSceneNode())->getAttachedObjectIterator();
     /// //Ogre::Node::ChildNodeIterator node_it = mSceneMgr->getRootSceneNode()->getChildIterator();
     /// //
     /// //while (node_it.hasMoreElements()) {
     /// //     //DumpNodes(ss, node_it.getNext(), level + 2);               
     /// //     node_it.getNext();
     /// //}
     /// 
     /// 
     /// for(int x = 0; x < gol_->x_width(); x++) {
     ///      for(int y = 0; y < gol_->y_height(); y++) {
     ///           std::stringstream ss_x, ss_y;
     ///           ss_x << x;
     ///           ss_y << y;
     ///      
     ///           std::string name = "mySphere" + ss_y.str() + "_" + ss_x.str();
     ///           //Ogre::Entity * ent = mSceneMgr->getEntity("mySphere5_5");
     ///           Ogre::Entity * ent = mSceneMgr->getEntity(name);
     ///      
     ///           if (gol_->at(x,y).grid_type() == 1) {
     ///                ent->setVisible(true);
     ///           } else {
     ///                ent->setVisible(false);
     ///           }
     /// 
     ///           //Ogre::Node * node = ent->getParentNode();
     ///           //Ogre::Vector3 pos = node->getPosition();
     ///           //node->setPosition(pos.x, pos.y, pos.z+1);
     ///           //cout << gol_->at(x,y).grid_type();
     ///      }
     ///      //cout << endl;
     /// }     
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
