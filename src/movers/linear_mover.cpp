//  $Id: linear_mover.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include "linear_mover.hpp"
#include "../collider.hpp"

namespace Movers {

LinearMover::LinearMover(World* const world_arg, const Vector3f& pos_arg)
  : Mover(world_arg, pos_arg)
{
}

LinearMover::~LinearMover()
{
}

void LinearMover::update(const Vector3f& move, const Collider& collision_check)
{
  Vector3f target_pos = pos + move;
  Vector3f step_vector = move;

  // Static cast to stop warning
  int move_length = static_cast<int>(move.length());

  // Make the step vector (i.e. change to a unit vector)
  step_vector.normalize();

  collision = false;

  // Move to the destination one unit vector at a time
  for (int i = 0; i < move_length && !collision; ++i)
    {
      collision = collision_check(world, pos, step_vector);

      pos += step_vector;
    }

  // If on a collision pixel, back away from it.
  if (collision)
    pos -= step_vector;

  remaining_move = target_pos - pos;
}

} // namespace Movers

/* EOF */
