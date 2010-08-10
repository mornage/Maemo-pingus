//  $Id: hurry_up.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_HURRY_UP_HXX
#define HEADER_PINGUS_HURRY_UP_HXX

#include "../gui/component.hpp"

#include "../font.hpp"

class DrawingContext;
class Client;

/** Hurry up if the time goes over... */
class HurryUp : public GUI::Component
{
private:
  Font font;
  bool is_running;
  bool is_finished;
  bool center_reached;
  Client* client;

  int  wait_counter;
  float x_pos;

  float speed;

public:
  HurryUp(Client*);
  virtual ~HurryUp();

  void draw(DrawingContext& gc);
  void update(float delta);
  void set_client(Client*);

private:
  HurryUp (const HurryUp&);
  HurryUp& operator= (const HurryUp&);
};


#endif
