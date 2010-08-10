//  $Id: pingus_main.hpp 3231 2007-09-22 15:46:31Z grumbel $
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

#ifndef HEADER_PINGUS_PINGUS_MAIN_HXX
#define HEADER_PINGUS_PINGUS_MAIN_HXX

#include <string>
#include "pingus.hpp"
#include "SDL.h"
#include "pingus_options.hpp"
#include "pathname.hpp"

void segfault_handler(int);

class PingusMain
{
private:
  PingusOptions cmd_options;

public:
  PingusMain();
  virtual ~PingusMain();

  virtual int main(int argc, char** argv);

  void on_exit_press();
private:
  /** After all subsystems have been inited, the screen will get
      setup, the game (the menu or a level, depending on
      command line flags) will start and the user will get
      controll. */
  void start_game();

  void parse_args(int argc, char** argv);
  void apply_args();
  void read_rc_file(void);

  void print_greeting_message();

  void init_sdl();
  void deinit_sdl();

  void init_pingus();
  void init_path_finder();
  void deinit_pingus();

  PingusMain (const PingusMain&);
  PingusMain& operator= (const PingusMain&);

} app; // golbal class instance


#endif

/* EOF */
