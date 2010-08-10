//  $Id: file_reader.hpp 3090 2007-09-05 19:08:47Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_FILE_READER_HXX
#define HEADER_PINGUS_FILE_READER_HXX

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class Size;
class Color;
class Vector3f;
class Vector2i;

class ResDescriptor;
class FileReaderImpl;
class Pathname;

/** Interface to read name/value pairs out of some kind of file or
    structure */
class FileReader
{
public:
  FileReader(boost::shared_ptr<FileReaderImpl> impl_);
  FileReader();

  /** Name of the current section, ie. in the case of
      <groundpiece><pos>...</groundpiece> it would be 'groundpiece' */
  std::string get_name() const;

  bool read_int   (const char* name, int&)           const;
  bool read_float (const char* name, float&)         const;
  bool read_bool  (const char* name, bool&)          const;
  bool read_string(const char* name, std::string&)   const;
  bool read_path  (const char* name, Pathname&)      const;
  bool read_vector(const char* name, Vector3f&)      const;
  bool read_vector2i(const char* name, Vector2i&)    const;
  bool read_size  (const char* name, Size&)          const;
  bool read_color (const char* name, Color&)         const;
  bool read_desc  (const char* name, ResDescriptor&) const;
  bool read_section(const char* name, FileReader&)   const;
  FileReader read_section(const char* name)   const;

  template<class E, class T>
  bool read_enum  (const char* name, E& value, T enum2string) const
  {
    std::string str;
    if (read_string(name, str))
      {
        value = enum2string(str);
        return true;
      }

    return false;
  }

  std::vector<std::string> get_section_names() const;
  std::vector<FileReader>  get_sections() const;
  int  get_num_sections() const;

  static FileReader parse(const std::string& filename);
  static FileReader parse(const Pathname& pathname);
private:
  boost::shared_ptr<FileReaderImpl> impl;
};

#endif

/* EOF */
