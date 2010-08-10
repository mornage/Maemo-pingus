//  $Id: inputbox.cpp 3180 2007-09-18 16:52:31Z grumbel $
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

#include <iostream>
#include "fonts.hpp"
#include "display/drawing_context.hpp"
#include "inputbox.hpp"

namespace Editor {

Inputbox::Inputbox(const Rect& rect)
  : RectComponent(rect)
{
}

void
Inputbox::draw(DrawingContext& gc)
{
  gc.draw_fillrect(rect, Color(255,255,255));
  gc.draw_rect(rect, has_focus() ? Color(255,128,0) : Color(0,0,0));
  
  gc.print_left(Fonts::verdana11, rect.left + 5, 
                rect.top + rect.get_height()/2 - Fonts::verdana11.get_height()/2,
                text);
}

void
Inputbox::set_text(const std::string& text_)
{
  text = text_;
}

void
Inputbox::on_key_pressed(const unsigned short c)
{
  if (c == 0)
    {
      // ignore
    }
  else if (c == 8) // backspace
    {
      if (!text.empty())
        {
          text = text.substr(0, text.size()-1);
          on_change(text);
        }      
    }
  else if (c == 13) // enter
    {
      on_change(text);
      on_enter(text);
    }
  else
    { // FIXME: This doesn't handle UTF8 properly 
      if (c < 256)
        {
          text += (unsigned char)c;
          on_change(text);
        }
    }
}

} // namespace Editor

/* EOF */
