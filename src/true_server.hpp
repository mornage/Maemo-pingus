//  $Id: true_server.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_TRUE_SERVER_HXX
#define HEADER_PINGUS_TRUE_SERVER_HXX

#include "pingus_level.hpp"
#include "server.hpp"


/** FIXME: This whole Server/Client concept is screwed and the
    TrueServer/Server thing even more... */
class TrueServer : public Server
{
private:
  bool fast_forward;
  bool pause;

public:
  TrueServer(const PingusLevel& plf);
  virtual ~TrueServer();

  void update();

  void set_fast_forward(bool value);
  bool get_fast_forward();

  void set_pause(bool);
  bool get_pause();

  /** set the server into the finshed state, this is used when you
      press ESCAPE inside a game */
  void set_finished();

private:
  TrueServer (const TrueServer&);
  TrueServer& operator= (const TrueServer&);
};


#endif

/* EOF */
