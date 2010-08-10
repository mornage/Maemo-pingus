//  $Id: evdev_driver.hpp 3253 2007-09-28 13:43:40Z grumbel $
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

#ifndef HEADER_PINGUS_INPUT_EVDEV_DRIVER_HPP
#define HEADER_PINGUS_INPUT_EVDEV_DRIVER_HPP

#include "driver.hpp"

namespace Input {

class EvdevDevice;

/** */
class EvdevDriver : public Driver
{
private:
  typedef std::vector<EvdevDevice*> Devices;
  Devices devices;

public:
  EvdevDriver();
  ~EvdevDriver();

  std::string get_name() const;
  void update(float delta);

  Button*   create_button  (const FileReader& reader, Control* parent);
  Axis*     create_axis    (const FileReader& reader, Control* parent);
  Scroller* create_scroller(const FileReader& reader, Control* parent);
  Pointer*  create_pointer (const FileReader& reader, Control* parent);
  Keyboard* create_keyboard(const FileReader& reader, Control* parent);

  EvdevDevice* get_device(const std::string& device_filename);
};

} // namespace Input

#endif

/* EOF */
