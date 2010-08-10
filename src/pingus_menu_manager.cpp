//  $Id: pingus_menu_manager.cpp 3265 2007-09-30 16:07:08Z grumbel $
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

#include <iostream>
#include "screen/screen_manager.hpp"
#include "sound/sound.hpp"
#include "resource.hpp"
#include "blitter.hpp"
#include "pingus_menu_manager.hpp"


PingusMenuManager* PingusMenuManager::instance_ = 0;

PingusMenuManager::PingusMenuManager ()
  : mainmenu (this),
    exitmenu (this)
{
	int w = Display::get_width();
	int h = Display::get_height();
	// We only need to scale the background main menu images if the screen 
	// resolution is not default
	if (w != 800 && h != 600)
	{
		background.add_layer (Blitter::scale_surface_to_canvas(
			Resource::load_surface("core/menu/layer1"), w, 185 * h / 600), 0, 0, 12, 0);
		background.add_layer (Blitter::scale_surface_to_canvas(
			Resource::load_surface("core/menu/layer2"), w, 362 * h / 600), 0, 150 * (float)h / 600, 25, 0);
		background.add_layer (Blitter::scale_surface_to_canvas(
			Resource::load_surface("core/menu/layer3"), w, 306 * h / 600), 0, 200 * (float)h / 600, 50, 0);
		background.add_layer (Blitter::scale_surface_to_canvas(
			Resource::load_surface("core/menu/layer4"), w, 171 * h / 600), 0, 429 * (float)h / 600, 100, 0);
		background.add_layer (Blitter::scale_surface_to_canvas(
			Resource::load_surface("core/menu/layer5"), 302 * w / 800, 104 * h / 600), 0, 500 * (float)h / 600, 200, 0);
	}
	else
	{
		background.add_layer(Resource::load_sprite("core/menu/layer1"), 0, 0, 12, 0);
		background.add_layer(Resource::load_sprite("core/menu/layer2"), 0, 150, 25, 0);
		background.add_layer(Resource::load_sprite("core/menu/layer3"), 0, 200, 50, 0);
		background.add_layer(Resource::load_sprite("core/menu/layer4"), 0, 429, 100, 0);
		background.add_layer(Resource::load_sprite("core/menu/layer5"), 0, 500, 200, 0);
	}
	push_menu (&mainmenu);
}

PingusMenuManager::~PingusMenuManager ()
{
}

bool
PingusMenuManager::draw (DrawingContext& gc)
{
  background.draw(gc);

  gc.draw_fillrect(0,
                   Display::get_height () - 26,
                   Display::get_width (),
                   Display::get_height (),
                   Color(0, 0, 0, 255));

  for (MenuStackIter i = menu_stack.begin (); i != menu_stack.end (); ++i)
    (*i)->draw(gc);

  SDL_Delay(10);

  return true;
}

void
PingusMenuManager::update (const GameDelta& delta)
{
  background.update (delta.get_time ());
  menu_stack.back()->update (delta);
}

void
PingusMenuManager::set_menu (PingusSubMenu * menu)
{
  pop_menu ();
  push_menu (menu);
}

void
PingusMenuManager::push_menu (PingusSubMenu * menu)
{
  menu->preload ();
  menu_stack.push_back (menu);
}

void
PingusMenuManager::pop_menu ()
{
  if (!menu_stack.empty ())
    menu_stack.pop_back();
}

PingusSubMenu *
PingusMenuManager::current_menu ()
{
  if (!menu_stack.empty ())
    {
      MenuStackRIter i = menu_stack.rbegin ();
      if (! *i)
	std::cout << "PingusMenuManager: Error: current_menu is " << *i << std::endl;
      return *i;
    }
  else
    {
      std::cout << "PingusMenuManager: Error: MenuStack empty!" << std::endl;
      return 0;
    }
}

void
PingusMenuManager::show_exit_menu ()
{
  push_menu (&exitmenu);
}

void
PingusMenuManager::exit ()
{
  //std::cout << "poping PingusMenuManager" << std::endl;
  ScreenManager::instance ()->pop_screen ();
}

void
PingusMenuManager::on_startup()
{
  Sound::PingusSound::play_music("pingus-1.it");
}

PingusMenuManager*
PingusMenuManager::instance ()
{
  if (instance_)
    return instance_;
  else
    return instance_ = new PingusMenuManager ();
}

void
PingusMenuManager::init()
{
  instance_ = 0;
}

void
PingusMenuManager::deinit()
{
  delete instance_;
}


/* EOF */
