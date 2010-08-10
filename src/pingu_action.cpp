//  $Id: pingu_action.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include <assert.h>
#include <math.h>
#include "math/vector3f.hpp"
#include "col_map.hpp"
#include "world.hpp"
#include "pingu.hpp"
#include "pingu_action.hpp"
#include "worldobj.hpp"


PinguAction::PinguAction (Pingu* p)
  : pingu (p)
{
}

PinguAction::~PinguAction ()
{
}

// Checks if the pingu action needs to catch another pingu (needed for
// example by the blocker)
bool
PinguAction::need_catch ()
{
  return false;
}

// Wrapper around the colmap, to get the pixels infront of the pingu,
// from is current position
int
PinguAction::rel_getpixel (int x, int y)
{
  // FIXME: Inline me
  return WorldObj::get_world()->get_colmap()->getpixel(static_cast<int>(pingu->get_x() + (x * pingu->direction)),
                                                       static_cast<int>(pingu->get_y() - y));
}

ActionType
PinguAction::get_activation_mode () const
{
  return INSTANT;
}

char
PinguAction::get_persistent_char ()
{
  assert(!"This is not a persitent action!");
  return '-';
}

bool
PinguAction::head_collision_on_walk (int x, int y)
{
  int pixel = rel_getpixel(x, y + pingu_height);

  if (pixel != Groundtype::GP_NOTHING && !(pixel & Groundtype::GP_BRIDGE))
    return true;

  return false;
}

bool
PinguAction::collision_on_walk (int x, int y)
{
  bool collision = false;
  int pixel = Groundtype::GP_NOTHING;

  for (int pingu_y = 0; pingu_y <= pingu_height; ++pingu_y)
    {
      pixel = rel_getpixel(x, y + pingu_y);

      if (pixel != Groundtype::GP_NOTHING && pixel != Groundtype::GP_BRIDGE)
	{
	  collision = true;
	  break;
	}
    }

  return collision;
}

std::string
PinguAction::get_name () const
{
  return Actions::action_to_screenname(get_type());
}

void
PinguAction::move_with_forces ()
{
  // Apply gravity
  pingu->set_velocity(pingu->get_velocity() + Vector3f(0.0f, 1.0f));

#if 0 // New Code
  Vector3f pos        = pingu->get_pos();
  Vector3f target_pos = pos + pingu->get_velocity();
  Vector3f dir        = target_pos - pingu->get_pos();
  Vector3f velocity   = pingu->get_velocity();

  float length = dir.length();
  dir.normalize();

  for(float i = 0; i < length; ++i)
    {
      pingu->set_pos(pos + (dir * i));

      // If there is something below the Pingu
      if (rel_getpixel(0, -1) != Groundtype::GP_NOTHING)
        {
          // FIXME: this shouldn't be really here, but its a
          // FIXME: quick&dirty way to kill falling pingus
          if (velocity.y > Actions::Faller::deadly_velocity+1)
            {
              //std::cout << "Velocity: " << velocity << std::endl;
              pingu->set_action(Actions::Splashed);
              return;
            }
          else
            {
              // Make it so that the Pingu won't go down any further.
              pingu->set_velocity(Vector3f(0, 0));
              return;
            }
        }
      else if (head_collision_on_walk(0, 1))
        {
          return;
        }
      else if (collision_on_walk(1, 0))
        {
          // Make the Pingu bounce off the wall
          velocity.x = -velocity.x / 3.0f;
          pingu->set_velocity(velocity);
          pingu->direction.change();
          return;
        }
    }
#else // Old Code

  // FIXME: What does this variable do?
  Vector3f resultant_force = pingu->get_velocity();

  // FIXME: and what is this all about?! Can't we just use floats?
  // Strictly speaking x_numerator should be initialised with
  // (resultant_force.y / 2) and y_numerator with (resultant_force.x / 2).
  // This would make the algorithm essentially match the Mid-Point Line
  // Algorithm.  However, zero should do and is more comprehendable.
  int x_numerator = 0;
  int y_numerator = 0;
  int denominator = 0;
  int x_inc = 0;
  int y_inc = 0;

  if (fabs(resultant_force.x) > fabs(resultant_force.y))
    {
      // Initialise so that we move in whole pixels in x direction and
      // 'fractions' of a pixel in y direction.
      denominator = static_cast<int>(fabs(resultant_force.x));
      x_inc = denominator;
      y_inc = static_cast<int>(fabs(resultant_force.y));
    }
  else
    {
      // Initialise so that we move in whole pixels in y direction and
      // 'fractions' of a pixel in x direction.
      denominator = static_cast<int>(fabs(resultant_force.y));
      x_inc = static_cast<int>(fabs(resultant_force.x));
      y_inc = denominator;
    }

  Vector3f force_counter = resultant_force;

  // Keep moving the Pingu until there is only a fraction left
  while (   force_counter.x <= -1
            || force_counter.x >=  1
            || force_counter.y <= -1
            || force_counter.y >=  1)
    {
      x_numerator += x_inc;

      // Is it now not a fraction?
      if (x_numerator >= denominator)
	{
	  // Revert back to being a fraction
	  x_numerator -= denominator;

          // If there is something to the left of the Pingu
          if (collision_on_walk(1, 0))
            {
              // Make the Pingu reflect off the wall
              force_counter.x = -(force_counter.x);
              resultant_force.x = -(resultant_force.x/3);

              pingu->set_velocity(resultant_force);

              pingu->direction.change();
            }
          else
            {
              // Move the Pingu left
              pingu->set_x(pingu->get_x() + pingu->direction);
              force_counter.x -= pingu->direction;
            }
        }

      y_numerator += y_inc;

      // Is it now not a fraction?
      if (y_numerator >= denominator)
	{
	  // Revert back to being a fraction
	  y_numerator -= denominator;

	  // Move the Pingu depending on what the direction of the force is
	  if (force_counter.y >= 1)
	    {
	      // If there is something below the Pingu
	      if (rel_getpixel(0, -1) != Groundtype::GP_NOTHING)
		{
                  // FIXME: this shouldn't be really here, but its a
                  // FIXME: quick&dirty way to kill falling pingus
                  if (resultant_force.y >= deadly_velocity)
                    {
                      pingu->set_action(Actions::Splashed);
                      return;
                    }
		  // Make it so that the Pingu won't go down any further.
                  pingu->set_velocity(Vector3f(0, 0));
                  return;
		}
	      else
		{
		  // Move the Pingu down
		  pingu->set_y(pingu->get_y() + 1);
		  force_counter.y--;
		}
	    }
	  else if (force_counter.y <= -1)
	    {
	      // If there is something in the way above the Pingu
	      if (head_collision_on_walk(0, 1))
		{
		  // Make it so that the Pingu won't go up any further.
		  force_counter.y = 0;
		  resultant_force.y = 0;

		  pingu->set_velocity(resultant_force);
		}
	      else
		{
		  // Move the Pingu up
		  pingu->set_y(pingu->get_y() - 1);
		  force_counter.y++;
		}
	    }
	}
    }
#endif
}


/* EOF */
