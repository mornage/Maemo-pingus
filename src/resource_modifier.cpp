//  $Id: resource_modifier.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include <assert.h>
#include "resource_modifier.hpp"

namespace ResourceModifierNS {

ResourceModifier horizontal_flip (ResourceModifier modifier)
{
  switch (modifier)
    {
    case ROT0:
      return ROT0FLIP;
    case ROT90:
      return ROT90FLIP;
    case ROT180:
      return ROT180FLIP;
    case ROT270:
      return ROT270FLIP;
    case ROT0FLIP:
      return ROT0;
    case ROT90FLIP:
      return ROT90;
    case ROT180FLIP:
      return ROT180;
    case ROT270FLIP:
      return ROT270;
    default:
      assert (0);
      return ROT0;
    }
}

ResourceModifier vertical_flip (ResourceModifier modifier)
{
  switch (modifier)
    {
    case ROT0:
      return ROT180FLIP;
    case ROT90:
      return ROT270FLIP;
    case ROT180:
      return ROT0FLIP;
    case ROT270:
      return ROT90FLIP;
    case ROT0FLIP:
      return ROT180;
    case ROT90FLIP:
      return ROT270;
    case ROT180FLIP:
      return ROT0;
    case ROT270FLIP:
      return ROT90;
    default:
      assert (0);
      return ROT0;
    }
}

ResourceModifier rotate_90 (ResourceModifier modifier)
{
  switch (modifier)
    {
    case ROT0:
      return ROT90;
    case ROT90:
      return ROT180;
    case ROT180:
      return ROT270;
    case ROT270:
      return ROT0;
    case ROT0FLIP:
      return ROT270FLIP;
    case ROT90FLIP:
      return ROT0FLIP;
    case ROT180FLIP:
      return ROT90FLIP;
    case ROT270FLIP:
      return ROT180FLIP;
    default:
      assert (0);
      return ROT0;
    }
}

ResourceModifier rotate_270 (ResourceModifier modifier)
{
  switch (modifier)
    {
    case ROT0:
      return ROT270;
    case ROT90:
      return ROT0;
    case ROT180:
      return ROT90;
    case ROT270:
      return ROT180;
    case ROT0FLIP:
      return ROT90FLIP;
    case ROT90FLIP:
      return ROT180FLIP;
    case ROT180FLIP:
      return ROT270FLIP;
    case ROT270FLIP:
      return ROT0FLIP;
    default:
      assert (0);
      return ROT0;
    }
}

std::string rs_to_string(ResourceModifier modifier)
{
  switch (modifier)
    {
    case ROT0:
      return "ROT0";
    case ROT90:
      return "ROT90";
    case ROT180:
      return "ROT180";
    case ROT270:
      return "ROT270";
    case ROT0FLIP:
      return "ROT0FLIP";
    case ROT90FLIP:
      return "ROT90FLIP";
    case ROT180FLIP:
      return "ROT180FLIP";
    case ROT270FLIP:
      return "ROT270FLIP";
    default:
      assert (0);
      return "--Error--";
    }
}

ResourceModifier rs_from_string (const std::string& modifier)
{
  if (modifier == "ROT0")
    return ROT0;
  else if (modifier == "ROT90")
    return ROT90;
  else if (modifier == "ROT180")
    return ROT180;
  else if (modifier == "ROT270")
    return ROT270;
  else if (modifier == "ROT0FLIP")
    return ROT0FLIP;
  else if (modifier == "ROT90FLIP")
    return ROT90FLIP;
  else if (modifier == "ROT180FLIP")
    return ROT180FLIP;
  else if (modifier == "ROT270FLIP")
    return ROT270FLIP;
  else
    {
      assert (0);
      return ROT0;
    }
}

} // namespace ResourceModifierNS

/* EOF */
