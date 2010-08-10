/*  $Id: sdl_driver.cpp 3265 2007-09-30 16:07:08Z grumbel $
**
**  Pingus - A free Lemmings clone
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include "global_event.hpp"
#include "screen/screen_manager.hpp"
#include "math/size.hpp"
#include "file_reader.hpp"
#include "sdl_driver.hpp"

namespace Input {

SDLDriver::SDLDriver()
  : keyboard_binding(0)
{
  for (int i = 0; i < SDLK_LAST; ++i) {
    char* key_name = SDL_GetKeyName(static_cast<SDLKey>(i));
    string2key[key_name] = static_cast<SDLKey>(i);
    
    // FIXME: Make the keynames somewhere user visible so that users can use them
    // std::cout << "Key: '" << key_name << "'" << std::endl;
  }
}

SDLDriver::~SDLDriver()
{
  
}

Keyboard*
SDLDriver::create_keyboard(const FileReader& reader, Control* parent)
{
  return (keyboard_binding = new Keyboard(parent));
}

Button*
SDLDriver::create_button(const FileReader& reader, Control* parent)
{
  //std::cout << "SDL: " << reader.get_name() << std::endl;
  if (reader.get_name() == "sdl:joystick-button")
    {
      JoystickButtonBinding binding;

      reader.read_int("device", binding.device);
      reader.read_int("button", binding.button);
      
      if (open_joystick(binding.device))
        {
          binding.binding = new Button(parent);
          joystick_button_bindings.push_back(binding);
      
          return binding.binding;
        }
      else
        {
          return 0;
        }
    }
  else if (reader.get_name() == "sdl:mouse-button")
    {
      MouseButtonBinding binding;

      reader.read_int("button", binding.button);
      binding.binding = new Button(parent);
      mouse_button_bindings.push_back(binding);

      return binding.binding;
    }
  else if (reader.get_name() == "sdl:keyboard-button")
    {
      std::string key;
      if (reader.read_string("key", key)) 
        {
          String2Key::iterator i = string2key.find(key);
          if (i != string2key.end()) 
            {
              KeyboardButtonBinding binding;
      
              binding.key = i->second;
              binding.binding = new Button(parent);
              keyboard_button_bindings.push_back(binding);

              return binding.binding;
            }
          else 
            {
              std::cout << "SDLDriver: Couldn't find keysym for key '" << key << "'" << std::endl;
              return 0;
            }
        }
      else
        {
          std::cout << "SDLDriver: 'key' missing" << std::endl;
          return 0;
        }
    }
  else
    {
      return 0;
    }
}

Axis*
SDLDriver::create_axis(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "sdl:joystick-axis")
    {
      JoystickAxisBinding binding;

      reader.read_int("device", binding.device);
      reader.read_int("axis",   binding.axis);
      
      if (open_joystick(binding.device))
        {
          binding.binding = new Axis(parent);
          joystick_axis_bindings.push_back(binding);
      
          return binding.binding;
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

Scroller*
SDLDriver::create_scroller(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "sdl:mouse-scroller")
    {
      ScrollerBinding binding;

      binding.binding = new Scroller(parent);
      scroller_bindings.push_back(binding);

      return binding.binding;
    }
  else
    {
      return 0;
    }
}

Pointer*
SDLDriver::create_pointer(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "sdl:mouse-pointer")
    {
      PointerBinding binding;

      binding.binding = new Pointer(parent);
      pointer_bindings.push_back(binding);

      return binding.binding;
    }
  else
    {
      return 0;
    }
}

bool 
SDLDriver::open_joystick(int device)
{
  JoystickHandles::iterator i = joystick_handles.find(device);
  if (i == joystick_handles.end())
    {
      SDL_Joystick* joy = SDL_JoystickOpen(device);
      if (joy)
        {
          joystick_handles[device] = joy;
          return true;
        }
      else
        {
          std::cout << "SDLDriver: Couldn't open joystick number " << device << std::endl;
          return false;
        }
    }
  else
    {
      return true;
    }
}

void
SDLDriver::update(float delta)
{
  // FIXME: Little hackywacky, better way would be to fetch event
  // loops somewhere else and only forward the relevant SDL_Events to
  // the SDLDriver
  SDL_Event event;
  while (SDL_PollEvent(&event))
    {
      switch(event.type)
        {
          case SDL_QUIT: // FIXME: make this into a GameEvent
            exit(1);
            break;

          case SDL_MOUSEMOTION:
            for(std::vector<PointerBinding>::iterator i = pointer_bindings.begin();
                i != pointer_bindings.end(); ++i)
              {
                i->binding->set_pos(Vector2f(event.motion.x, event.motion.y));
              }

            for(std::vector<ScrollerBinding>::iterator i = scroller_bindings.begin();
                i != scroller_bindings.end(); ++i)
              {
                i->binding->set_delta(Vector2f(event.motion.xrel, event.motion.yrel));
              }
            break;

          case SDL_MOUSEBUTTONDOWN:
          case SDL_MOUSEBUTTONUP:
            for(std::vector<MouseButtonBinding>::iterator i = mouse_button_bindings.begin();
                i != mouse_button_bindings.end(); ++i)
              {
                if (event.button.button == (*i).button)
                  {
                    if (event.button.state == SDL_PRESSED)
                      (*i).binding->set_state(BUTTON_PRESSED);
                    else
                      (*i).binding->set_state(BUTTON_RELEASED);
                  }
              }
            break;

          case SDL_VIDEORESIZE:
            ScreenManager::instance()->resize(Size(event.resize.w, event.resize.h));
            break;

          case SDL_KEYDOWN:
            if (keyboard_binding)
              keyboard_binding->send_char(event.key.keysym.unicode);
            
          case SDL_KEYUP:
            if (event.key.state == SDL_PRESSED)
              global_event.on_button_press(event.key);
            else
              global_event.on_button_release(event.key);            

            for(std::vector<KeyboardButtonBinding>::iterator i = keyboard_button_bindings.begin();
                i != keyboard_button_bindings.end(); ++i)
              {
                if (event.key.keysym.sym == i->key)
                  {
                    if (event.key.state == SDL_PRESSED)
                      i->binding->set_state(BUTTON_PRESSED);
                    else
                      i->binding->set_state(BUTTON_RELEASED);
                  }
              }
            break;

          case SDL_JOYAXISMOTION:
            for(std::vector<JoystickAxisBinding>::iterator i = joystick_axis_bindings.begin();
                i != joystick_axis_bindings.end(); ++i)            
              {
                if (event.jaxis.which == i->device &&
                    event.jaxis.axis  == i->axis)
                  i->binding->set_state(event.jaxis.value / 32767.0f);
              }
            break;
            
          case SDL_JOYBUTTONDOWN:
          case SDL_JOYBUTTONUP:
            for(std::vector<JoystickButtonBinding>::iterator i = joystick_button_bindings.begin();
                i != joystick_button_bindings.end(); ++i)
              {
                if (event.jbutton.which  == i->device &&
                    event.jbutton.button == i->button)
                  {
                    i->binding->set_state(event.jbutton.state == SDL_PRESSED ? BUTTON_PRESSED : BUTTON_RELEASED);
                  }
              }
            break;
            
          default:
            // FIXME: Do something with other events
            break;
        }
    }
}

} // namespace Input

/* EOF */
