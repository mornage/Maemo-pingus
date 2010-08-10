//  $Id: minimap.hpp 3257 2007-09-29 13:29:04Z grumbel $
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

#ifndef HEADER_PINGUS_EDITOR_MINIMAP_HPP
#define HEADER_PINGUS_EDITOR_MINIMAP_HPP

#include "gui/rect_component.hpp"

namespace Editor {

class EditorScreen;

/** */
class Minimap : public GUI::RectComponent
{
private:
  EditorScreen* editor;
  DrawingContext* drawing_context;
  bool dragging;
  
public:
  Minimap(EditorScreen*, const Rect& );
  ~Minimap();

  void draw (DrawingContext& gc);
  void update (float delta);

  void on_primary_button_press (int x, int y);
  void on_primary_button_release (int x, int y);
  void on_pointer_move(int x, int y);

  void update_layout();
};

} // namespace Editor

#endif

/* EOF */
