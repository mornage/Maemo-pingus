//  $Id: font_description.cpp 3090 2007-09-05 19:08:47Z grumbel $
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

#include "pingus_error.hpp"
#include "file_reader.hpp"
#include "font_description.hpp"

FontDescription::FontDescription(const Pathname& pathname_)
  : pathname(pathname_)
{
  name            = "<unknown>";
  monospace       = false;
  space_length    = 20;
  alpha_threshold = 0;
  char_spacing    = 1.0f;
  vertical_spacing = -1.0f;

  FileReader reader = FileReader::parse(pathname);

  if (reader.get_name() != "pingus-font")
    {
      PingusError::raise("FontDescription: not a pingus-font file");
    }
  else
    {
      reader.read_string("name",          name);
      reader.read_path("image",           image);
      reader.read_string("characters",    characters);
      reader.read_bool("monospace",       monospace);
      reader.read_float("char-spacing",     char_spacing);
      reader.read_float("vertical-spacing", vertical_spacing);
      reader.read_int("space-length",     space_length);
      reader.read_int("alpha-threshold",  alpha_threshold);
    }
}

/* EOF */
