//  $Id: scene_context.hpp 3096 2007-09-06 16:12:02Z grumbel $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_SCENE_CONTEXT_HXX
#define HEADER_SCENE_CONTEXT_HXX

#include "SDL.h"
#include "drawing_context.hpp"

class SceneContextImpl;

/** The SceneContext maintains all the different drawing layers to
    which a game object can draw. Each drawing layer serves a
    different purporse and all are combined in the end to form the
    final image. */
class SceneContext
{
public:
  SceneContext();
  SceneContext(const Rect& rect);
  ~SceneContext();
  
  /** The main drawing context, also known as color buffer, to this
      you draw all normal graphics, sprites and enemies, as you would
      do with a normal framebuffer */
  DrawingContext& color();

  /** This is the lightmap, to this you draw all lights, meaning that
      a color of white will result in a area that is completly
      visible, while a value of black will mean that the area will be
      not lighted at all and be completly black. This lightmap is
      multiplied with the color buffer to get the light effect */
  DrawingContext& light();

  /** The highlight map is usefull for all objects that are extremly
      bright so that they generate a lenseflare or a glow. The
      highlight map doesn't light the scenario itself, but gets
      additionally rendered above the color and light buffer, thus its
      allows to add glow without risking to losing it in an area of
      darkness */
  DrawingContext& highlight();

  /** Translate the drawing context */
  void translate(float x, float y);

  /** Set the rotation of the drawing context */
  void rotate(float angel);

  /** Set the scaling of the drawing context */
  void scale(float x, float y);

  void push_modelview();
  void pop_modelview();
  void reset_modelview();

  void set_cliprect(const Rect& rect);
  void reset_cliprect();

  /** Takes all the buffers and combines them to form the final image
      that will be shown on the screen */
  void render(SDL_Surface* gc, const Rect& rect);

  void clear();
private:
  SceneContextImpl* impl;

  SceneContext (const SceneContext&);
  SceneContext& operator= (const SceneContext&);
};

class SceneContextDrawingRequest : public DrawingRequest
{
private:
  SceneContext* sc;

public:
  SceneContextDrawingRequest(SceneContext* sc, const Vector3f& pos_ = Vector3f(0,0,0));
  virtual ~SceneContextDrawingRequest();
  void render(SDL_Surface* gc, const Rect& render);
};


#endif

/* EOF */
