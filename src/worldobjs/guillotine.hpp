//  $Id: guillotine.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_WORLDOBJS_GUILLOTINE_HXX
#define HEADER_PINGUS_WORLDOBJS_GUILLOTINE_HXX

#include "../direction.hpp"
#include "../worldobj.hpp"


namespace WorldObjsData {
class GuillotineData;
}

class Pingu;

namespace WorldObjs {

class Guillotine : public WorldObj
{
private:
  Sprite   sprite_kill_right;
  Sprite   sprite_kill_left;  
  Sprite   sprite_idle;
  Vector3f      pos;
  Direction   direction;

  bool killing;

public:
  Guillotine(const FileReader& reader);

  float get_z_pos() const;

  void update();
  void draw(SceneContext& gc);
protected:
  void catch_pingu(Pingu*);

private:
  Guillotine(const Guillotine&);
  Guillotine& operator=(const Guillotine&);
};

} // namespace WorldObjs

#endif

/* EOF */
