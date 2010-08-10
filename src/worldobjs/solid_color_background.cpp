//  $Id: solid_color_background.cpp 3265 2007-09-30 16:07:08Z grumbel $
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

#include "../display/display.hpp"
#include "../display/scene_context.hpp"
#include "solid_color_background.hpp"

namespace WorldObjs {

SolidColorBackground::SolidColorBackground(const FileReader& reader)
{
  reader.read_color("color", color);
}

void
SolidColorBackground::draw (SceneContext& gc)
{
  // FIXME: should use SceneContext, not CL_Display
  gc.color().fill_screen(color);
}

} // namespace WorldObjs

/* EOF */
