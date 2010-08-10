//  $Id: action_holder.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include <iostream>
#include "pingus_level.hpp"
#include "pingu_action_factory.hpp"
#include "action_holder.hpp"
#include "cheat.hpp"

using namespace Actions;

ActionHolder::ActionHolder(const PingusLevel& plf)
{
  const std::map<std::string, int>& actions = plf.get_actions();

  for(std::map<std::string, int>::const_iterator i = actions.begin(); i != actions.end(); ++i)
    {
      set_actions(Actions::action_from_string(i->first), i->second);
    }
}

ActionHolder::~ActionHolder ()
{
}

std::vector<Actions::ActionName>
ActionHolder::get_available_actions()
{
  std::vector<ActionName> ret;

  for(std::map<ActionName, int>::iterator i= available_actions.begin();
      i != available_actions.end(); ++i)
    ret.push_back(i->first);

  return ret;
}

void
ActionHolder::set_actions (ActionName name, int available)
{
  available_actions[name] = available;
}

void
ActionHolder::push_action (ActionName name)
{
  if (!Cheat::unlimited_actions)
    available_actions[name]++;
}

bool
ActionHolder::pop_action (ActionName name)
{
  if (Cheat::unlimited_actions)
    {
      return true;
    }
  else
    {
      int& avail = available_actions[name];

      if (avail > 0)
        {
          --avail;
          return true;
        }
      else
        {
          return false;
        }
    }
}

int
ActionHolder::get_available (ActionName name)
{
  return available_actions[name];
}

/* EOF */
