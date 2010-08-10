//  $Id: guillotine.cpp 2986 2007-08-17 16:20:09Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../display/scene_context.hpp"
#include "../pingu.hpp"
#include "../pingu_holder.hpp"
#include "../world.hpp"
#include "../resource.hpp"
#include "guillotine.hpp"

namespace WorldObjs {

Guillotine::Guillotine(const FileReader& reader)
  : sprite_kill_right (Resource::load_sprite("traps/guillotinekill/right")),
    sprite_kill_left (Resource::load_sprite("traps/guillotinekill/left")),
    sprite_idle (Resource::load_sprite("traps/guillotineidle")),
    killing(false)
{
  reader.read_vector("position", pos);
  
  sprite_kill_right.set_play_loop(false);
  sprite_kill_left.set_play_loop(false);
  sprite_idle.set_play_loop(true);
}

void
Guillotine::draw (SceneContext& gc)
{
  if (killing) {
    if (direction.is_left())
      gc.color().draw (sprite_kill_left, pos);
    else
      gc.color().draw (sprite_kill_right, pos);
  } else {
    gc.color().draw (sprite_idle, pos);
  }
}


float
Guillotine::get_z_pos () const
{
  return pos.z;
}

void
Guillotine::update ()
{
  // Only have to check one sprite because they update simultaneously
  if (sprite_kill_left.is_finished())
    killing = false;

  PinguHolder* holder = world->get_pingus();
  for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu)
    catch_pingu(*pingu);

  if (killing) {
    // Update both sprites so they finish at the same time.
    sprite_kill_left.update();
    sprite_kill_right.update();
    // FIXME: Should be a different sound
    if (sprite_kill_left.get_current_frame() == 7)
       WorldObj::get_world()->play_sound("splash", pos);
  } else {
    sprite_idle.update();
  }
}

void
Guillotine::catch_pingu (Pingu* pingu)
{
  if (!killing)
    {
      if (pingu->is_inside (static_cast<int>(pos.x + 38), static_cast<int>(pos.y + 90),
			    static_cast<int>(pos.x + 42), static_cast<int>(pos.y + 98)))
	{
	  killing = true;
	  pingu->set_status(PS_DEAD);
	  direction = pingu->direction;
    sprite_kill_left.restart();
    sprite_kill_right.restart();
	}
    }
}

} // namespace WorldObjs

/* EOF */
