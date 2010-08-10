//  $Id: timer.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include "SDL.h"
#include "debug.hpp"
#include "globals.hpp"
#include "timer.hpp"


Timer::Timer(const char* desc)
  : description(desc),
    start_time(SDL_GetTicks())
{
}

void
Timer::stop()
{
  unsigned int time = SDL_GetTicks() - start_time;
  pout(PINGUS_DEBUG_LOADING)
    << "Timer: '" << description << "' took "
    << time << "msec" << std::endl;
}


/* EOF */
