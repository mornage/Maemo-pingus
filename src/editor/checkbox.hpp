//  $Id: checkbox.hpp 3166 2007-09-16 15:29:14Z grumbel $
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

#ifndef HEADER_CHECKBOX_HPP
#define HEADER_CHECKBOX_HPP

#include <boost/signal.hpp>
#include "gui/rect_component.hpp"

namespace Editor {

/** */
class Checkbox : public GUI::RectComponent
{
private:
  bool checked;
  std::string label;

public:
  Checkbox(const Rect& rect, const std::string& label = "");
  ~Checkbox();

  void draw(DrawingContext& gc);
  void update_layout() {}
  
  void set_checked(bool t);
  bool is_checked() const { return checked; }
  void on_primary_button_press(int x, int y);

  boost::signal<void (bool)> on_change;
 
private:
  Checkbox (const Checkbox&);
  Checkbox& operator= (const Checkbox&);
};

} // namespace Editor

#endif

/* EOF */
