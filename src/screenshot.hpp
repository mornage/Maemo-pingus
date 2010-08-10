//  $Id: screenshot.hpp 2993 2007-08-17 16:53:51Z jsalmon3 $
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

#ifndef HEADER_PINGUS_SCREENSHOT_HXX
#define HEADER_PINGUS_SCREENSHOT_HXX

#include "SDL.h"
#include "pingus.hpp"
#include <string>


/** Simple class to get a screenshot and save it as pnm */
class Screenshot
{
private:
  static std::string get_date();
  static std::string get_filename();

public:
  static std::string make_screenshot();
  static void save(SDL_Surface* surface, const std::string& filename);

  /** buffer must be RGB and width*height*3 large */
  static void save_ppm(const std::string& filename, uint8_t* buffer, int width, int height);
  static void save_png(const std::string& filename, uint8_t* buffer, int width, int height);
private:
  Screenshot ();
  Screenshot (const Screenshot&);
  Screenshot& operator= (const Screenshot&);
};


#endif

/* EOF */
