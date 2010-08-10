//  $Id: triple_button.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include "triple_button.hpp"

namespace Input {
namespace Buttons {

TripleButton::TripleButton (Button* button1_, Button* button2_, Button* button3_)
  : button1(button1_),
    button2(button2_),
    button3(button3_),
    first_second_pressed(false),
    ignore_third(false)
{
}

TripleButton::~TripleButton ()
{
  delete button1;
  delete button2;
  delete button3;
}

void
TripleButton::update (float delta)
{
  button1->update(delta);
  button2->update(delta);
  button3->update(delta);

  if (button1->is_pressed() && button2->is_pressed())
    {
      if (!first_second_pressed)
        {
          first_second_pressed = true;
          ignore_third = button3->is_pressed();
        }
    }
  else
    {
      first_second_pressed = false;
      ignore_third         = true;
    }
}

bool
TripleButton::is_pressed() const
{
  return ( ! ignore_third && first_second_pressed && button3->is_pressed());
}

} // namespace Buttons
} // namespace Input

/* EOF */
