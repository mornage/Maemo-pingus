//  $Id: miner.hpp 3216 2007-09-22 01:47:03Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_ACTIONS_MINER_HXX
#define HEADER_PINGUS_ACTIONS_MINER_HXX

#include "../pingu_action.hpp"
#include "../state_sprite.hpp"

namespace Actions {

class Miner : public PinguAction
{
private:
  CollisionMask miner_radius;
  StateSprite sprite;
  int slow_count;

public:
  Miner (Pingu* p);
  virtual ~Miner () {}

  ActionName get_type () const { return Actions::Miner; }

  void draw (SceneContext& gc);
  void update ();

private:
  Miner (const Miner&);
  Miner& operator= (const Miner&);
};

} // namespace Actions

#endif

/* EOF */
