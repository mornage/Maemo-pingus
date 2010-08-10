//  $Id: boarder.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include "../math/vector3f.hpp"
#include "../display/scene_context.hpp"
#include "../pingu.hpp"
#include "../resource.hpp"
#include "boarder.hpp"

namespace Actions {

Boarder::Boarder (Pingu* p)
  : PinguAction(p),
    x_pos(pingu->get_x()),
    speed(0.0)
{
  sprite.load(Direction::LEFT,  Resource::load_sprite("pingus/player" + 
    pingu->get_owner_str() + "/boarder/left"));
  sprite.load(Direction::RIGHT, Resource::load_sprite("pingus/player" + 
    pingu->get_owner_str() + "/boarder/right"));
}

void
Boarder::update ()
{
  sprite[pingu->direction].update();

  if (on_ground())
  {
    if (speed < 15.0)
      speed += 15.0 * 25.0f/1000.0f;
    else {
      speed = 15.0;
    }

    // Incremental update so that we don't skip pixels
    Vector3f new_pos = pingu->get_pos();
    new_pos.x = new_pos.x + pingu->direction * speed;
    while (new_pos.x != pingu->get_pos().x)
    {
      Vector3f old_pos = pingu->get_pos();
      pingu->set_pos(Vector3f(old_pos.x + (old_pos.x < new_pos.x) ? 1.0f : -1.0f, 
        old_pos.y, old_pos.z));

      if (pingu->rel_getpixel (1, 0))
      {
        // Hit a wall
        pingu->set_pos(old_pos); // + (pingu->direction * 10);
        ////pingu->pos.y = 10;

        pingu->apply_force (Vector3f(float(speed * pingu->direction * 0.5),
          -float(speed * abs(pingu->direction) * 0.5)));
        pingu->set_action(Actions::Walker);
        return;
      }
    }
  }
  else
  {
    pingu->apply_force (Vector3f((float)speed * pingu->direction, 0));
    pingu->set_action(Actions::Walker);
  }
}

void
Boarder::draw (SceneContext& gc)
{
  gc.color().draw(sprite[pingu->direction], pingu->get_pos ());
}

bool
Boarder::on_ground ()
{
  return pingu->rel_getpixel (0, -1) || pingu->rel_getpixel (0, -2);
}

} // namespace Actions

/* EOF */
