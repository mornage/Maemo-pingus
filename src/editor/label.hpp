//  $Id: label.hpp 3166 2007-09-16 15:29:14Z grumbel $
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

#ifndef HEADER_LABEL_HPP
#define HEADER_LABEL_HPP

#include "gui/rect_component.hpp"

namespace Editor {

/** */
class Label : public GUI::RectComponent
{
private:
  std::string text;

public:
  Label(const Rect& rect, const std::string& text);

  bool is_at(int, int) { return false; }
  void draw (DrawingContext& gc);
  void update (float delta);
  void update_layout() {}

  void set_text(const std::string& text_) { text = text_; }
};

} // namespace Editor

#endif

/* EOF */
