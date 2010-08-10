//  $Id: levelset.hpp 3351 2007-10-28 07:51:14Z grumbel $
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

#ifndef HEADER_LEVELSET_HPP
#define HEADER_LEVELSET_HPP

#include <string>
#include <vector>
#include "pingus_level.hpp"
#include "pathname.hpp"
#include "sprite.hpp"

/** */
class Levelset
{
public:
  struct Level {
    std::string resname;
    bool accessible;
    bool finished;
    PingusLevel plf;
  };

private:
  std::string title;
  std::string description;
  Sprite image;
  int  completion;
  std::vector<Level*> levels;

public:
  Levelset(const Pathname& pathname);
  ~Levelset();

  std::string get_title() const;
  std::string get_description() const;
  Sprite get_image() const;

  Level* get_level(int num) const;
  int get_level_count() const;

  /** Return the number of completed levels */
  int get_completion()  const;

  void refresh();
private:
  Levelset (const Levelset&);
  Levelset& operator= (const Levelset&);
};

#endif

/* EOF */
