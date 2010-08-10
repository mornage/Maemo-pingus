//  $Id: system.hpp 3340 2007-10-27 07:08:51Z grumbel $
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#ifndef HEADER_PINGUS_SYSTEM_HXX
#define HEADER_PINGUS_SYSTEM_HXX

#include "pingus.hpp"
#include <string>
#include <vector>
#include <map>
#include "SDL.h"


/** A wrapper class around some system dependend functions (mostly
    POSIX stuff) */
class System
{
private:
  static int verbose;
  static std::string default_email;
  static std::string default_username;

public:
  enum FileType { DE_DIRECTORY, DE_FILE };

  struct DirectoryEntry
  {
    FileType type;
    std::string name;

    DirectoryEntry(const std::string&, FileType t = DE_FILE);
  };

  ///
  typedef std::vector<DirectoryEntry> Directory;
  typedef Directory::iterator DirectoryIter;

  ///
  static Directory opendir(const std::string& pathname, const std::string& pattern = "*");

  /** Check if a file is avaiblable (no checking for permissens is currently performed)
      @param filename The name of the file
      @return True, if the file exist, false otherwise */
  static bool exist(std::string filename);

  /** Creates directory if it does not already exist.
      @param dir The name of the directory */
  static void create_dir(std::string dir);

  /** Change into the directory named dir, on error throw an PingusError */
  static void change_dir (std::string dir);

  /** Check if all needed directories are available, if not then create
      them. */
  static void init_directories();

  /** Strips directory from filenames
      @param filename The complete filename */
  static std::string basename(std::string filename);

  /** Strips basename from pathnames (see dirname(3))
      @param filename The complete filename */
  static std::string dirname(std::string filename);

  /** Return the extension of the given filename:

      System::extension ("foobar.jpg")    => "jpg"
      System::extension ("/bla/bla.blub/") => ""
      System::extension ("/bla/blabl") => ""
  */
  static std::string extension (std::string filename);
  static std::string cut_ext (std::string filename);

  /** Returns the directory where Pingus can store its user specific
      state and config data (savegames, config files, demos, etc.) */
  static std::string get_statdir();

  /** Returns the directory where Pingus can store things that needs
      to be cached, for example thumbnails */
  static std::string get_cachedir();

  /** Returns the directory were Pingus can store its system wide
      variable game data (highscores, cache images, ...) */
  static std::string get_vardir();

  /** Asks different variables to check were the directory for
      temporary files is located
      @return The location of the tmp directory */
  static std::string get_tmpdir();

  /** Returns the Username how the current user or an empty string */
  static std::string get_username();

  /** Returns the EMail of the user or an empty string */
  static std::string get_email();

  /** Get the currently country code, in a two letter ISO 639 syntax */
  static std::string get_language();

  /** Return the modification time of a file */
  static uint64_t get_mtime(const std::string& filename);

  /** Choose the correct translation out of the map, if there is none
      present, fall back to the default language */
  static std::string translate(const std::map<std::string, std::string>& strs);

  static std::string translate(const std::string& str);

  /** Translate to 'en' */
  static std::string translate_default(const std::map<std::string, std::string>& strs);

  /** Removes all .., double slashes and such from a pathname */
  static std::string realpath(const std::string& pathname);

  /** Read a file and generate a checksum and return it. The checksum
   generation is very primitiv and should probably be replaced by CRC
   or md5. */
  static std::string checksum (std::string filename);

private:
  System (const System&);
  System& operator= (const System&);
};


#endif

/* EOF */
