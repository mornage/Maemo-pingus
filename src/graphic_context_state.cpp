//  $Id: graphic_context_state.cpp 3265 2007-09-30 16:07:08Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2004 Ingo Ruhnke <grumbel@gmx.de>
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

#include <math.h>
#include "math.hpp"
#include "display/display.hpp"
#include "graphic_context_state.hpp"

class GraphicContextStateImpl
{
public:
  Rect rect;
  
  Vector2f offset;
  float zoom;
  float rotation;

  bool have_limit;
  Rect limit;
};

GraphicContextState::GraphicContextState()
  : impl(new GraphicContextStateImpl())
{
  impl->rect       = Rect(Vector2i(0,0), Size(Display::get_width(), Display::get_height()));
  impl->offset     = Vector2f(0,0);
  impl->zoom       = 1.0f;
  impl->rotation   = 0;
  impl->have_limit = false;
}

GraphicContextState::GraphicContextState(int w, int h)
  : impl(new GraphicContextStateImpl())
{  
  impl->rect       = Rect(Vector2i(0,0), Size(w, h));
  impl->offset     = Vector2f(0,0); 
  impl->zoom       = 1.0f;
  impl->rotation   = 0;
  impl->have_limit = false;
}

GraphicContextState::GraphicContextState(const Rect& rect)
  : impl(new GraphicContextStateImpl())
{
  impl->rect       = rect;
  impl->offset     = Vector2f(0,0); 
  impl->zoom       = 1.0f;
  impl->rotation   = 0;
  impl->have_limit = false;  
}

void
GraphicContextState::set_limit(const Rect& limit)
{
  impl->have_limit = true;
  impl->limit      = limit;
}

void
GraphicContextState::set_unlimited()
{
  impl->have_limit = false;
}

void
GraphicContextState::set_size(int w, int h)
{
  impl->rect = Rect(Vector2i(impl->rect.left, impl->rect.top), Size(w, h));
}

void
GraphicContextState::push(DrawingContext& gc)
{
  gc.push_modelview();

  gc.translate((float)impl->rect.left, (float)impl->rect.top);

  gc.translate((float)get_width()/2, (float)get_height()/2);
  gc.rotate(impl->rotation);
  gc.translate(-(float)get_width()/2, -(float)get_height()/2);

  gc.scale(get_zoom(), get_zoom());
  gc.translate(impl->offset.x, impl->offset.y);
}

void
GraphicContextState::push(SceneContext& gc)
{
  gc.push_modelview();

  gc.translate((float)impl->rect.left, (float)impl->rect.top);

  gc.translate((float)get_width()/2, (float)get_height()/2);
  gc.rotate(impl->rotation);
  gc.translate(-(float)get_width()/2, -(float)get_height()/2);

  gc.scale(get_zoom(), get_zoom());
  gc.translate(impl->offset.x, impl->offset.y);
}

void
GraphicContextState::pop (SceneContext& gc)
{
  gc.pop_modelview();
}

void
GraphicContextState::pop (DrawingContext& gc)
{
  gc.pop_modelview();
}

Rect
GraphicContextState::get_clip_rect()
{
  return Rect(Vector2i(int(-impl->offset.x),
                       int(-impl->offset.y)),
              Size(int(get_width()  / impl->zoom),
                   int(get_height() / impl->zoom)));
}

void
GraphicContextState::set_pos(const Vector2f& pos)
{
  impl->offset.x = -pos.x + (get_width()/2  / impl->zoom);
  impl->offset.y = -pos.y + (get_height()/2 / impl->zoom);

  if (impl->have_limit)
    {
      if (-impl->offset.x < impl->limit.left)
        {
          impl->offset.x = (float)-(impl->limit.left);
        }
      else if (-impl->offset.x + get_width() > impl->limit.right)
        {
          if (impl->limit.right - impl->limit.left > get_width())
            impl->offset.x = (float)-(impl->limit.right - get_width());
          else
            impl->offset.x = (float)-(impl->limit.left);
        }

      if (-impl->offset.y < impl->limit.top)
        {
          impl->offset.y = (float)-(impl->limit.top);
        }
      else if (-impl->offset.y + get_height() > impl->limit.bottom)
        {
          if (impl->limit.bottom - impl->limit.top > get_height())
            impl->offset.y = (float)-(impl->limit.bottom - get_height());
          else
            impl->offset.y = (float)-(impl->limit.top);
        }
    }
}

Vector2f
GraphicContextState::get_pos() const
{
  return Vector2f(-impl->offset.x + (get_width()/2  / impl->zoom),
                  -impl->offset.y + (get_height()/2  / impl->zoom));
}

void
GraphicContextState::set_zoom(Vector2f pos, float z)
{
  float old_zoom = impl->zoom;
  set_zoom(z);
  impl->offset.x = pos.x/impl->zoom - pos.x/old_zoom + impl->offset.x;
  impl->offset.y = pos.y/impl->zoom - pos.y/old_zoom + impl->offset.y;
}

void
GraphicContextState::set_zoom(float z)
{
  impl->zoom = z;
}

float
GraphicContextState::get_zoom()
{
  return impl->zoom;
}

void
GraphicContextState::zoom_to (const Rectf& rect)
{
  float center_x = (rect.left + rect.right) / 2.0f;
  float center_y = (rect.top + rect.bottom) / 2.0f;

  float width  = rect.right - rect.left;
  float height = rect.bottom - rect.top;
  float screen_relation = float(get_height())/float(get_width ());
  float rect_relation   = height/width; 
  
  //std::cout << "Screen: " << screen_relation << " Zoom: " << rect_relation << std::endl;
  if (rect_relation < screen_relation) // take width, ignore height
    {
      impl->zoom = get_width()/width; 
    }
  else // take height, ignore width
    {
      impl->zoom = get_height()/height;
    }

  impl->offset.x = (get_width()  / (2*impl->zoom)) - center_x;
  impl->offset.y = (get_height() / (2*impl->zoom)) - center_y;
}

Vector2f
GraphicContextState::screen2world(const Vector2i& pos_) const
{
  Vector2f pos(float(pos_.x - impl->rect.left),
               float(pos_.y - impl->rect.top));

  float sa = (float)sin(-impl->rotation/180.0f*Math::pi);
  float ca = (float)cos(-impl->rotation/180.0f*Math::pi);

  float dx = pos.x - (float)get_width()/2;
  float dy = pos.y - (float)get_height()/2;

  pos.x = get_width()/2  + (ca * dx - sa * dy);
  pos.y = get_height()/2 + (sa * dx + ca * dy);

  Vector2f p((float(pos.x) / impl->zoom) - impl->offset.x, 
             (float(pos.y) / impl->zoom) - impl->offset.y);

  return p;
}

void
GraphicContextState::set_rotation(float angle)
{
  impl->rotation = angle;
}

float
GraphicContextState::get_rotation()
{
  return impl->rotation;
}

int
GraphicContextState::get_width()  const 
{
  return impl->rect.get_width(); 
}

int
GraphicContextState::get_height() const 
{ 
  return impl->rect.get_height(); 
}

/* EOF */
