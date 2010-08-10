//  $Id: savegame_manager.cpp 3351 2007-10-28 07:51:14Z grumbel $
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

#include <assert.h>
#include <fstream>
#include "system.hpp"
#include "pingus_error.hpp"
#include "sexpr_file_reader.hpp"
#include "sexpr_file_writer.hpp"
#include "savegame_manager.hpp"
#include "lisp/lisp.hpp"
#include "lisp/parser.hpp"

SavegameManager* SavegameManager::instance_ = 0;

SavegameManager*
SavegameManager::instance()
{
  if (instance_)
    return instance_;
  else
    return (instance_ = new SavegameManager("savegames/savegames.scm"));
}

void SavegameManager::deinit()
{
  delete instance_;
  instance_ = 0;
}

SavegameManager::SavegameManager(const std::string& arg_filename)
  : filename(System::get_statdir() + arg_filename)
{
  boost::shared_ptr<lisp::Lisp> sexpr;

  try 
    {
      sexpr = lisp::Parser::parse(filename);
    }
  catch (const std::runtime_error& e) 
    {
      std::cerr << "SavegameManager: " << e.what() << std::endl;
      return;
    }

  if (!sexpr)
    {
      std::cerr << "SavegameManager: Couldn't find savegame file '" <<
        filename << "', starting with an empty one." << std::endl;
      return;
    }

  SExprFileReader reader(sexpr->get_list_elem(0));
  if (reader.get_name() != "pingus-savegame")
    {
      std::cerr << "Error: " << filename << ": not a (pingus-savegame) file" << std::endl;
      return;
    }

  const std::vector<FileReader>& sections = reader.get_sections();
  for(std::vector<FileReader>::const_iterator i = sections.begin();
      i != sections.end(); ++i)
    {
      Savegame* savegame = new Savegame(*i);
      SavegameTable::iterator j = find(savegame->get_filename());
      if (j != savegames.end())
        { // overwrite duplicates, shouldn't happen, but harmless
          std::cout << "SavegameManager: name collision: " << savegame->get_filename() << std::endl;
          delete *j;
          *j = savegame;
        }
      else
        {
          savegames.push_back(savegame);
        }
    }
}

SavegameManager::~SavegameManager()
{
  for (SavegameTable::iterator i =  savegames.begin(); i !=  savegames.end (); ++i)
    delete *i;
}

Savegame*
SavegameManager::get(const std::string& filename)
{
  SavegameTable::iterator i = find(filename);
  if (i == savegames.end())
    return 0;
  else
    return *i;
}

void
SavegameManager::store(Savegame& arg_savegame)
{
  Savegame* savegame = new Savegame(arg_savegame);
  SavegameTable::iterator i = find(savegame->get_filename());
  if (i == savegames.end())
    { // don't know anything about the savegame
      savegames.push_back(savegame);
    }
  else
    { // already have such a savegame
      if ((*i)->get_status() == Savegame::FINISHED
          && savegame->get_status() == Savegame::ACCESSIBLE)
        { // saved savegame is better then new game
          delete savegame;
        }
      else
        { // new game is better or equal, save it
          delete *i;
          *i = savegame;
        }
    }

  flush();
}

SavegameManager::SavegameTable::iterator
SavegameManager::find(const std::string& filename)
{
  //std::cout << "SavegameManager::find: \"" << filename << "\"" << std::endl;

  for(SavegameTable::iterator i = savegames.begin();
      i != savegames.end(); ++i)
    if ((*i)->get_filename() == filename)
      return i;

  return savegames.end();
}

void
SavegameManager::flush()
{
  std::ofstream out(filename.c_str());
  SExprFileWriter writer(out);

  writer.begin_section("pingus-savegame");

  for(SavegameTable::iterator i = savegames.begin(); i != savegames.end(); ++i)
    {
      (*i)->write_sexpr(writer);
    }

  writer.end_section();	// pingus-savegame
}


/* EOF */
