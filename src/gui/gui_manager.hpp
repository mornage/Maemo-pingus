//  $Id: gui_manager.hpp 3142 2007-09-14 15:39:32Z grumbel $
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

#ifndef HEADER_PINGUS_GUI_GUI_MANAGER_HXX
#define HEADER_PINGUS_GUI_GUI_MANAGER_HXX

#include <vector>
#include "../input/event.hpp"
#include "group_component.hpp"

class DrawingContext;
class GameDelta;

namespace GUI {

/** The GUIManager class holds a group of components and manages
    them. It dispatches the GameDelta to each individual
    component

    FIXME: We translate GameDelta into another 'language' which is
    then understood by the GUI, this seems unclear, not sure at
    which point it is best to split the GameDelta into
    on_primary_button_press(), etc.
*/
class GUIManager : public GroupComponent
{
private:
  Vector2i mouse_pos;

  void process_input (const GameDelta& delta);
  void process_pointer_event (const Input::PointerEvent& event);
  void process_button_event (unsigned int time_stamp, const Input::ButtonEvent& event);
  void process_keyboard_event (const Input::KeyboardEvent& event);

public:
  GUIManager();
  GUIManager(const Rect&);
  virtual ~GUIManager ();

  void update(const GameDelta& delta);

private:
  GUIManager (const GUIManager&);
  GUIManager& operator= (const GUIManager&);
};

} // namespace GUI

#endif

/* EOF */
