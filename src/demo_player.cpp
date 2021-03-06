//  $Id: demo_player.cpp 2986 2007-08-17 16:20:09Z grumbel $
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

#include <iostream>
#include "server.hpp"
#include "demo_player.hpp"
#include "xml_pdf.hpp"


DemoPlayer::DemoPlayer(Server* s, XMLPDF* pdf)
  : server(s),
    events(pdf->get_events())
{
}

DemoPlayer::~DemoPlayer()
{
}

void
DemoPlayer::update()
{
  while(!events.empty() && events.back().time_stamp == server->get_time())
    {
      ServerEvent& event = events.back();

      std::cout << "Sending: ";
      event.write_xml(std::cout);

      event.send(server);
      events.pop_back();
    }

  // Check for unexpected things (might happen if the demo file is broken)
  if (!events.empty() && events.back().time_stamp < server->get_time())
    {
      std::cout << "DemoPlayer Bug: We missed a timestamp: " << events.back().time_stamp << std::endl;
    }
}


/* EOF */
