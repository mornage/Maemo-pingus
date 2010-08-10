//  $Id: debug_stream.hpp 2986 2007-08-17 16:20:09Z grumbel $
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

#ifndef HEADER_PINGUS_DEBUG_STREAM_HXX
#define HEADER_PINGUS_DEBUG_STREAM_HXX

#include "pingus.hpp"
#include <string>
#include <vector>
#include <iostream>


class NilStream;

class DebugStream : public std::ostream
{

private:

  class Buffer : public std::streambuf
  {
  private:

    enum { buffersize = 1024 };

    std::vector<std::ostream*> out_streams;

    char char_buffer[buffersize];
    std::string prefix;

  public:

    Buffer (const std::string& prefix);
    virtual ~Buffer ();

    int overflow (int c);
    int sync ();

    void add (std::ostream& s);
    void set_prefix (const std::string & prefix_);

  private:

    void put_line (const std::string& line);

  } buffer;

  static NilStream nilstream;

public:

  DebugStream (const std::string& prefix);
  virtual ~DebugStream ();

  std::ostream & operator() (int component);

  void add (std::ostream& s);
  void set_prefix (const std::string & prefix);

private:
  DebugStream (const DebugStream&);
  DebugStream& operator= (const DebugStream&);
};



/// Stream used to consume unwanted debugmessages
class NilStream : public std::ostream
{
  private:

    /// Do nothing Buffer for NilStream
    class NilBuffer : public std::streambuf
    {
      private:

        char char_buffer[4];

      public:

         NilBuffer () { setp(char_buffer, char_buffer + 3); setg(0,0,0); }
        ~NilBuffer () { }

        int overflow (int) { return 0; }
        int sync     ()    { return 0; }
    } buffer;

   NilStream ();
   ~NilStream () { }

    NilStream (const NilStream &); ///< not supported

  public:

    // Avoid unneccessary calls to internal buffer and conversions
    NilStream & operator << (const char *)        { return *this; }
    NilStream & operator << (const std::string &) { return *this; }
    NilStream & operator << (int &)               { return *this; }
    NilStream & operator << (unsigned int &)      { return *this; }


  friend class DebugStream;
};


#endif

/* EOF */
