#ifndef THREE_EVENTS_EVENT_H
#define THREE_EVENTS_EVENT_H

#include <three/common.h>

namespace three {

class Event {
public:

  static const EventType UNKNOWN;

  virtual ~Event() {};

};

} // end namespace three

#endif // THREE_EVENTS_EVENT_H
