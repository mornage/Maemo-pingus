//  $Id: evdev_driver.cpp 3271 2007-10-01 17:24:54Z grumbel $
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

#include "evdev_device.hpp"
#include "evdev_driver.hpp"

namespace Input {

EvdevDriver::EvdevDriver() 
{
}

EvdevDriver::~EvdevDriver() 
{ 
  for(Devices::iterator i = devices.begin(); i != devices.end(); ++i)
    {
      delete *i;
    }
}

std::string
EvdevDriver::get_name() const
{
  return "evdev";
}

void
EvdevDriver::update(float delta)
{
  for(Devices::iterator i = devices.begin(); i != devices.end(); ++i)
    {
      (*i)->update(delta);
    }
}

EvdevDevice*
EvdevDriver::get_device(const std::string& device_filename)
{
  for(Devices::iterator i = devices.begin(); i != devices.end(); ++i)
    {
      if ((*i)->get_device() == device_filename)
        return *i;
    }

  try {
  EvdevDevice* device = new EvdevDevice(device_filename);
  devices.push_back(device);
  return device;
  } catch (std::exception& err) {
    std::cout << "EvdevDriver: " << err.what() << std::endl;
    return 0;
  }
}

Button*
EvdevDriver::create_button(const FileReader& reader, Control* parent)
{
  std::string device_filename;
  int button;
  if (reader.read_string("device", device_filename) &&
      reader.read_int("button", button))
    {
      EvdevDevice* device = get_device(device_filename);
      return device->create_button(parent, button);
    }
  else
    {
      std::cout << "Error: Some of 'device', 'button' missing" << std::endl;
      return 0;
    }
}

Axis*
EvdevDriver::create_axis(const FileReader& reader, Control* parent)
{
  return 0;
}

Scroller*
EvdevDriver::create_scroller(const FileReader& reader, Control* parent)
{
  std::string device_filename;
  int x, y;
  if (reader.read_string("device", device_filename) &&
      reader.read_int("x", x) &&
      reader.read_int("y", y))
    {
      EvdevDevice* device = get_device(device_filename);
      return device->create_scroller(parent, x, y);
    }
  else
    {
      std::cout << "Error: Some of 'device', 'x', 'y' missing" << std::endl;
      return 0;
    }
}

Pointer*
EvdevDriver::create_pointer(const FileReader& reader, Control* parent)
{
  return 0;
}

Keyboard*
EvdevDriver::create_keyboard(const FileReader& reader, Control* parent)
{
  return 0;
}

} // namespace Input

/* EOF */
