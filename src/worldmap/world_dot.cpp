//  $Id: world_dot.cpp 2986 2007-08-17 16:20:09Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2006 Ingo Ruhnke <grumbel@gmx.de>
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

#include "world_dot.hpp"
#include "../stat_manager.hpp"
#include "../file_reader.hpp"

namespace WorldMapNS {

WorldDot::WorldDot(FileReader reader) :
	Dot(reader.read_section("dot")),
	is_accessible(false),
	is_finished(false)
{
	// Get the status from the StatManger
	StatManager::instance()->get_bool(name + "-accessible", is_accessible);
	StatManager::instance()->get_bool(name + "-finished", is_finished);
}

void
WorldDot::unlock()
{
	is_accessible = true;
	StatManager::instance()->set_bool(name + "-accessible", true);
}

}	// WorldMapNS namespace

/* EOF */
