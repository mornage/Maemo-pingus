//  $Id: surface.hpp 3396 2007-10-30 06:59:28Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_SURFACE_HPP
#define HEADER_SURFACE_HPP

#include "SDL.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include "math/size.hpp"
#include "resource_modifier.hpp"
#include "pathname.hpp"
#include "math/color.hpp"

class Rect;
class Pathname;
class SurfaceImpl;

/** */
class Surface
{
public:
  Surface();

  Surface(boost::shared_ptr<SurfaceImpl> impl);

  Surface(const Pathname& name);

  /** Create an empty RGBA Surface */
  Surface(int width, int height);

  /** Create an empty Indexed Surface (8bit) */
  Surface(int width, int height, SDL_Palette* palette, int colorkey = -1);

  /** Create a Surface from a SDL_Surface */
  Surface(SDL_Surface* surface, bool delete_surface = true);

  ~Surface();

  uint8_t* get_data() const;
  void lock();
  void unlock();

  Size get_size()   const;
  int  get_width()  const;
  int  get_height() const;
  int  get_pitch()  const;

  void blit(const Surface& source, int x, int y);

  Color get_pixel(int x, int y) const;

  void fill(const Color& color);
  void optimize();

  Surface scale(int w, int h);
  Surface mod(ResourceModifierNS::ResourceModifier mod);
  Surface clone() const;
  Surface subsection(const Rect& rect) const;

  SDL_Surface* get_surface() const;

  operator bool() const;

  bool is_shared() const;

  void print(std::ostream& out);

protected:
  boost::shared_ptr<SurfaceImpl> impl;
};

#endif

/* EOF */
