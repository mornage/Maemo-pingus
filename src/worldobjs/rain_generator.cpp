//  $Id: rain_generator.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include <iostream>
#include "../particles/rain_particle_holder.hpp"
#include "../sound/sound.hpp"
#include "../world.hpp"
#include "../display/scene_context.hpp"
#include "rain_generator.hpp"

namespace WorldObjs {

RainGenerator::RainGenerator (const FileReader& reader)
  : do_thunder (false),
    thunder_count (0)
{
}

RainGenerator::~RainGenerator ()
{
}

void
RainGenerator::draw (SceneContext& gc)
{
  if (do_thunder)
    {
      if (thunder_count < 0.0f) {
      	do_thunder = false;
      	thunder_count = 0.0f;
      	waiter_count = 1.0f;
      }

      gc.color().fill_screen(Color(255, 255, 255, static_cast<int>(thunder_count*255)));
    }
}

void
RainGenerator::update()
{
  if (waiter_count < 0.0f && rand () % 150 == 0)
    {
      std::cout << "Doing thunder" << std::endl;
      do_thunder = true;
      thunder_count = 1.0f;
      waiter_count = 1.0f;
      Sound::PingusSound::play_sound ("sounds/thunder.wav");
    }

  if (do_thunder)
    thunder_count -= 10.0f * 0.025f;

  waiter_count -= 20.0f * 0.025f;

  for (int i=0; i < 16; ++i)
    world->get_rain_particle_holder()->add_particle(rand() % (world->get_width() * 2), -32);
}

} // namespace WorldObjs

/* EOF */
