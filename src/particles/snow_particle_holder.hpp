//  $Id: snow_particle_holder.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_PARTICLES_SNOW_PARTICLE_HOLDER_HXX
#define HEADER_PINGUS_PARTICLES_SNOW_PARTICLE_HOLDER_HXX

#include <vector>
#include "../sprite.hpp"
#include "../math/vector3f.hpp"
#include "../worldobj.hpp"


class SceneContext;

namespace Particles {

class SnowParticleHolder : public WorldObj
{
private:
  enum ParticleType { Snow1, Snow2, Snow3, Snow4, Snow5 };

  struct SnowParticle {
    bool         alive;
    bool         colliding;
    ParticleType type;
    Vector3f       pos;
    Vector3f       velocity;

    SnowParticle(int x, int y, bool colliding_);
  };

friend struct SnowParticle;

private:
  Sprite snow1;
  Sprite snow2;
  Sprite snow3;
  Sprite snow4;
  Sprite snow5;
  CollisionMask ground;

  std::vector<SnowParticle> particles;

public:
  SnowParticleHolder ();

  void add_particle (int x, int y, bool colliding = false);

  float get_z_pos () const { return 1000.0f; }

  /// Let the particle move
  void update ();

  /// Draw the particle with the correct zoom resize
  void draw (SceneContext& gc);

private:
  SnowParticleHolder (const SnowParticleHolder&);
  SnowParticleHolder& operator= (const SnowParticleHolder&);
};

} //namespace Particles

#endif

/* EOF */
