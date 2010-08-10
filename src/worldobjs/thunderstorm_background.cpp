//  $Id: thunderstorm_background.cpp 3138 2007-09-13 05:27:19Z jsalmon3 $
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
#include "../display/scene_context.hpp"
#include "thunderstorm_background.hpp"

namespace WorldObjs {

ThunderstormBackground:: ThunderstormBackground(const FileReader& reader)
  : clouds_sur(Resource::load_sprite("textures/thunderstorm")),
    x_pos(0)
{
  reader.read_vector("position", pos);
}

float
ThunderstormBackground::get_z_pos () const
{
  return pos.z;
}

void
ThunderstormBackground::update ()
{
  ++x_pos;
  if (x_pos >= static_cast<int>(clouds_sur.get_width()))
    x_pos = 0;
}

void
ThunderstormBackground::draw (SceneContext& gc)
{
  gc.color().draw(clouds_sur, Vector2i(x_pos, 0));
}

} // namespace WorldObjs

/* EOF */
