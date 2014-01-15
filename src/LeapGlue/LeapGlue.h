#ifndef LEAPGLUE_H_
#define LEAPGLUE_H_
/// ---------------------------------------------------------------------------
/// @file LeapGlue.h
/// @author Kevin DeMarco <kevin.demarco@gmail.com>
///
/// Time-stamp: <2014-01-15 02:11:54 syllogismrxs>
///
/// @version 1.0
/// Created: 14 Jan 2014
///
/// ---------------------------------------------------------------------------
/// @section LICENSE
/// 
/// The MIT License (MIT)  
/// Copyright (c) 2012 Kevin DeMarco
///
/// Permission is hereby granted, free of charge, to any person obtaining a 
/// copy of this software and associated documentation files (the "Software"), 
/// to deal in the Software without restriction, including without limitation 
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
/// and/or sell copies of the Software, and to permit persons to whom the 
/// Software is furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in 
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
/// DEALINGS IN THE SOFTWARE.
/// ---------------------------------------------------------------------------
/// @section DESCRIPTION
/// 
/// The LeapGlue class ...
/// 
/// ---------------------------------------------------------------------------
#include <iostream>
#include <Leap.h>

using namespace Leap;

//class SampleListener : public Listener {
//  public:
//    virtual void onInit(const Controller&);
//    virtual void onConnect(const Controller&);
//    virtual void onDisconnect(const Controller&);
//    virtual void onExit(const Controller&);
//    virtual void onFrame(const Controller&);
//    virtual void onFocusGained(const Controller&);
//    virtual void onFocusLost(const Controller&);
//};

typedef struct Vector3D
{
     double x;
     double y;
     double z;
}Vector3D_t;

typedef struct HandPacket
{
     int fingers;
     Vector3D_t avg_pos;
     double sphere_radius;
     Vector3D_t palm_position;
     double roll;
     double pitch;
     double yaw;
}HandPacket_t;

typedef struct LeapPacket
{
     bool valid;
     int frame_id;
     int hands;
     int fingers;
     int tools;
     int gestures;     
     HandPacket_t first;
     HandPacket_t second;
} LeapPacket_t;

extern "C" {
     void hello_leap();
     bool poll_frame(LeapPacket_t &packet);
}

#endif
