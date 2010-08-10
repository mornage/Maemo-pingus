//  $Id: pointer_factory.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include <iostream>
#include "../pingus_error.hpp"
#include "axis_factory.hpp"
#include "pointers/axis_pointer.hpp"
#include "pointers/mouse_pointer.hpp"
#include "pointers/multiple_pointer.hpp"
#include "pointer_factory.hpp"

namespace Input {

using namespace Pointers;

Pointer* PointerFactory::create (FileReader reader)
{
  if (reader.get_name() == "axis-pointer")
    return axis_pointer(reader);

  else if (reader.get_name() == "mouse-pointer")
    return mouse_pointer();

  else if (reader.get_name() == "multiple-pointer")
    return multiple_pointer(reader);

  else
    PingusError::raise(std::string("Unknown pointer type: ") + reader.get_name());

  return 0; // never reached
}

Pointer* PointerFactory::axis_pointer (FileReader reader)
{
  float speed;
  if (!reader.read_float("speed", speed))
    PingusError::raise("AxisPointer without speed parameter");

  std::vector<Axis*> axes;
  
  const std::vector<FileReader>& sections = reader.get_sections();
  for(std::vector<FileReader>::const_iterator i = sections.begin() + 1;
      i != sections.end(); ++i)
    {
      axes.push_back(AxisFactory::create(*i));
    }

  return new AxisPointer(speed, axes);
}

Pointer* PointerFactory::mouse_pointer ()
{
  return new MousePointer;
}

Pointer* PointerFactory::multiple_pointer (FileReader reader)
{
  std::vector<Pointer*> pointers;

  const std::vector<FileReader>& sections = reader.get_sections();
  for(std::vector<FileReader>::const_iterator i = sections.begin();
      i != sections.end(); ++i)
    pointers.push_back(create(*i));
  
  return new MultiplePointer(pointers);
}

} // namespace Input

/* EOF */
