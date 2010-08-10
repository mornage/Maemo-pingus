//  $Id: path_drawable.cpp 4107 2010-03-18 11:52:00Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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
#include "../math/color.hpp"
#include "../display/drawing_context.hpp"
#include "path_drawable.hpp"

namespace WorldMapNS {

PathDrawable::PathDrawable (const Path& arg_path)
  : path(arg_path)
{
}

void
PathDrawable::draw (DrawingContext& gc)
{
  Path::iterator prev = path.begin();

  for(Path::iterator next = prev + 1; next != path.end(); ++next)
    {
      gc.draw_line((int)prev->x, (int)prev->y,
                   (int)next->x, (int)next->y,
                   Color(255, 255, 255));
      prev = next;
    }
}

void
PathDrawable::update (float delta)
{
  }

} // namespace WorldMapNS

/* EOF */
