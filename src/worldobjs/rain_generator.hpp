//  $Id: rain_generator.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_PARTICLES_RAIN_GENERATOR_HXX
#define HEADER_PINGUS_PARTICLES_RAIN_GENERATOR_HXX

#include "../worldobj.hpp"

namespace WorldObjs {

class RainGenerator : public WorldObj
{
private:
  bool  do_thunder;
  float thunder_count;
  float waiter_count;
public:
  RainGenerator(const FileReader& reader);
  ~RainGenerator();

  void update ();
  void draw (SceneContext& gc);
  float get_z_pos () const { return 1000; }

private:
  RainGenerator (const RainGenerator&);
  RainGenerator& operator= (const RainGenerator&);
};

} // namespace WorldObjs

#endif

/* EOF */
