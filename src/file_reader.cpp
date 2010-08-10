//  $Id: file_reader.cpp 3090 2007-09-05 19:08:47Z grumbel $
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

#include "sexpr_file_reader.hpp"
#include "lisp/parser.hpp"
#include "lisp/lisp.hpp"
#include "pathname.hpp"
#include "file_reader.hpp"
#include "file_reader_impl.hpp"

FileReader::FileReader(boost::shared_ptr<FileReaderImpl> impl_)
  : impl(impl_)
{
}

FileReader::FileReader()
{
}

std::string
FileReader::get_name() const
{
  if (impl.get())
    return impl->get_name();
  else
    return "";
}

bool
FileReader::read_int(const char* name, int& value) const
{
  if (impl.get())
    return impl->read_int(name, value);
  else
    return false;
}

bool
FileReader::read_float (const char* name, float& value) const
{
  if (impl.get())
    return impl->read_float(name, value);
  else
    return false;
}

bool
FileReader::read_bool  (const char* name, bool& value) const
{
  if (impl.get())
    return impl->read_bool(name, value);
  else
    return false;
}

bool
FileReader::read_string(const char* name, std::string& value) const
{
  if (impl.get())
    return impl->read_string(name, value);
  else
    return false;
}

bool
FileReader::read_path(const char* name, Pathname& value) const
{
  if (impl.get())
    {
      std::string filename;
      if (impl->read_string(name, filename))
        {
          value = Pathname(filename, Pathname::DATA_PATH);
          return true;
        }
      else
        {
          return false;
        }
    }
  else
    return false;
}

bool
FileReader::read_vector(const char* name, Vector3f& value) const
{
  if (impl.get())
    return impl->read_vector(name, value);
  else
    return false;
}

bool
FileReader::read_color(const char* name, Color& value) const
{
  if (impl.get())
    return impl->read_color(name, value);
  else
    return false;
}

bool
FileReader::read_desc(const char* name, ResDescriptor& desc) const
{
  if (impl.get())
    return impl->read_desc(name, desc);
  else
    return false;
}

bool
FileReader::read_size  (const char* name, Size& value) const
{
  if (impl.get())
    return impl->read_size(name, value);
  else
    return false;
}

bool
FileReader::read_vector2i(const char* name, Vector2i& value) const
{
  if (impl.get())
    return impl->read_vector2i(name, value);
  else
    return false;
}

bool
FileReader::read_section(const char* name, FileReader& reader) const
{
  if (impl.get())
    return impl->read_section(name, reader);
  else
    return false;
}

std::vector<std::string>
FileReader::get_section_names() const
{
  if (impl.get())
    return impl->get_section_names();
  else
    return std::vector<std::string>();
}

std::vector<FileReader>
FileReader::get_sections() const
{
  if (impl.get())
    return impl->get_sections();
  else
    return std::vector<FileReader>();
}

int
FileReader::get_num_sections() const
{
  return int(impl->get_sections().size());
}

FileReader
FileReader::read_section(const char* name)   const
{
  FileReader reader;
  read_section(name, reader);
  return reader;
}

FileReader
FileReader::parse(const std::string& filename)
{
  boost::shared_ptr<lisp::Lisp> sexpr = lisp::Parser::parse(filename);
  if (sexpr)
    {
      return SExprFileReader(sexpr->get_list_elem(0));
    }
  else
    {
      return FileReader();
    }
}

FileReader
FileReader::parse(const Pathname& pathname)
{
  boost::shared_ptr<lisp::Lisp> sexpr = lisp::Parser::parse(pathname.get_sys_path());
  if (sexpr)
    {
      return SExprFileReader(sexpr->get_list_elem(0));
    }
  else
    {
      return FileReader();
    }  
}

/* EOF */
