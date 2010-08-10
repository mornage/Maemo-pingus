//  $Id: digger.cpp 3216 2007-09-22 01:47:03Z grumbel $
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

#include <cstdio>
#include "../col_map.hpp"
#include "../display/scene_context.hpp"
#include "../ground_map.hpp"
#include "../world.hpp"
#include "../worldobj.hpp"
#include "../resource.hpp"
#include "../sound/sound.hpp"
#include "../pingu.hpp"
#include "digger.hpp"

namespace Actions {

Digger::Digger (Pingu* p)
  : PinguAction(p),
    digger_radius("other/digger_radius_gfx", "other/digger_radius"),
    digger_c(0)
{
  sprite = Resource::load_sprite("pingus/player" + pingu->get_owner_str() + "/digger/left");
}

void
Digger::update ()
{
  sprite.update ();

  if (rel_getpixel(0, -1) ==  Groundtype::GP_WATER
      || rel_getpixel(0, -1) ==  Groundtype::GP_LAVA)
    {
      pingu->set_action(Actions::Drown);
      return;
    }

  if (++digger_c >= 5)
    {
      digger_c = 0;
      dig();
    }

  if (!have_something_to_dig())
    {
      dig ();
      pingu->set_action(Actions::Walker);
    }
}

bool
Digger::have_something_to_dig ()
{
  if (rel_getpixel(0, -1) !=  Groundtype::GP_NOTHING)
    {
      if (rel_getpixel(0, -1) ==  Groundtype::GP_SOLID)
	{
	  Sound::PingusSound::play_sound("chink");
	  return false;
	}
      else
	return true;
    }
  else
    {
      return false;
    }
}

void
Digger::dig ()
{
  WorldObj::get_world()->remove(digger_radius,
                                static_cast<int>(pingu->get_pos().x - (digger_radius.get_width() / 2)),
                                static_cast<int>(pingu->get_pos().y - digger_radius.get_height() + 2));
  pingu->set_pos(pingu->get_pos().x, pingu->get_pos().y + 1.0f);
}

void
Digger::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pingu->get_pos ());
}

} // namespace Actions

/* EOF */
