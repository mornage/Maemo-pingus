//  $Id: faller.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_ACTIONS_FALLER_HXX
#define HEADER_PINGUS_ACTIONS_FALLER_HXX

#include "../state_sprite.hpp"
#include "../pingu_action.hpp"

namespace Actions {

class Faller : public PinguAction
{
private:
  StateSprite faller;
  StateSprite tumbler;

  int falling;

public:
  Faller(Pingu*);
  virtual ~Faller();

  void  draw (SceneContext& gc);
  void  update();

  bool change_allowed (Actions::ActionName new_action);

  ActionName get_type() const { return Actions::Faller; }
  bool is_tumbling () const;

private:
  Faller (const Faller&);
  Faller& operator= (const Faller&);
};

} // namespace Actions

#endif

/* EOF */
