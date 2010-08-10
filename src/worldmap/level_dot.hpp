//  $Id: level_dot.hpp 3328 2007-10-26 04:19:25Z grumbel $
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

#ifndef HEADER_PINGUS_WORLDMAP_LEVEL_DOT_HXX
#define HEADER_PINGUS_WORLDMAP_LEVEL_DOT_HXX

#include "../sprite.hpp"
#include "../pingus_level.hpp"
#include "dot.hpp"

namespace WorldMapNS {

/** */
class LevelDot : public Dot
{
private:
  Sprite green_dot_sur;
  Sprite red_dot_sur;
  Sprite inaccessible_dot_sur;
  Sprite highlight_green_dot_sur;
  Sprite highlight_red_dot_sur;

  PingusLevel plf;

public:
  LevelDot(FileReader reader);

  void draw(DrawingContext& gc);
  void draw_hover(DrawingContext& gc);

  void update(float delta);
  PingusLevel get_plf () const { return plf; }
  void on_click();

  bool finished();
  bool accessible();
  void unlock();

private:
  LevelDot (const LevelDot&);
  LevelDot& operator= (const LevelDot&);
};

} // namespace WorldMapNS

#endif

/* EOF */
