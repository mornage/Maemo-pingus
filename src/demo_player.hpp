//  $Id: demo_player.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_DEMO_PLAYER_HXX
#define HEADER_PINGUS_DEMO_PLAYER_HXX

#include <vector>
#include "server_event.hpp"


class Server;
class XMLPDF;

class DemoPlayer
{
private:
  Server* server;
  std::vector<ServerEvent> events;

public:
  DemoPlayer(Server* s, XMLPDF* pdf);
  ~DemoPlayer();

  void update();

private:
  DemoPlayer (const DemoPlayer&);
  DemoPlayer& operator= (const DemoPlayer&);
};


#endif

/* EOF */
