//  $Id: object_selector_set.cpp 3166 2007-09-16 15:29:14Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#include "object_selector_set.hpp"

namespace Editor {

ObjectSelectorSet::ObjectSelectorSet(ObjectSelectorList* list_, int thumb_w, int thumb_h)
  : list(list_),
    thumb_size(thumb_w, thumb_h),
    offset(0)
{
}

ObjectSelectorSet::~ObjectSelectorSet()
{
  for(Objects::iterator i = objects.begin(); i != objects.end(); ++i)
    delete (*i);
}

void
ObjectSelectorSet::add(ObjectSelectorList::Object* obj)
{
  objects.push_back(obj);
}

int
ObjectSelectorSet::get_width() const
{
  return list->get_rect().get_width() / thumb_size.width;
}

int
ObjectSelectorSet::get_height() const
{
  return (objects.size() / get_width()) + ((objects.size() % get_width() > 0) ? 1 : 0);
}

} // namespace Editor

/* EOF */
