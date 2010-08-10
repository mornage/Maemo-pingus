//  $Id: dummy_screen.hpp 3265 2007-09-30 16:07:08Z grumbel $
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

#ifndef HEADER_PINGUS_DUMMY_SCREEN_HXX
#define HEADER_PINGUS_DUMMY_SCREEN_HXX

#include "screen/screen.hpp"


class DrawingContext;

/** DummyScreen without any actual functionality, just for testing */
class DummyScreen : public Screen
{
private:

public:
  DummyScreen () { }
  virtual ~DummyScreen () {}

  /** Draw this screen @return true if draw was successfull, false if
      frameskip has taken place ('causes a skip of flip_display) */
  bool draw (DrawingContext& gc) { return 0; }

  /** Pass a delta to the screen */
  void update (const GameDelta& delta) {}

private:
  DummyScreen (const DummyScreen&);
  DummyScreen& operator= (const DummyScreen&);
};


#endif

/* EOF */
