//  $Id: smallmap_image.hpp 3147 2007-09-14 19:13:17Z grumbel $
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

#ifndef HEADER_PINGUS_SMALLMAP_IMAGE_HXX
#define HEADER_PINGUS_SMALLMAP_IMAGE_HXX

#include "pingus.hpp"
#include "sprite.hpp"

class Server;

/** The base image of the small map, it doesn't handle any userinput,
    it only generates the surface */
class SmallMapImage
{
private:
  Server* server;

  /** The canvas that represents the small-colmap */
  Surface canvas;

  /** Graphic surface for the generated rectanglar background of the small map */
  Sprite sur;

  /** number of seconds till the smallmap will update itself */
  float update_count;

  /** The serial is used to track changes to the colmap */
  unsigned int colmap_serial;

public:
  SmallMapImage (Server* s, int width, int height);
  void update (float delta);

  Sprite get_surface();
  
  /** Regenerate the smallmap surface */
  void update_surface();
private:
  SmallMapImage (const SmallMapImage&);
  SmallMapImage& operator= (const SmallMapImage&);
};


#endif

/* EOF */
