//  $Id: gui_style.cpp 3166 2007-09-16 15:29:14Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#include "gui_style.hpp"

namespace Editor {

void
GUIStyle::draw_raised_box(DrawingContext& gc, const Rect& rect, const Color& color, int border)
{
  // FIXME: Should use draw_line
  gc.draw_fillrect(rect.left, rect.top, rect.right, rect.bottom,
                   Color(255, 255, 255));
  gc.draw_fillrect(rect.left+border, rect.top+border, rect.right, rect.bottom,
                          Color(169, 157, 140));
  gc.draw_fillrect(rect.left+border, rect.top+border, rect.right-border, rect.bottom-border,
                   color);
}

void
GUIStyle::draw_lowered_box(DrawingContext& gc, const Rect& rect, const Color& color, int border)
{
  // FIXME: Should use draw_line
  gc.draw_fillrect(rect.left, rect.top, rect.right, rect.bottom,
                   Color(169, 157, 140));
  gc.draw_fillrect(rect.left+border, rect.top+border, rect.right, rect.bottom,
                   Color(255, 255, 255));
  gc.draw_fillrect(rect.left+border, rect.top+border, rect.right-border, rect.bottom-border,
                   color);  
}

} // namespace Editor

/* EOF */
