//  $Id: resource_manager.cpp 3166 2007-09-16 15:29:14Z grumbel $
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

#include <iostream>
#include "debug.hpp"
#include "globals.hpp"
#include "lisp/lisp.hpp"
#include "lisp/parser.hpp"
#include "string_util.hpp"
#include "sprite_description.hpp"
#include "sexpr_file_reader.hpp"
#include "resource_manager.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
  std::map<std::string, SpriteDescription*>::iterator i;
  for (i = resources.begin(); i != resources.end(); ++i) {
    delete (*i).second;
  }
}

std::vector<std::string>
ResourceManager::get_section(const std::string& name)
{
  std::vector<std::string> lst;
  for (std::map<std::string, SpriteDescription*>::iterator i = resources.begin();
       i != resources.end(); ++i) 
    {
      if (StringUtil::has_prefix(i->first, name))
        lst.push_back(i->first);
    }
  return lst;
}

void
ResourceManager::add_resources(const std::string& filename)
{
  pout(PINGUS_DEBUG_RESOURCES) << "ResourceManager: " << filename << std::endl;
  boost::shared_ptr<lisp::Lisp> sexpr = lisp::Parser::parse(filename);
  if (sexpr)
    {
      SExprFileReader reader(sexpr->get_list_elem(0));

      if (reader.get_name() == "pingus-resources")
        {
          std::vector<FileReader> sections = reader.get_sections();
          for(std::vector<FileReader>::iterator i = sections.begin(); i != sections.end(); ++i)
            {
              //std::cout << "Section: " << i->get_name() << std::endl;
              parse("", *i);
            }
        }
      else
        {
          std::cout << "Couldn't find section 'pingus-resources' section in file " << filename
                    << "\ngot " << reader.get_name()
                    << std::endl;
        }
    }
  else
    {
      std::cout << "ResourceManager: File not found " << filename << std::endl;
    }
}

void
ResourceManager::parse(const std::string& section, FileReader& reader)
{
  if (reader.get_name() == "section")
    {
      parse_section(section, reader);
    }
  else if (reader.get_name() == "sprite")
    {
      std::string name;
      reader.read_string("name", name);
      if (!section.empty())
        name = section + "/" + name;
 
      if (resources[name])
	delete resources[name];
      resources[name] = new SpriteDescription(reader);
    }
  else if (reader.get_name() == "alias")
    {
      std::string name;
      std::string link;
      reader.read_string("name", name);
      reader.read_string("link", link);
      //std::cout << "alias: " << name << " -> " << link << std::endl;
    }
  else if (reader.get_name() == "name")
    {
      // ignore (ugly)
    }
  else
    {
      std::cout << "ResourceManager: unknown token: '" << reader.get_name() << "'" << std::endl;
    }
}

void
ResourceManager::parse_section(const std::string& section, FileReader& reader)
{
  std::string name;
  reader.read_string("name", name);

  std::vector<FileReader> sections = reader.get_sections();
  for(std::vector<FileReader>::iterator i = sections.begin(); i != sections.end(); ++i)
    {    
      if (section.empty())
        parse(name, *i);
      else
        parse(section + "/" + name, *i);
    }
}

SpriteDescription* 
ResourceManager::get_sprite_description(const std::string& name) const
{
  Resources::const_iterator i = resources.find(name);
  if (i != resources.end())
    {
      return i->second;
    }
  else
    {
      return 0;
    }  
}

/* EOF */
