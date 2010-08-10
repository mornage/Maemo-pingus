//  $Id: teleporter_target.hpp 2908 2007-08-14 17:46:58Z grumbel $
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

#ifndef HEADER_PINGUS_WORLDOBJS_TELEPORTER_TARGET_HXX
#define HEADER_PINGUS_WORLDOBJS_TELEPORTER_TARGET_HXX

#include "../worldobj.hpp"

namespace WorldObjs {

class TeleporterTarget : public WorldObj
{
private:
  Vector3f pos;
  Sprite   sprite;

public:
  TeleporterTarget(const FileReader& reader);

  void  draw (SceneContext& gc);
  void  update ();
  float get_z_pos () const;
  Vector3f get_pos() const { return pos; }
  void  teleporter_used();
private:
  TeleporterTarget (const TeleporterTarget&);
  TeleporterTarget& operator= (const TeleporterTarget&);
};

} // namespace WorldObjs

#endif

/* EOF */
