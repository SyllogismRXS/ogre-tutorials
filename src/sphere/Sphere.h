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
#ifndef __SPHERE_h_
#define __SPHERE_h_

#include <BaseApplication/BaseApplication.h>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
 
class Sphere : public BaseApplication
{
public:
     Sphere(void);
	virtual ~Sphere(void);
 
protected:
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
};


#endif
