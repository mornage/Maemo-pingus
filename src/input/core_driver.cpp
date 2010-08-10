//  $Id: core_driver.cpp 3223 2007-09-22 02:34:08Z jsalmon3 $
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

#include "math.hpp"
#include "manager.hpp"
#include "core_driver.hpp"

namespace Input {

class AxisPointer : public Pointer
{
private:
  Axis* x_axis;
  Axis* y_axis;
  Button* speed_button;
  float speed;

public:
  AxisPointer(Control* parent) 
    : Pointer(parent),
      x_axis(0), y_axis(0), speed_button(0),
      speed(400.0f)
  {
  }

  ~AxisPointer()
  {
  }

  void setup(Axis* x, Axis* y, Button* s = 0)
  {
    x_axis = x;
    y_axis = y;
    speed_button = s;
  }

  void update(Control* ) 
  {
    //std::cout << "event" << std::endl;
  }

  void update(float delta)
  {
    x_axis->update(delta);
    y_axis->update(delta);
    if (speed_button) speed_button->update(delta);

    Vector2f new_pos = pos;
    float c_speed = speed;
    
    if (speed_button && speed_button->get_state() == BUTTON_PRESSED)
      {
        c_speed *= 5.0f;
      }

    new_pos.x += x_axis->get_pos() * c_speed * delta;
    new_pos.y += y_axis->get_pos() * c_speed * delta;

    // FIXME: Shouldn't be hardcored, but shouldn't depend on Display
    // either
    new_pos.x = Math::clamp(0.0f, new_pos.x, 800.0f);
    new_pos.y = Math::clamp(0.0f, new_pos.y, 600.0f);

    if (new_pos != pos)
      {
        pos = new_pos;
        notify_parent();
      }
  }
};

class AxisScroller : public Scroller
{
private:
  Axis* x_axis;
  Axis* y_axis;
  Button* speed_button;
  float speed;

public:
  AxisScroller(Control* parent) 
    : Scroller(parent),
      x_axis(0), y_axis(0), speed_button(0),
      speed(800.0f)
  {
  }

  ~AxisScroller()
  {
  }

  void setup(Axis* x, Axis* y, Button* s = 0)
  {
    x_axis = x;
    y_axis = y;
    speed_button = s;
  }

  void update(Control* ) 
  {
    //std::cout << "event" << std::endl;
  }

  void update(float delta)
  {
    x_axis->update(delta);
    y_axis->update(delta);

    if (speed_button) speed_button->update(delta);

    float    c_speed = speed;
    
    if (speed_button && speed_button->get_state() == BUTTON_PRESSED)
      {
        c_speed *= 5.0f;
      }

    this->delta.x = -x_axis->get_pos() * c_speed * delta;
    this->delta.y = y_axis->get_pos() * c_speed * delta;

    notify_parent();
  }
};

class ButtonScroller : public Scroller
{
private:
  Button* up;
  Button* down;
  Button* left;
  Button* right;
  float speed; 

public:
  ButtonScroller(Control* parent)
    : Scroller(parent),
      up(0), down(0), left(0), right(0),
      speed(800.0f)
  {
  }

  ~ButtonScroller()
  {
    delete up;
    delete down;
    delete left;
    delete right;
  }

  void setup(Button* up_, Button* down_, Button* left_, Button* right_)
  {
    up    = up_;
    down  = down_;
    left  = left_;
    right = right_;
  }

  void update(Control* ) 
  {
  }

  void update(float delta_t)
  {
    up->update(delta_t);
    down->update(delta_t);
    left->update(delta_t);
    right->update(delta_t);

    delta.x = delta.y = 0.0f;
    
    if (left->get_state() == BUTTON_PRESSED)
      delta.x += speed * delta_t;

    if (right->get_state() == BUTTON_PRESSED)
      delta.x += -speed * delta_t;

    if (up->get_state() == BUTTON_PRESSED)
      delta.y += speed * delta_t;

    if (down->get_state() == BUTTON_PRESSED)
      delta.y += -speed * delta_t;       

    notify_parent();
  }
};

Button*
CoreDriver::create_button(const FileReader& reader, Control* parent)
{
  return 0;
}

Axis*
CoreDriver::create_axis(const FileReader& reader, Control* parent)
{
  return 0;
}

Scroller*
CoreDriver::create_scroller(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "core:axis-scroller") 
    {
      AxisScroller* axis = new AxisScroller(parent);

      FileReader x_reader;
      if (!reader.read_section("x-axis", x_reader))
        {
          std::cout << "CoreDriver: Couldn't find x-axis" << std::endl;
          delete axis;
          return 0;
        }
    
      FileReader y_reader;
      if (!reader.read_section("y-axis", y_reader))
        {
          std::cout << "CoreDriver: Couldn't find y-axis" << std::endl;
          delete axis;
          return 0;       
        }

      Axis* x_axis = manager->create_axis(x_reader.get_sections().front(), axis);
      Axis* y_axis = manager->create_axis(y_reader.get_sections().front(), axis);

      Button* button = 0;
      FileReader button_reader;
      if (reader.read_section("button", button_reader))
        {
          button = manager->create_button(button_reader.get_sections().front(), axis);
        }

      if (x_axis && y_axis)
        {
          axis->setup(x_axis, y_axis, button);
          return axis;
        }
      else
        {
          return 0;
        }
    }
  else if (reader.get_name() == "core:button-scroller")
    {
      ButtonScroller* scroller = new ButtonScroller(parent);

      FileReader left_reader;
      if (!reader.read_section("left", left_reader))
        {
          std::cout << "CoreDriver: core:button-scroller: Couldn't find 'left'" << std::endl;
          delete scroller;
          return 0;
        }

      FileReader right_reader;
      if (!reader.read_section("right", right_reader))
        {
          std::cout << "CoreDriver: core:button-scroller: Couldn't find 'right'" << std::endl;
          delete scroller;
          return 0;
        }

      FileReader up_reader;
      if (!reader.read_section("up", up_reader))
        {
          std::cout << "CoreDriver: core:button-scroller: Couldn't find 'up'" << std::endl;
          delete scroller;
          return 0;
        }

      FileReader down_reader;
      if (!reader.read_section("down", down_reader))
        {
          std::cout << "CoreDriver: core:button-scroller: Couldn't find 'down'" << std::endl;
          delete scroller;
          return 0;
        }
      
      // FIXME: Add more error checking
      Button* up_button    = manager->create_button(up_reader.get_sections().front(),    scroller);
      Button* down_button  = manager->create_button(down_reader.get_sections().front(),  scroller);
      Button* left_button  = manager->create_button(left_reader.get_sections().front(),  scroller);
      Button* right_button = manager->create_button(right_reader.get_sections().front(), scroller);

      scroller->setup(up_button,
                      down_button,
                      left_button,
                      right_button);
      return scroller;
    }
  else 
    {
      return 0;
    }
}

Pointer*
CoreDriver::create_pointer(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "core:axis-pointer") 
    {
      AxisPointer* axis = new AxisPointer(parent);

      FileReader x_reader;
      if (!reader.read_section("x-axis", x_reader))
        {
          std::cout << "CoreDriver: Couldn't find x-axis" << std::endl;
          delete axis;
          return 0;
        }
    
      FileReader y_reader;
      if (!reader.read_section("y-axis", y_reader))
        {
          std::cout << "CoreDriver: Couldn't find y-axis" << std::endl;
          delete axis;
          return 0;       
        }

      Axis* x_axis = manager->create_axis(x_reader.get_sections().front(), axis);
      Axis* y_axis = manager->create_axis(y_reader.get_sections().front(), axis);

      Button* button = 0;
      FileReader button_reader;
      if (reader.read_section("button", button_reader))
        {
          button = manager->create_button(button_reader.get_sections().front(), axis);
        }

      if (x_axis && y_axis)
        {
          axis->setup(x_axis, y_axis, button);
          return axis;
        }
      else
        {
          return 0;
        }
    } 
  else 
    {
      return 0;
    }
}

Keyboard*
CoreDriver::create_keyboard(const FileReader& reader, Control* parent)
{
  return 0;
}

} // namespace Input

/* EOF */
