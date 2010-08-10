//  $Id: pingu_particle_holder.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_PARTICLES_PINGU_PARTICLE_HOLDER_HXX
#define HEADER_PINGUS_PARTICLES_PINGU_PARTICLE_HOLDER_HXX

#include <vector>
#include "../sprite.hpp"
#include "../math/vector3f.hpp"
#include "../worldobj.hpp"


class SceneContext;

namespace Particles {

class PinguParticleHolder : public WorldObj
{
  struct PinguParticle {
    int  livetime;
    bool use_frame2;
    /// The current position of the particle
    Vector3f pos;

    /// The velocity of the particle
    Vector3f velocity;

    PinguParticle (int x, int y);
  };

private:
  Sprite surface;
  std::vector<PinguParticle> particles;

public:
  PinguParticleHolder ();

  void add_particle (int x, int y);

  float get_z_pos () const { return 1000.0f; }

  /// Let the particle move
  void update ();

  /// Draw the particle with the correct zoom resize
  void draw (SceneContext& gc);

private:
  PinguParticleHolder (const PinguParticleHolder&);
  PinguParticleHolder& operator= (const PinguParticleHolder&);
};

} // namespace Particles

#endif

/* EOF */
