//  $Id: screen_manager.cpp 3269 2007-10-01 04:24:14Z grumbel $
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

#include "SDL.h"
#include <iostream>
#include "../globals.hpp"
#include "math/size.hpp"
#include "pathname.hpp"
#include "display/cursor.hpp"
#include "display/display.hpp"
#include "screen_manager.hpp"
#include "../path_manager.hpp"
#include "screenshot.hpp"
#include "../display/drawing_context.hpp"
#include "../input/controller.hpp"
#include "../input/manager.hpp"

ScreenManager* ScreenManager::instance_ = 0;

ScreenManager::ScreenManager()
{
  display_gc = new DrawingContext();

  cached_action = CA_NONE;
}

ScreenManager::~ScreenManager ()
{
  delete display_gc;
}

void
ScreenManager::display()
{
  Input::Manager input_manager;

  Input::Controller* input_controller = 0;

  if (controller_file.empty())
    input_controller = input_manager.create_controller(Pathname("controller/default.scm", 
                                                                Pathname::DATA_PATH));
  else
    input_controller = input_manager.create_controller(Pathname(controller_file,
                                                                Pathname::SYSTEM_PATH));

  Cursor* cursor = 0;
  if (swcursor_enabled)
    {
      cursor = new Cursor("core/cursors/animcross");
      Display::add_flip_screen_hook(cursor);
      SDL_ShowCursor(SDL_DISABLE);
    }

  DeltaManager delta_manager;

  // Main loop for the menu
  while (!screens.empty())
    {
      float time_delta = delta_manager.getset();

      if (time_delta > 1.0)
	{
          if (maintainer_mode)
            std::cout << "ScreenManager: detected large delta (" << time_delta
                      << "), ignoring and doing frameskip" << std::endl;
	  continue;
	}

      input_manager.update(time_delta);

      // Fill the delta with values
      GameDelta delta(time_delta, delta_manager.get_absolute(),  
                      input_controller->poll_events());

      last_screen = get_current_screen();

      // Most likly the screen will get changed in this update call
      get_current_screen()->update (delta);

      if (cursor)
        cursor->update(time_delta);

      // Last screen has poped, so we are going to end here
      if (screens.empty())
	continue;

      while (cached_action != CA_NONE)
        {
          switch (cached_action)
            {
            case CA_POP:
              real_pop_screen();
              break;
            case CA_POP_ALL:
              real_pop_all_screens();
              break;
            case CA_REPLACE:
              real_replace_screen(replace_screen_arg);
              break;
            case CA_CLEAR:
              real_clear();
              break;
            default:
              break;
            }
        }

      // FIXME: is there a more gentel way to do that instead of spreading the checks all around here?
      // Last screen has poped, so we are going to end here
      if (screens.empty())
	continue;

      // skip draw if the screen changed to avoid glitches
      if (last_screen == get_current_screen() || fast_mode)
      	{
	  if (get_current_screen()->draw(*display_gc))
            {
              display_gc->render(Display::get_screen(), Rect(Vector2i(0,0), Size(Display::get_width(),
                                                                                     Display::get_height())));
              Display::flip_display ();
              display_gc->clear();
            }
        }
      else
	{
	  //std::cout << "ScreenManager: fading screens" << std::endl;
	  fade_over(last_screen, get_current_screen());
	}

      // Stupid hack to make this thing take less CPU
      SDL_Delay(1);
    }

  Display::remove_flip_screen_hook(cursor);
  delete cursor;
  delete input_controller;
}

ScreenPtr&
ScreenManager::get_current_screen()
{
  assert(!screens.empty());
  return screens.back ();
}

ScreenManager*
ScreenManager::instance ()
{
  if (instance_)
    return instance_;
  else
    return instance_ = new ScreenManager ();
}

void
ScreenManager::push_screen (Screen* screen, bool delete_screen)
{
  if (!screens.empty())
    {
      screens.back ()->on_shutdown ();
    }

  screens.push_back (ScreenPtr(screen, delete_screen));
  screen->on_startup ();
}

void
ScreenManager::pop_screen ()
{
  assert (cached_action == CA_NONE || cached_action == CA_POP);
  cached_action = CA_POP;
}

void
ScreenManager::pop_all_screens()
{
  assert(cached_action == CA_NONE);
  cached_action = CA_POP_ALL;
}

void
ScreenManager::replace_screen (Screen* screen, bool delete_screen)
{
  assert (cached_action == CA_NONE);
  cached_action = CA_REPLACE;
  replace_screen_arg = ScreenPtr(screen, delete_screen);
}

void
ScreenManager::real_replace_screen (const ScreenPtr& ptr)
{
  cached_action = CA_NONE;
  screens.back ()->on_shutdown ();
  screens.back () = ptr;
  screens.back ()->on_startup ();
}

void
ScreenManager::real_pop_screen ()
{
  cached_action = CA_NONE;
  ScreenPtr back = screens.back ();
  screens.pop_back();
  back->on_shutdown();

  if (!screens.empty ())
    {
      screens.back()->on_startup ();
    }
}

void
ScreenManager::real_pop_all_screens()
{
  cached_action = CA_NONE;
  ScreenPtr back = screens.back();
  screens.pop_back();
  back->on_shutdown();

  screens.clear();
}

void
ScreenManager::clear()
{
  cached_action = CA_CLEAR;
}

void
ScreenManager::real_clear()
{
  cached_action = CA_NONE;
  screens.clear();
}

void
ScreenManager::fade_over (ScreenPtr& old_screen, ScreenPtr& new_screen)
{
  DeltaManager delta_manager;
  float passed_time = 0;

  float progress = 0.0f;
  while (progress <= 1.0f)
    {
      float time_delta = delta_manager.getset ();
      passed_time += time_delta;

      int border_x = int((Display::get_width()/2)  * (1.0f - progress));
      int border_y = int((Display::get_height()/2) * (1.0f - progress));

      old_screen->draw(*display_gc);
      display_gc->render(Display::get_screen(), Rect(Vector2i(0,0), Size(Display::get_width(),
                                                                         Display::get_height())));
      display_gc->clear();
      
      Display::push_cliprect(Rect(Vector2i(0 + border_x, 0 + border_y),
                                  Size(screen_width  - 2*border_x, screen_height - 2*border_y)));

      new_screen->draw(*display_gc);
      display_gc->render(Display::get_screen(), Rect(Vector2i(0,0), Size(Display::get_width(),
                                                                         Display::get_height())));
      display_gc->clear();

      //GameDelta delta (time_delta, CL_System::get_time(), events);
      // FIXME: Animation looks nifty but doesn't work all that good
      //new_screen->update (delta);
      //old_screen->update (delta);
      
      Display::pop_cliprect();
      Display::flip_display ();
      display_gc->clear();
      
      progress = passed_time/1.0f;
    }
}

void
ScreenManager::resize(const Size& size)
{
  display_gc->set_rect(Rect(Vector2i(0, 0), size));

  // FIXME: Calling this causes horrible flicker, any better way to resize the screen?
  Display::set_video_mode(size.width, size.height);

  get_current_screen()->resize(size);
}

Screen*
ScreenManager::get_screen()
{
  return get_current_screen().get();
}

void
ScreenManager::init()
{
  instance_ = 0;
}

void
ScreenManager::deinit()
{
  delete instance_;
  instance_ = 0;
}

/* EOF */
