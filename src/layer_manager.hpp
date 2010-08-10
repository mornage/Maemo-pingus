//  $Id: layer_manager.hpp 3265 2007-09-30 16:07:08Z grumbel $
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

#ifndef HEADER_PINGUS_LAYER_MANAGER_HXX
#define HEADER_PINGUS_LAYER_MANAGER_HXX

#include "pingus.hpp"
#include <cmath>
#include "sprite.hpp"
#include "display/display.hpp"
#include "display/drawing_context.hpp"


class LayerManager
{
private:
  class Layer
  {
  private:
    Sprite sur;

    float x_pos;
    float y_pos;

    float x_update;
    float y_update;

    float x_offset;
    float y_offset;

  public:
    Layer ()
      : x_pos(0), y_pos(0),
        x_update(0), y_update(0),
        x_offset(0), y_offset(0)
    {}

    Layer (const Sprite& arg_sur, float x_o, float y_o, float x_u, float y_u)
      : sur(arg_sur),
        x_pos(0), y_pos(0),
        x_update(x_u), y_update(y_u),
        x_offset(x_o), y_offset(y_o)
    {}

    void draw (DrawingContext& gc)
    {
      gc.draw(sur, Vector3f(x_pos + x_offset, y_pos + y_offset));
      gc.draw(sur, Vector3f(x_pos + x_offset - gc.get_width(), y_pos + y_offset));
    }

    void update (float delta)
    {
      x_pos = fmod((x_pos + x_update * delta),(float)Display::get_width());
      y_pos = fmod((y_pos + y_update * delta),(float)Display::get_height());
    }
  };

  std::vector<Layer> layers;

public:
  LayerManager ();
  ~LayerManager();

  void add_layer (Sprite sur, float x_o, float y_o, float x_u, float y_u);
  void draw (DrawingContext& gc);
  void update (float delta);

private:
  LayerManager (const LayerManager&);
  LayerManager& operator= (const LayerManager&);
};


#endif

/* EOF */
