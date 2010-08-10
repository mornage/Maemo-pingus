//  $Id: ground_particle.hpp 2986 2007-08-17 16:20:09Z grumbel $
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
#if 0
#ifndef HEADER_PINGUS_PARTICLES_GROUND_PARTICLE_HXX
#define HEADER_PINGUS_PARTICLES_GROUND_PARTICLE_HXX

#include "particle.hpp"

///
class GroundParticle : public Particle
{
private:
  int time;
public:
  GroundParticle(int x, int y, float x_a, float y_a);

  void update(float delta);
  void draw_offset(int ofx, int ofy, float s);

private:
  GroundParticle (const GroundParticle&);
  GroundParticle& operator= (const GroundParticle&);
};

#endif

/* EOF */
#endif
