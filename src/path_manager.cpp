//  $Id: path_manager.cpp 3231 2007-09-22 15:46:31Z grumbel $
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

#include <sstream>
#include "globals.hpp"
#include "system.hpp"
#include "debug.hpp"
#include "path_manager.hpp"

PathManager path_manager;

PathManager::PathManager ()
  : path_found (false)
{
}

PathManager::~PathManager ()
{
}

void
PathManager::add_path (const std::string& path)
{
  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: add_path: " << path << std::endl;
  path_list.push_back (path);
}

std::string
PathManager::complete (const std::string& relative_path)
{
  std::string comp_path = base_path + "/" + relative_path;
  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: " << relative_path << " -> " << comp_path << std::endl;

  return comp_path;
}

/** Search for a path which contains the file 'file' */
bool
PathManager::find_path (const std::string& file)
{
  std::ostringstream out;
  for (PathIter i = path_list.begin (); !path_found && i != path_list.end (); ++i)
    {
      if (System::exist(*i + "/" + file))
	{
	  path_found = true;
	  base_path = *i;

	  return true;
	}
      else
        {
          out << "PathManager: Checking for file: '" << *i << "/" << file << "' failed" << std::endl;
        }
    }

  std::cout << out.str();
  std::cout << "PathManager: No base path found" << std::endl;

  return false;
}

void
PathManager::set_path (const std::string& path)
{
  base_path = path;
}


/* EOF */
