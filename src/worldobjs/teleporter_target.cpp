//  $Id: teleporter_target.cpp 2908 2007-08-14 17:46:58Z grumbel $
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
#include "../display/scene_context.hpp"
#include "../pingu.hpp"
#include "../pingu_holder.hpp"
#include "../world.hpp"
#include "../resource.hpp"
#include "teleporter_target.hpp"

namespace WorldObjs {

TeleporterTarget::TeleporterTarget(const FileReader& reader)
  : WorldObj(reader),
    sprite(Resource::load_sprite("worldobjs/teleportertarget"))
{
  reader.read_vector("position", pos);
}

float
TeleporterTarget::get_z_pos () const
{
  return pos.z;
}

void
TeleporterTarget::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pos);
}

void
TeleporterTarget::update ()
{
  sprite.update();
}

void
TeleporterTarget::teleporter_used()
{
  sprite.restart();
}

} // namespace WorldObjs

/* EOF */
