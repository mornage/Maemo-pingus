//  $Id: liquid.cpp 2986 2007-08-17 16:20:09Z grumbel $
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
#include "../col_map.hpp"
#include "../display/scene_context.hpp"
#include "../resource.hpp"
#include "../world.hpp"
#include "liquid.hpp"

namespace WorldObjs {

Liquid::Liquid(const FileReader& reader)
  : old_width_handling(false),
    width(0)
{
  /*
    if (XMLhelper::get_prop(cur, "use-old-width-handling", old_width_handling))
    {
    if (old_width_handling)
    std::cout << "XMLPLF: Using Old Width Handling: " << std::endl;
    }
  */
  ResDescriptor desc;

  reader.read_vector("position", pos);
  reader.read_desc  ("surface",  desc);
  reader.read_int   ("repeat",   width);

  sur = Resource::load_sprite(desc);

  if (!old_width_handling)
    width = width * sur.get_width();
}

float
Liquid::get_z_pos () const
{
  return pos.z;
}

void
Liquid::on_startup ()
{
  CollisionMask mask = Resource::load_collision_mask("liquids/water_cmap");

  for(int i=0; i < width; ++i)
    world->get_colmap()->put(mask,
                             static_cast<int>(pos.x + i),
                             static_cast<int>(pos.y),
                             Groundtype::GP_WATER);
}

void
Liquid::draw (SceneContext& gc)
{
  for(int x = static_cast<int>(pos.x);
      x < pos.x + width;
      x += sur.get_width())
    {
      gc.color().draw(sur, Vector3f((float)x, pos.y));
    }
}

void
Liquid::update()
{
  sur.update(0.033f); 
}

} // namespace WorldObjs

/* EOF */
