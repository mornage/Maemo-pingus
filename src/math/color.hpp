//  $Id: color.hpp 2987 2007-08-17 16:25:49Z grumbel $
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

#ifndef HEADER_MATH_COLOR_HPP
#define HEADER_MATH_COLOR_HPP

#include "SDL.h"

/** */
class Color
{
public:
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Color()
    : r(0), g(0), b(0), a(255)
  {}

  Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255)
    : r(r_), g(g_), b(b_), a(a_)
  {}
};

#endif

/* EOF */
