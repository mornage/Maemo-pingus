//  $Id: smashed.cpp 2986 2007-08-17 16:20:09Z grumbel $
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
#include "../math/vector3f.hpp"
#include "../display/scene_context.hpp"
#include "../pingu.hpp"
#include "smashed.hpp"

namespace Actions {

Smashed::Smashed (Pingu* p)
  : PinguAction(p),
    sound_played(false)
{
  sprite = Resource::load_sprite("pingus/player" + pingu->get_owner_str() + "/bomber");
}

void
Smashed::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pingu->get_pos ());
}

void
Smashed::update()
{
  sprite.update();
  //  pingu->particle->add_pingu_explo(pingu->x_pos, pingu->y_pos - 16);
  if (sprite.is_finished())
    pingu->set_status(PS_DEAD);
}

} // namespace Actions

/* EOF */
