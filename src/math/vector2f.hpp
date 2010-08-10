//  $Id: vector2f.hpp 2986 2007-08-17 16:20:09Z grumbel $
//
//  SuperTux -  A Jump'n Run
//  Copyright (C) 2004 Matthias Braun <matze@braunis.de>
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

#ifndef SUPERTUX_VECTOR_H
#define SUPERTUX_VECTOR_H

#include <iosfwd>
#include "vector2i.hpp"

/** Simple two dimensional vector. */
class Vector2f
{
public:
  Vector2f(float nx, float ny)
      : x(nx), y(ny)
  { }
  Vector2f(const Vector2f& other)
      : x(other.x), y(other.y)
  { }
  Vector2f(const Vector2i& other)
    : x((float)other.x), y((float)other.y)
  {}
  Vector2f()
      : x(0), y(0)
  { }

  bool operator ==(const Vector2f& other) const
    {
      return x == other.x && y == other.y;
    }

  bool operator !=(const Vector2f& other) const
    {
      return !(x == other.x && y == other.y);
    }

  const Vector2f& operator=(const Vector2f& other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }

  Vector2f operator+(const Vector2f& other) const
    {
      return Vector2f(x + other.x, y + other.y);
    }

  Vector2f operator-(const Vector2f& other) const
    {
      return Vector2f(x - other.x, y - other.y);
    }

  Vector2f operator*(float s) const
    {
      return Vector2f(x * s, y * s);
    }

  Vector2f operator/(float s) const
    {
      return Vector2f(x / s, y / s);
    }

  Vector2f operator-() const
    {
      return Vector2f(-x, -y);
    }

  const Vector2f& operator +=(const Vector2f& other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  const Vector2f& operator -=(const Vector2f& other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  const Vector2f& operator *=(float val)
  {
    x *= val;
    y *= val;
    return *this;
  }

  const Vector2f& operator /=(float val)
  {
    x /= val;
    y /= val;
    return *this;
  }

  /** Takes angle in radian and returns a copy of the vector rotated
      by \a angle */
  Vector2f rotate(float angle) const;

  /// Scalar product of 2 vectors
  float operator*(const Vector2f& other) const
    {
      return x*other.x + y*other.y;
    }

  float magnitude() const;
  float length() const { return magnitude(); }

  Vector2f unit() const;
  void normalize();

  // ... add the other operators as needed, I'm too lazy now ...

  float x, y; // leave this public, get/set methods just give me headaches
  // for such simple stuff :)
};

std::ostream& operator<<(std::ostream& s, const Vector2f& v);

#endif

