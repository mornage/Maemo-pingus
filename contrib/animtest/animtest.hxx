//  $Id: animtest.hxx,v 1.1 2003/02/18 14:21:20 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_ANIMTEST_HXX
#define HEADER_ANIMTEST_HXX

#include <ClanLib/application.h>

class Sprite
{
public:

};

/** */
class Animtest : public CL_ClanApplication
{
private:
public:
  Animtest();
  int main(int argc, char** argv);
  char* get_title() { return "Pingus Anim Test"; }

private:
  Animtest (const Animtest&);
  Animtest& operator= (const Animtest&);
} app;

#endif

/* EOF */
