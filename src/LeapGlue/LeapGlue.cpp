#include <iostream>

#include "LeapGlue.h"

using std::cout;
using std::endl;

//void SampleListener::onInit(const Controller& controller) {
//     std::cout << "Initialized" << std::endl;
//}
//
//void SampleListener::onConnect(const Controller& controller) {
//     std::cout << "Connected" << std::endl;
//     controller.enableGesture(Gesture::TYPE_CIRCLE);
//     controller.enableGesture(Gesture::TYPE_KEY_TAP);
//     controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
//     controller.enableGesture(Gesture::TYPE_SWIPE);
//
//}
//
//void SampleListener::onDisconnect(const Controller& controller) {
//     //Note: not dispatched when running in a debugger.
//     std::cout << "Disconnected" << std::endl;
//}
//
//void SampleListener::onExit(const Controller& controller) {
//     std::cout << "Exited" << std::endl;
//}
//
//void SampleListener::onFrame(const Controller& controller) {
//     // Get the most recent frame and report some basic information
//     const Frame frame = controller.frame();
//     std::cout << "Frame id: " << frame.id()
//               << ", timestamp: " << frame.timestamp()
//               << ", hands: " << frame.hands().count()
//               << ", fingers: " << frame.fingers().count()
//               << ", tools: " << frame.tools().count()
//               << ", gestures: " << frame.gestures().count() << std::endl;
//
//     if (!frame.hands().isEmpty()) {
//          // Get the first hand
//          const Hand hand = frame.hands()[0];
//
//          // Check if the hand has any fingers
//          const FingerList fingers = hand.fingers();
//          if (!fingers.isEmpty()) {
//               // Calculate the hand's average finger tip position
//               Vector avgPos;
//               for (int i = 0; i < fingers.count(); ++i) {
//                    avgPos += fingers[i].tipPosition();
//               }
//               avgPos /= (float)fingers.count();
//               std::cout << "Hand has " << fingers.count()
//                         << " fingers, average finger tip position" << avgPos << std::endl;
//          }
//
//          // Get the hand's sphere radius and palm position
//          std::cout << "Hand sphere radius: " << hand.sphereRadius()
//                    << " mm, palm position: " << hand.palmPosition() << std::endl;
//
//          // Get the hand's normal vector and direction
//          const Vector normal = hand.palmNormal();
//          const Vector direction = hand.direction();
//
//          // Calculate the hand's pitch, roll, and yaw angles
//          std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
//                    << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
//                    << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
//     }
//
//     // Get gestures
//     const GestureList gestures = frame.gestures();
//     for (int g = 0; g < gestures.count(); ++g) {
//          Gesture gesture = gestures[g];
//
//          switch (gesture.type()) {
//          case Gesture::TYPE_CIRCLE:
//          {
//               CircleGesture circle = gesture;
//               std::string clockwiseness;
//
//               if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
//                    clockwiseness = "clockwise";
//               } else {
//                    clockwiseness = "counterclockwise";
//               }
//
//               // Calculate angle swept since last frame
//               float sweptAngle = 0;
//               if (circle.state() != Gesture::STATE_START) {
//                    CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
//                    sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
//               }
//               std::cout << "Circle id: " << gesture.id()
//                         << ", state: " << gesture.state()
//                         << ", progress: " << circle.progress()
//                         << ", radius: " << circle.radius()
//                         << ", angle " << sweptAngle * RAD_TO_DEG
//                         <<  ", " << clockwiseness << std::endl;
//               break;
//          }
//          case Gesture::TYPE_SWIPE:
//          {
//               SwipeGesture swipe = gesture;
//               std::cout << "Swipe id: " << gesture.id()
//                         << ", state: " << gesture.state()
//                         << ", direction: " << swipe.direction()
//                         << ", speed: " << swipe.speed() << std::endl;
//               break;
//          }
//          case Gesture::TYPE_KEY_TAP:
//          {
//               KeyTapGesture tap = gesture;
//               std::cout << "Key Tap id: " << gesture.id()
//                         << ", state: " << gesture.state()
//                         << ", position: " << tap.position()
//                         << ", direction: " << tap.direction()<< std::endl;
//               break;
//          }
//          case Gesture::TYPE_SCREEN_TAP:
//          {
//               ScreenTapGesture screentap = gesture;
//               std::cout << "Screen Tap id: " << gesture.id()
//                         << ", state: " << gesture.state()
//                         << ", position: " << screentap.position()
//                         << ", direction: " << screentap.direction()<< std::endl;
//               break;
//          }
//          default:
//               std::cout << "Unknown gesture type." << std::endl;
//               break;
//          }
//     }
//
//     if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
//          std::cout << std::endl;
//     }
//}
//
//void SampleListener::onFocusGained(const Controller& controller) {
//     std::cout << "Focus Gained" << std::endl;
//}
//
//void SampleListener::onFocusLost(const Controller& controller) {
//     std::cout << "Focus Lost" << std::endl;
//}

Leap::Controller controller;

bool poll_frame(LeapPacket_t &packet) {          
     if (!controller.isConnected()) {
          packet.valid = false;
          return false;
     }
     
     // Get the most recent frame and report some basic information
     const Frame frame = controller.frame();
     //std::cout << "Frame id: " << frame.id()
     //          << ", timestamp: " << frame.timestamp()
     //          << ", hands: " << frame.hands().count()
     //          << ", fingers: " << frame.fingers().count()
     //          << ", tools: " << frame.tools().count()
     //          << ", gestures: " << frame.gestures().count() << std::endl;

     packet.frame_id = frame.id();
     packet.hands = frame.hands().count();
     packet.fingers = frame.fingers().count();
     packet.tools = frame.tools().count();
     packet.gestures = frame.gestures().count();
     
     packet.first.fingers = 0;
     packet.second.fingers = 0;

     if (!frame.hands().isEmpty()) {
          // Get the first hand
          const Hand hand = frame.hands()[0];

          // Check if the hand has any fingers
          const FingerList fingers = hand.fingers();
          if (!fingers.isEmpty()) {
               // Calculate the hand's average finger tip position
               Vector avgPos;
               for (int i = 0; i < fingers.count(); ++i) {
                    avgPos += fingers[i].tipPosition();
               }
               avgPos /= (float)fingers.count();
               //std::cout << "Hand has " << fingers.count()
               //          << " fingers, average finger tip position" << avgPos << std::endl;
               packet.first.fingers = fingers.count();
               packet.first.avg_pos.x = avgPos.x;
               packet.first.avg_pos.y = avgPos.y;
               packet.first.avg_pos.z = avgPos.z;

          }

          // Get the hand's sphere radius and palm position
          //std::cout << "Hand sphere radius: " << hand.sphereRadius()
          //          << " mm, palm position: " << hand.palmPosition() << std::endl;

          packet.first.sphere_radius = hand.sphereRadius();
          packet.first.palm_position.x = hand.palmPosition().x;
          packet.first.palm_position.y = hand.palmPosition().y;
          packet.first.palm_position.z = hand.palmPosition().z;
          
          // Get the hand's normal vector and direction
          const Vector normal = hand.palmNormal();
          const Vector direction = hand.direction();

          // Calculate the hand's pitch, roll, and yaw angles
          //std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
          //          << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
          //          << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
          packet.first.roll = normal.roll() * RAD_TO_DEG;
          packet.first.pitch = direction.pitch() * RAD_TO_DEG;
          packet.first.yaw = direction.yaw() * RAD_TO_DEG;

          if (packet.hands > 1) {
               const Hand second_hand = frame.hands()[1];

               // Check if the hand has any fingers
               const FingerList fingers = second_hand.fingers();
               if (!fingers.isEmpty()) {
                    // Calculate the hand's average finger tip position
                    Vector avgPos;
                    for (int i = 0; i < fingers.count(); ++i) {
                         avgPos += fingers[i].tipPosition();
                    }
                    avgPos /= (float)fingers.count();
                    //std::cout << "Hand has " << fingers.count()
                    //          << " fingers, average finger tip position" << avgPos << std::endl;
                    packet.second.fingers = fingers.count();
                    packet.second.avg_pos.x = avgPos.x;
                    packet.second.avg_pos.y = avgPos.y;
                    packet.second.avg_pos.z = avgPos.z;

               }

               // Get the hand's sphere radius and palm position
               //std::cout << "Hand sphere radius: " << hand.sphereRadius()
               //          << " mm, palm position: " << hand.palmPosition() << std::endl;

               packet.second.sphere_radius = second_hand.sphereRadius();
               packet.second.palm_position.x = second_hand.palmPosition().x;
               packet.second.palm_position.y = second_hand.palmPosition().y;
               packet.second.palm_position.z = second_hand.palmPosition().z;
          
               // Get the hand's normal vector and direction
               const Vector normal = second_hand.palmNormal();
               const Vector direction = second_hand.direction();

               // Calculate the hand's pitch, roll, and yaw angles
               //std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
               //          << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
               //          << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
               packet.second.roll = normal.roll() * RAD_TO_DEG;
               packet.second.pitch = direction.pitch() * RAD_TO_DEG;
               packet.second.yaw = direction.yaw() * RAD_TO_DEG;
          }
     }

     //// Get gestures
     //const GestureList gestures = frame.gestures();
     //for (int g = 0; g < gestures.count(); ++g) {
     //     Gesture gesture = gestures[g];
     //
     //     switch (gesture.type()) {
     //     case Gesture::TYPE_CIRCLE:
     //     {
     //          CircleGesture circle = gesture;
     //          std::string clockwiseness;
     //
     //          if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
     //               clockwiseness = "clockwise";
     //          } else {
     //               clockwiseness = "counterclockwise";
     //          }
     //
     //          // Calculate angle swept since last frame
     //          float sweptAngle = 0;
     //          if (circle.state() != Gesture::STATE_START) {
     //               CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
     //               sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
     //          }
     //          std::cout << "Circle id: " << gesture.id()
     //                    << ", state: " << gesture.state()
     //                    << ", progress: " << circle.progress()
     //                    << ", radius: " << circle.radius()
     //                    << ", angle " << sweptAngle * RAD_TO_DEG
     //                    <<  ", " << clockwiseness << std::endl;
     //          break;
     //     }
     //     case Gesture::TYPE_SWIPE:
     //     {
     //          SwipeGesture swipe = gesture;
     //          std::cout << "Swipe id: " << gesture.id()
     //                    << ", state: " << gesture.state()
     //                    << ", direction: " << swipe.direction()
     //                    << ", speed: " << swipe.speed() << std::endl;
     //          break;
     //     }
     //     case Gesture::TYPE_KEY_TAP:
     //     {
     //          KeyTapGesture tap = gesture;
     //          std::cout << "Key Tap id: " << gesture.id()
     //                    << ", state: " << gesture.state()
     //                    << ", position: " << tap.position()
     //                    << ", direction: " << tap.direction()<< std::endl;
     //          break;
     //     }
     //     case Gesture::TYPE_SCREEN_TAP:
     //     {
     //          ScreenTapGesture screentap = gesture;
     //          std::cout << "Screen Tap id: " << gesture.id()
     //                    << ", state: " << gesture.state()
     //                    << ", position: " << screentap.position()
     //                    << ", direction: " << screentap.direction()<< std::endl;
     //          break;
     //     }
     //     default:
     //          std::cout << "Unknown gesture type." << std::endl;
     //          break;
     //     }
     //}

     //if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
     //     std::cout << std::endl;
     //}
     
     packet.valid = true;
     return true;
}

//void SampleListener::onFocusGained(const Controller& controller) {
//     std::cout << "Focus Gained" << std::endl;
//}
//
//void SampleListener::onFocusLost(const Controller& controller) {
//     std::cout << "Focus Lost" << std::endl;
//}

void hello_leap()
{
     
     std::cout << "============================>" << endl;
     std::cout << "Hello Leap!" << endl;
     std::cout << "============================>" << endl;
}

//LeapGlue::LeapGlue()
//{     
//}

