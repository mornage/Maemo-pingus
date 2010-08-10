//  $Id: floater.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include "../resource.hpp"
#include "../pingu.hpp"
#include "../display/scene_context.hpp"
#include "../groundtype.hpp"
#include "floater.hpp"

namespace Actions {

Floater::Floater(Pingu* p)
  : PinguAction(p),
    falling_depth(0),
    step(0)
{
  sprite = Resource::load_sprite("pingus/player" + pingu->get_owner_str() + "/floater/left");
}

void
Floater::update()
{
  sprite.update ();

  pingu->set_velocity(Vector3f(0.0f, 1.0f));

  if (rel_getpixel(0, -1) == Groundtype::GP_NOTHING)
    {
      ++step;
      if (step > 0)
	{
	  pingu->set_y(pingu->get_y() + 1);
	  step = 0;
	}
    }
  else
    {
      pingu->set_action (Actions::Walker);
    }
}

void
Floater::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pingu->get_pos());
}

bool
Floater::change_allowed (ActionName)
{
  return false;
}

} // namespace Actions

/* EOF */
