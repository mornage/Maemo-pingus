//  $Id: bridger.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_ACTIONS_BRIDGER_HXX
#define HEADER_PINGUS_ACTIONS_BRIDGER_HXX

#include "../math/vector3f.hpp"
#include "../pingu_action.hpp"
#include "../state_sprite.hpp"

namespace Actions {

class Bridger : public PinguAction
{
private:
  enum Mode { B_WALKING, B_BUILDING } mode;
  enum { MAX_BRICKS = 15 };
  enum { brick_length = 16 };

private:
  StateSprite walk_sprite;
  StateSprite build_sprite;
  CollisionMask brick_l;
  CollisionMask brick_r;

  int bricks;
  //int step;
  //int do_steps;
  bool block_build;

  std::string name;
public:
  Bridger(Pingu*);

  std::string get_name () const;
  ActionName get_type () const { return Actions::Bridger; }

  void   update ();
  void   update_build ();
  void   update_walk ();

  void   draw (SceneContext& gc);

  bool   way_is_free ();
  bool   brick_placement_allowed (void);
  void   place_a_brick ();
  void   walk_one_step_up ();

private:
  Bridger (const Bridger&);
  Bridger& operator= (const Bridger&);
};

} // namespace Actions

#endif

/* EOF */
