//  $Id: event.hpp 3120 2007-09-11 14:57:58Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_PINGUS_INPUT_EVENT_HXX
#define HEADER_PINGUS_INPUT_EVENT_HXX

#include <vector>
#include <string>
#include "../pingus.hpp"

namespace Input {

enum EventType { BUTTON_EVENT_TYPE, 
                 POINTER_EVENT_TYPE, 
                 AXIS_EVENT_TYPE, 
                 SCROLLER_EVENT_TYPE, 
                 KEYBOARD_EVENT_TYPE };

enum EventName { 
  // Buttons
  PRIMARY_BUTTON, 
  SECONDARY_BUTTON,
  PAUSE_BUTTON,
  FAST_FORWARD_BUTTON,
  ARMAGEDDON_BUTTON, 
  ESCAPE_BUTTON, 

  ACTION_1_BUTTON, 
  ACTION_2_BUTTON,
  ACTION_3_BUTTON,
  ACTION_4_BUTTON,
  ACTION_5_BUTTON,
  ACTION_6_BUTTON,
  ACTION_7_BUTTON,
  ACTION_8_BUTTON,
  ACTION_9_BUTTON, 
  ACTION_10_BUTTON,
                  
  ACTION_UP_BUTTON,
  ACTION_DOWN_BUTTON, 
                 
  // Pointer
  STANDARD_POINTER,
  
  // Scroller
  STANDARD_SCROLLER,

  STANDARD_KEYBOARD,

  // Axis
  ACTION_AXIS,
};


enum ButtonState { BUTTON_RELEASED, BUTTON_PRESSED };

struct ButtonEvent
{
  EventName   name;
  ButtonState state;
};


struct PointerEvent
{
  EventName name;
  float x;
  float y;
};

struct AxisEvent
{
  EventName name;
  float     dir;
};

struct ScrollEvent
{
  EventName name;
  float x_delta;
  float y_delta;
};

struct KeyboardEvent
{
  unsigned short key;
};

struct Event
{
  EventType type;

  union {
    ButtonEvent   button;
    PointerEvent  pointer;
    AxisEvent     axis;
    ScrollEvent   scroll;
    KeyboardEvent keyboard;
  };
};

typedef std::vector<Event> EventLst;

inline Event makeButtonEvent(EventName name, ButtonState state)
{
  Event event;

  event.type  = BUTTON_EVENT_TYPE;
  event.button.name  = name;
  event.button.state = state;

  return event;
}

inline Event makePointerEvent(EventName name, float x, float y)
{
  Event event;

  event.type = POINTER_EVENT_TYPE;
  event.pointer.name = name;
  event.pointer.x    = x;
  event.pointer.y    = y;

  return event;
}

inline Event makeAxisEvent(EventName name, float dir)
{
  Event event;

  event.type = AXIS_EVENT_TYPE;
  event.axis.dir  = dir;
  event.axis.name = name;

  return event;
}

inline Event makeScrollerEvent(EventName name, float x_delta, float y_delta)
{
  Event event;

  event.type    = SCROLLER_EVENT_TYPE;
  event.scroll.name    = name;
  event.scroll.x_delta = x_delta;
  event.scroll.y_delta = y_delta;

  return event;
}

inline Event makeKeyboardEvent(unsigned short c)
{
  Event event;
	
  event.type = KEYBOARD_EVENT_TYPE;
  event.keyboard.key = c;
	
  return event;
}

} // namespace Input

#endif

/* EOF */
