//  $Id: sound_impl.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_SOUND_IMPL_HXX
#define HEADER_PINGUS_SOUND_IMPL_HXX

#include "../pingus.hpp"

namespace Sound {

class PingusSoundImpl
{
public:
	PingusSoundImpl () { };
	virtual ~PingusSoundImpl () { };

	/** Load a music file and play it immediately.
    @param filename The complete filename
    @param volume   The volume to play the music with  */
  virtual void real_play_music(const std::string & filename, float volume, bool loop) = 0;

	/** Stops playing any music file */
  virtual void real_stop_music() = 0;

	/** Load a sound file and play it immediately
    @param filename The complete filename
    @param volume   The volume to play the sound at
    @param panning  The panning to play the sound with */
  virtual void real_play_sound(const std::string & filename, 
															 float volume, float panning) = 0;
}; // class PingusSoundImpl

}  // namespace Sound

#endif
