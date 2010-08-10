//  $Id: savegame.cpp 3328 2007-10-26 04:19:25Z grumbel $
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

#include <iostream>
#include "sexpr_file_writer.hpp"
#include "savegame.hpp"
#include "string_util.hpp"

std::string
Savegame::status_to_string(S_Status status)
{
  switch (status)
    {
    case FINISHED:
      return "finished";

    case ACCESSIBLE:
      return "accessible";

    case NONE:
    default:
      return "none";
    }
}

Savegame::S_Status
Savegame::string_to_status (std::string str)
{
  str = StringUtil::to_lower(str);
  if (str == "accessible")
    return ACCESSIBLE;
  else if (str == "finished")
    return FINISHED;
  else if (str == "none")
    return NONE;
  else
    return NONE;
}

Savegame::Savegame()
{
  status = ACCESSIBLE;
  saved_pingus = 0;
  needed_time = 0;
}

Savegame::Savegame(FileReader reader)
{
  read_sexpr(reader);
}

Savegame::Savegame(const std::string& filename_, 
                   S_Status status_, 
                   int      time_,
                   int      saved_pingus_)
  : filename(filename_),
    status(status_),
    needed_time(time_),
    saved_pingus(saved_pingus_)
{
}

void
Savegame::write_sexpr(SExprFileWriter& writer)
{
  writer.begin_section("level");
  writer.write_string ("filename", filename);
  writer.write_enum   ("status",   status, status_to_string);
  writer.write_int    ("time",     needed_time);
  writer.write_int    ("saved-pingus", saved_pingus);
  writer.end_section();
}

void
Savegame::read_sexpr(FileReader reader)
{
  reader.read_string ("filename", filename);
  reader.read_enum   ("status",   status, string_to_status);
  reader.read_int    ("time",     needed_time);
  reader.read_int    ("saved-pingus", saved_pingus);
}

/* EOF */
