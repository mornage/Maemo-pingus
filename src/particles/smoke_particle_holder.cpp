//  $Id: smoke_particle_holder.cpp 3277 2007-10-11 01:28:16Z plouj $
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

#include "../globals.hpp"
#include "../display/scene_context.hpp"
#include "../resource.hpp"
#include "smoke_particle_holder.hpp"

namespace Particles {

SmokeParticleHolder::SmokeParticle::SmokeParticle (float x, float y, float vel_x, float vel_y)
  : pos(Vector3f(x,y)), velocity(Vector3f(vel_x, vel_y))
{
  time = livetime = 25 + (rand() % 10);
  use_surf2 = rand() % 2;
}


SmokeParticleHolder::SmokeParticleHolder ()
  : surf1(Resource::load_sprite("particles/smoke")),
    surf2(Resource::load_sprite("particles/smoke2"))
{
}


void
SmokeParticleHolder::add_particle (float x, float y, float vel_x, float vel_y)
{
  // search for dead entry to replace
  for (std::vector<SmokeParticle>::iterator it=particles.begin(); it != particles.end(); ++it)
    if (!it->livetime)
      {
        *it = SmokeParticle(x, y, vel_x, vel_y);
	    return;
	  }

	// create new entry
  particles.push_back(SmokeParticle(x, y, vel_x, vel_y));
}

void
SmokeParticleHolder::update ()
{
  // update all contained particles
  for (std::vector<SmokeParticle>::iterator it=particles.begin(); it != particles.end(); ++it)
    {
      // skip dead particles
      if (!it->livetime)
        continue;

      it->pos.x += it->velocity.x;
	  it->pos.y += it->velocity.y;

	  --it->livetime;
    }
}


void
SmokeParticleHolder::draw (SceneContext& gc)
{
  for (std::vector<SmokeParticle>::iterator it=particles.begin(); it != particles.end(); ++it)
    {
      if (!it->livetime)
        continue;

      if (!it->use_surf2)
        gc.color().draw(surf1, it->pos);
	  else
	    gc.color().draw(surf2, it->pos);
    }
}

} // namespace Particles

/* EOF */
