//  $Id: direction.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_DIRECTION_HXX
#define HEADER_PINGUS_DIRECTION_HXX

#include "pingus.hpp"


/// Simple class for managing the direction of a pingu
class Direction
{
public:
  enum Dir { LEFT = -1, NONE = 0, RIGHT = +1 };
private:
  Dir direction;

public:
  Direction ();
  Direction (const Direction& dir);
  ~Direction ();

  Direction& operator= (const Direction&);

  operator int () const { return direction; }

  void change ();
  void left ();
  void right ();

  bool is_left () const;
  bool is_right () const;
};


#endif

/* EOF */
