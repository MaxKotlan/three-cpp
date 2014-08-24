#ifndef THREE_EVENTS_MOUSE_EVENT_H
#define THREE_EVENTS_MOUSE_EVENT_H

#include <three/common.h>
#include <three/events/input_event.h>

namespace three {

enum MouseButton {
  NONE = 0,
  LEFT,
  MIDDLE,
  RIGHT,
  X1,
  X2
};

class MouseEvent : public InputEvent {
public:

  static const EventType MOUSE_MOVE;
  static const EventType MOUSE_DOWN;
  static const EventType MOUSE_UP;
  static const EventType MOUSE_WHEEL;

  MouseEvent( const EventType type, unsigned int timestamp, MouseButton button, unsigned char buttons,
              float screenX, float screenY, float movementX = 0.f, float movementY = 0.f )
    : InputEvent( type, timestamp ),
      button( button ),
      buttons( buttons ),
      screenX( screenX ),
      screenY( screenY ),
      movementX( movementX ),
      movementY( movementY ) {}

  MouseButton button;

  unsigned char buttons;

  float screenX;
  float screenY;

  float movementX;
  float movementY;

};

} // end namespace three

#endif // THREE_EVENTS_MOUSE_EVENT_H
