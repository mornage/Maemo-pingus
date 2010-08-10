//  $Id: controller.hpp 3219 2007-09-22 02:03:10Z jsalmon3 $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_INPUT_CONTROLLER_HXX
#define HEADER_PINGUS_INPUT_CONTROLLER_HXX

#include <assert.h>
#include "event.hpp"

namespace Input {

class ControllerDescription;

class ControllerButton;
class ControllerAxis;
class ControllerPointer;
class ControllerScroller;
class ControllerKeyboard;

class Controller
{

private:
  static Controller* current_;
public:
  static Controller* current();

private:
  // State Stuff
  std::vector<ControllerButton*>   buttons;
  std::vector<ControllerAxis*>     axes;
  std::vector<ControllerPointer*>  pointers;
  std::vector<ControllerScroller*> scrollers;
  std::vector<ControllerKeyboard*> keyboards;
  
  std::vector<Event> events;
public:
  std::vector<Event> poll_events();

  Controller(const ControllerDescription& desc);
  ~Controller();
  
  ControllerAxis*     get_axis(int id);
  ControllerButton*   get_button(int id);
  ControllerPointer*  get_pointer(int id);
  ControllerScroller* get_scroller(int id);
  ControllerKeyboard* get_keyboard(int id);

  void add_axis_event(int id, float pos);
  void add_button_event(int id, ButtonState state);
  void add_pointer_event(int id, float x, float y);
  void add_scroller_event(int id, float xrel, float yrel);
  void add_keyboard_event(unsigned short key);

  void add_axis(int id, ControllerAxis* axis);
  void add_button(int id, ControllerButton* button); 
  void add_pointer(int id, ControllerPointer* pointer);
  void add_scroller(int id, ControllerScroller* scroller);
  void add_keyboard(int id, ControllerKeyboard* keyboard);
  
  void update(float delta);
private:
  Controller(const Controller&);
  Controller& operator= (const Controller&);
};

} // namespace Input

#endif 

/* EOF */
