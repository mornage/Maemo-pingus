//  $Id: solid_color_background.hpp 3147 2007-09-14 19:13:17Z grumbel $
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

#ifndef HEADER_PINGUS_WORLDOBJS_SOLID_COLOR_BACKGROUND_HXX
#define HEADER_PINGUS_WORLDOBJS_SOLID_COLOR_BACKGROUND_HXX

#include "../math/color.hpp"
#include "../worldobj.hpp"

namespace WorldObjsData {
class SolidColorBackgroundData;
}

namespace WorldObjs {

class SolidColorBackground : public WorldObj
{
private:
  Color color;

public:
  SolidColorBackground(const FileReader& reader);

  // FIXME: Make z_position editable
  float get_z_pos () const { return -10; }
  void update () {}

  void draw (SceneContext& gc);

private:
  SolidColorBackground (const SolidColorBackground&);
  SolidColorBackground& operator= (const SolidColorBackground&);
};

} // namespace WorldObjs

#endif

/* EOF */
