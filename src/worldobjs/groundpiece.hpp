//  $Id: groundpiece.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_WORLDOBJS_GROUNDPIECE_HXX
#define HEADER_PINGUS_WORLDOBJS_GROUNDPIECE_HXX

#include "../res_descriptor.hpp"
#include "../groundtype.hpp"
#include "../worldobj.hpp"
#include "../math/vector3f.hpp"


namespace WorldObjsData {
class GroundpieceData;
}

namespace WorldObjs {

/** Groundpieces form the ground on which the pingus can walk, which
    they can dig and which they can detonate away */
class Groundpiece : public WorldObj
{
private:
  Vector3f        pos;
  ResDescriptor desc;
  Groundtype::GPType gptype;

public:
  Groundpiece(const FileReader& reader);

  float get_z_pos () const { return pos.z; }

  void draw (SceneContext&) {}
  void on_startup ();
  bool purge_after_startup () { return true; }
private:
  Groundpiece (const Groundpiece&);
  Groundpiece& operator= (const Groundpiece&);
};

} // namespace WorldObjs

#endif

/* EOF */
