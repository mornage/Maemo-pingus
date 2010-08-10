//  $Id: button_panel.hpp 3126 2007-09-11 16:25:16Z grumbel $
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

#ifndef HEADER_PINGUS_BUTTON_PANEL_HXX
#define HEADER_PINGUS_BUTTON_PANEL_HXX

#include <vector>

#include "action_button.hpp"


class Client;

class ButtonPanel : public GUI::Component
{
private:
  friend class ClientEvent;

  Client* client;
  TrueServer* server;

  std::vector<ActionButton*> a_buttons;
  typedef std::vector<ActionButton*>::iterator AButtonIter;
  int pressed_button;

  bool left_pressed;
  unsigned int  last_press;

  int x_pos, y_pos;

public:
  ButtonPanel(Client* c, int arg_x_pos, int arg_y_pos);
  virtual ~ButtonPanel();

  void on_primary_button_press(int x, int y);
  void on_primary_button_release(int x, int y);

  bool is_at (int x, int y);

  Actions::ActionName get_action_name();
  void   update(float delta);
  void   draw(DrawingContext& gc);

  /// Set n'th action
  void   set_button(int);

  /// Select the next action
  void next_action ();

  /// Select the previous action
  void previous_action ();

private:
  ButtonPanel (const ButtonPanel&);
  ButtonPanel& operator= (const ButtonPanel&);
};


#endif

/* EOF */
