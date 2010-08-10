//  $Id: file_list.hpp 3111 2007-09-08 15:52:02Z grumbel $
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

#ifndef HEADER_FILE_LIST_HPP
#define HEADER_FILE_LIST_HPP

#include <boost/signal.hpp>
#include "system.hpp"
#include "sprite.hpp"
#include "gui/rect_component.hpp"

namespace Editor {

/** */
class FileList : public GUI::RectComponent
{
private:
  int hspace;
  int vspace;

  Sprite file_icon;
  Sprite directory_icon;
  System::Directory directory;
  int current_item;
  int click_item;
  int page;
  int num_pages;
  
public:
  FileList(const Rect& rect);

  void draw (DrawingContext& gc);
  void update (float delta);
  
  void update_layout();
  void set_directory(const std::string& pathname, const std::string& pattern = "*"); 

  void on_pointer_move (int x, int y);

  void on_primary_button_press (int x, int y);
  void on_primary_button_release (int x, int y);

  void next_page();
  void prev_page();

  bool has_more_next_pages();
  bool has_more_prev_pages();

  boost::signal<void (const System::DirectoryEntry&)> on_click;

private:
  int items_per_page();

  FileList (const FileList&);
  FileList& operator= (const FileList&);
};

} // namespace Editor

#endif

/* EOF */
