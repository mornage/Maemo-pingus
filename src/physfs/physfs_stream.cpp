/*
Copyright (C) 2005 Matthias Braun <matze@braunis.de>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include <config.h>

#include "physfs_stream.hpp"

#include <assert.h>
// #include <physfs.h>
#include <stdexcept>
#include <sstream>

IFileStreambuf::IFileStreambuf(const std::string& filename)
{
    file = PHYSFS_openRead(filename.c_str());
    if(file == 0) {
        std::stringstream msg;
        msg << "Couldn't open file '" << filename << "': "
            << PHYSFS_getLastError();
        throw std::runtime_error(msg.str());
    }
}

IFileStreambuf::~IFileStreambuf()
{
    PHYSFS_close(file);
}

int
IFileStreambuf::underflow()
{
    if(PHYSFS_eof(file)) {
        return traits_type::eof();
    }
   
    PHYSFS_sint64 bytesread = PHYSFS_read(file, buf, 1, sizeof(buf));
    if(bytesread <= 0) {
        return traits_type::eof();
    }
    setg(buf, buf, buf + bytesread);

    // without the conversation some characters (255?) would be
    // handled like EOF
    return traits_type::to_int_type(buf[0]);
}

IFileStreambuf::pos_type
IFileStreambuf::seekpos(pos_type pos, std::ios_base::openmode)
{
  if(PHYSFS_seek(file, static_cast<PHYSFS_uint64> (pos)) == 0) {
    return pos_type(off_type(-1));
  }

  // the seek invalidated the buffer
  setg(buf, buf, buf);
  return pos;
}

IFileStreambuf::pos_type
IFileStreambuf::seekoff(off_type off, std::ios_base::seekdir dir,
                        std::ios_base::openmode mode)
{
  off_type pos = off;
  PHYSFS_sint64 ptell = PHYSFS_tell(file);
  
  switch(dir) {
    case std::ios_base::beg:
      break;
    case std::ios_base::cur:
      if(off == 0)
		  return static_cast<pos_type> ((std::streamoff)ptell) - static_cast<pos_type> ((std::streamoff)(egptr() - gptr()));
      pos += static_cast<off_type> (ptell) - static_cast<off_type> (egptr() - gptr());
      break;
    case std::ios_base::end:
      pos += static_cast<off_type> (PHYSFS_fileLength(file));
      break;
    default:
#ifdef DEBUG
      assert(false);
#else
      return pos_type(off_type(-1));
#endif
  }

  return seekpos(static_cast<pos_type> (pos), mode);
}

//---------------------------------------------------------------------------

OFileStreambuf::OFileStreambuf(const std::string& filename)
{
    file = PHYSFS_openWrite(filename.c_str());
    if(file == 0) {
        std::stringstream msg;
        msg << "Couldn't open file '" << filename << "': "
            << PHYSFS_getLastError();
        throw std::runtime_error(msg.str());
    }
    
    setp(buf, buf+sizeof(buf));
}

OFileStreambuf::~OFileStreambuf()
{
    sync();
    PHYSFS_close(file);
}

int
OFileStreambuf::overflow(int c)
{
    if(pbase() == pptr())
        return 0;

    size_t size = pptr() - pbase();
    PHYSFS_sint64 res = PHYSFS_write(file, pbase(), 1, (PHYSFS_uint32)size);
    if(res <= 0)
        return traits_type::eof();
    
    if(c != traits_type::eof()) {
        PHYSFS_sint64 res = PHYSFS_write(file, &c, 1, 1);
        if(res <= 0)
            return traits_type::eof();
    }

    setp(buf, buf + res);
    return 0;
}

int
OFileStreambuf::sync()
{
    return overflow(traits_type::eof());
}

//---------------------------------------------------------------------------

IFileStream::IFileStream(const std::string& filename)
    : std::istream(0), streambuf(filename)
{
  rdbuf(&streambuf);
}

IFileStream::~IFileStream()
{
}

//---------------------------------------------------------------------------

OFileStream::OFileStream(const std::string& filename)
    : std::ostream(0), streambuf(filename)
{
  rdbuf(&streambuf);
}

OFileStream::~OFileStream()
{
}

