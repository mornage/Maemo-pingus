//  $Id: sprite.hpp 3170 2007-09-17 19:49:08Z grumbel $
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

#ifndef HEADER_SPRITE_HPP
#define HEADER_SPRITE_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include "math/origin.hpp"
#include "resource_modifier.hpp"
#include "SDL.h"

class Color;
class Surface;
class Pathname;
class SpriteImpl;
class SpriteDescription;

/** */
class Sprite
{
public:
  Sprite();
  Sprite(const Pathname& name);
  Sprite(const SpriteDescription& desc, ResourceModifierNS::ResourceModifier mod = ResourceModifierNS::ROT0);
  Sprite(const Surface& surface);
  ~Sprite();

  int get_width()  const;
  int get_height() const;

  void update(float delta = 0.033f);

  void draw(float x, float y, SDL_Surface* target);
  void set_hotspot(Origin origin, int x, int y);
  Vector2i get_offset() const;
  void set_frame(int i);
  int  get_frame_count() const;
  int  get_current_frame() const;
  bool is_finished() const;
  bool is_looping() const;
  void set_play_loop(bool loop = true);
  void restart();
  void finish();
  operator bool();
  SDL_Surface* get_surface() const;
  void set_surface(SDL_Surface* surface);

  /** Resizes the Sprite to the given size. This is a destructive
      operation. The original Surface will be lost. */
  void scale(int w, int h);

  /** Fills the Sprite with the given color. Transparent areas aren't
      touched.  This is a destructive operation. The original Surface
      will be lost. */
  void fill(const Color& color);

  /** Duplicate the underlying SDL_Surface to allow manipulation
      without affecting other references to it */
  void make_single_user();

  void apply_mod(ResourceModifierNS::ResourceModifier mod);

private:
  boost::shared_ptr<SpriteImpl> impl;
};

#endif

/* EOF */
