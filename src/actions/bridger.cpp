//  $Id: bridger.cpp 3340 2007-10-27 07:08:51Z grumbel $
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

#include <cassert>
#include "../col_map.hpp"
#include "../display/scene_context.hpp"
#include "../pingu.hpp"
#include "../ground_map.hpp"
#include "../resource.hpp"
#include "../sound/sound.hpp"
#include "../world.hpp"
#include "../worldobj.hpp"
#include "../gettext.h"
#include "../string_util.hpp"
#include "bridger.hpp"

namespace Actions {

Bridger::Bridger (Pingu* p)
  : PinguAction(p),
    mode(B_BUILDING),
    brick_l("other/brick_left"),
    brick_r("other/brick_right"),
    bricks(MAX_BRICKS),
    block_build(false),
    name(_("Bridger") + std::string(" (" + StringUtil::to_string(bricks) + ")"))
{
  walk_sprite.load (Direction::LEFT,  Resource::load_sprite("pingus/player" + 
                                                            pingu->get_owner_str() + "/bridger_walk/left"));
  walk_sprite.load (Direction::RIGHT, Resource::load_sprite("pingus/player" + 
                                                            pingu->get_owner_str() + "/bridger_walk/right"));

  build_sprite.load(Direction::LEFT,  Resource::load_sprite("pingus/player" + 
                                                             pingu->get_owner_str() + "/bridger/left"));
  build_sprite.load(Direction::RIGHT, Resource::load_sprite("pingus/player" + 
                                                             pingu->get_owner_str() + "/bridger/right"));
}

void
Bridger::draw (SceneContext& gc)
{
  int x_offset(6), y_offset(4);

  if (bricks == MAX_BRICKS) {
    x_offset = -4;
    y_offset = 0;

  } else if (bricks == MAX_BRICKS - 1) {
    x_offset = 0;
    y_offset = 1;
  } else if (bricks == MAX_BRICKS - 2) {
    x_offset = 3;
    y_offset = 2;
  }

  switch (mode)
    {
    case B_BUILDING:
      gc.color().draw(build_sprite[pingu->direction], Vector3f(pingu->get_pos().x - (x_offset * pingu->direction),
                                                             pingu->get_pos().y + y_offset));
      break;

    case B_WALKING:
      gc.color().draw(walk_sprite[pingu->direction], Vector3f(pingu->get_pos().x - (x_offset * pingu->direction),
                                                            pingu->get_pos().y + y_offset));
      break;
    }
}

void
Bridger::update()
{
  switch (mode)
    {
    case B_BUILDING:
      update_build ();
      break;

    case B_WALKING:
      update_walk ();
      break;
    }
}

void
Bridger::update_walk ()
{
  if (walk_sprite[pingu->direction].is_finished ()) // FIXME: Dangerous! might not be fixed timing
    {
      if (way_is_free())
	{
	  mode = B_BUILDING;
	  block_build = false;
	  walk_sprite[pingu->direction].restart();
	  walk_one_step_up();
	}
      else // We reached a wall...
	{
	  pingu->direction.change ();
	  pingu->set_action (Actions::Walker);
	  return;
	}
    }
  else
    {
      walk_sprite.update ();
    }
}

void
Bridger::update_build ()
{
  build_sprite[pingu->direction].update (0.033f);

  if (build_sprite[pingu->direction].get_current_frame () >= 7 && !block_build)
    {
      block_build = true;

      if (bricks > 0)
	{
	  if (brick_placement_allowed())
	    place_a_brick();
	  else
	    {
	      pingu->direction.change ();
	      pingu->set_action (Actions::Walker);
	      return;
	    }
	}
      else // Out of bricks
	{
	  pingu->set_action(Actions::Waiter);
          return;
	}
    }

  if (build_sprite[pingu->direction].is_finished ())
    {
      mode = B_WALKING;
      build_sprite[pingu->direction].restart();
    }
}

// way_is_free() needs to stop BRIDGERS from getting stuck between a brick
// and the ceiling.  The routine also stops cases of Bridgers building up but
// then not being able to walk all the way down the bridge the it has built.
// Even though the routine may be the same as brick_placement_allowed(), it is
// best to keep them apart as they may need to be independent of each other if
// there needs to be a patch.
bool
Bridger::way_is_free()
{
  bool way_free = true;

  for (int x_inc = 1; x_inc <= 4; x_inc++)
    {
      if (rel_getpixel(x_inc, 2) != Groundtype::GP_NOTHING
	  || head_collision_on_walk(x_inc, 2))
	{
	  way_free = false;
	  break;
	}
    }

  return way_free;
}

// brick_placement_allowed() is mainly for stopping WALKERS from getting stuck
// between a brick and the ceiling.  Even though the routine may be the same,
// as way_is_free() it is best to keep them apart as they may need to be
// independent of each other if there needs to be a patch.
bool
Bridger::brick_placement_allowed(void)
{
#ifdef BRIDGER_HEAD_COLLISION_CHECK
  bool brick_allowed = true;

  // Don't allow a brick to be placed if a Pingu would have a head collision
  // if it walked along the whole of the brick.  Otherwise the Pingu,
  // especially a walker, could get stuck between the brick and the ceiling.
  for (int x_inc = 1; x_inc <= brick_length; ++x_inc)
    {
      if (head_collision_on_walk(x_inc, 2))
	{
	  brick_allowed = false;
	  break;
	}
    }

  return brick_allowed;
#else
  return !head_collision_on_walk(0, 2);
#endif
}

void
Bridger::place_a_brick()
{
  bricks--;
  name = _("Bridger") + std::string(" (") + StringUtil::to_string(bricks) + ")";

  if (bricks < 4)
    Sound::PingusSound::play_sound("ting");

  if (pingu->direction.is_right())
    {
      WorldObj::get_world()->put(brick_r,
                                 static_cast<int>(pingu->get_pos().x + 10 - brick_r.get_width()),
                                 static_cast<int>(pingu->get_pos().y),
                                 Groundtype::GP_BRIDGE);
    }
  else
    {
      WorldObj::get_world()->put(brick_l,
                                 static_cast<int>(pingu->get_pos().x - 10),
                                 static_cast<int>(pingu->get_pos().y),
                                 Groundtype::GP_BRIDGE);
    }
}

void
Bridger::walk_one_step_up()
{
  pingu->set_pos(pingu->get_pos().x + (float)(4 * pingu->direction), 
                 pingu->get_pos().y - 2);
}

std::string
Bridger::get_name () const
{
  return name;
}

} // namespace Actions

/* EOF */
