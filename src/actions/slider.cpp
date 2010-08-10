//  $Id: slider.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include "../resource.hpp"
#include "../col_map.hpp"
#include "../display/scene_context.hpp"
#include "../pingu.hpp"
#include "slider.hpp"

namespace Actions {

Slider::Slider (Pingu* p)
  : PinguAction(p),
    speed(10)
{
  sprite.load(Direction::LEFT,  "pingus/player" + pingu->get_owner_str() + 
    "/slider/left");
  sprite.load(Direction::RIGHT, "pingus/player" + pingu->get_owner_str() + 
    "/slider/right");
}

void
Slider::update ()
{
  sprite[pingu->direction].update();

  for (int i = 0; i < speed && rel_getpixel(1, 0) == Groundtype::GP_NOTHING; ++i)
    {
      pingu->set_x(pingu->get_x() + pingu->direction);

      if (rel_getpixel(0, -1) ==  Groundtype::GP_NOTHING)
        {
          speed = (speed > 5) ? 5 : speed;

          if (pingu->direction.is_right())
					  {
              pingu->set_velocity(pingu->get_velocity() + Vector3f(speed, 0.0));
            } 
          else
					  {
              pingu->set_velocity(pingu->get_velocity() + Vector3f(-speed, 0.0));
            }

          pingu->set_action(Actions::Walker);
          return;
        }
    }

  speed -= 7 * 0.025f;
  if (speed < 1)
    {
      pingu->set_action(Actions::Walker);
      return;
    }
}

void
Slider::draw (SceneContext& gc)
{
  gc.color().draw(sprite[pingu->direction], pingu->get_pos() + Vector3f(0, -2));
}

} // namespace Actions

/* EOF */
