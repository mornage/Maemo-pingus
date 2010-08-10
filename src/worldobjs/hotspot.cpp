//  $Id: hotspot.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include <iostream>
#include "../globals.hpp"
#include "../display/scene_context.hpp"
#include "../resource.hpp"
#include "hotspot.hpp"

namespace WorldObjs {

Hotspot::Hotspot(const FileReader& reader)
{
  ResDescriptor desc;

  reader.read_vector("position", pos);
  reader.read_desc  ("surface",  desc);
  reader.read_float ("parallax", para);

  sprite = Resource::load_sprite(desc);
}

Hotspot::~Hotspot ()
{
}

void
Hotspot::update()
{
  sprite.update();
}

void
Hotspot::draw (SceneContext& gc)
{
  // FIXME: para support doesnn't work correctly
  gc.color().draw (sprite, pos);
}

float
Hotspot::get_z_pos () const
{
  return pos.z;
}

} // namespace WorldObjs

/* EOF */
