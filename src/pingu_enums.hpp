//  $Id: pingu_enums.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_PINGU_ENUMS_HXX
#define HEADER_PINGUS_PINGU_ENUMS_HXX

#include "pingus.hpp"
#include <string>

/** The Pingus Status shows the current status of a Pingu, as
    displayed in the PingusCounter pannel. PS_DEAD are pingus that got
    killed, PS_ALIVE are pingus that are still active in the world and
    PS_EXITED are pingus that successfully finished a level

    FIXME: different subvalues of PS_DEAD might be usefull (drowned,
    FIXME: splashed, smashed, etc.) */
enum PinguStatus { PS_ALIVE, PS_EXITED, PS_DEAD };

namespace Actions {

/** The order of the actions here are the same as the order of actions
    in the buttonpanel, so if the order in the buttonpanel is not what
    it should be it needs to be changed here. */
enum ActionName
  { Angel,
    Basher,
    Blocker,
    Boarder,
    Bomber,
    Bridger,
    Climber,
    Digger,
    Drown,
    Exiter,
    Faller,
    Floater,
    Jumper,
    Laserkill,
    Miner,
    Rocketlauncher,
    Slider,
    Smashed,
    Splashed,
    Superman,
    Teleported,
    Waiter,
    Walker
  };

/** Converts a action enum into its internal string representation, as
    used in the xml or the resource files Bomber => "bomber" */
std::string action_to_string(ActionName action);

/** Converts a internal action string back into its action enum
    representation  "bomber" => Bomber */
ActionName  action_from_string(const std::string& action);

/** Convert a action enum into its visual representation, aka the
    thing that is seen on the screen for the user Bomber => "Bomber" */
std::string action_to_screenname(ActionName action);

} // namespace Actions

// Pingu "globals"
extern const int pingu_height;
extern const float deadly_velocity;

#endif


/* EOF */
