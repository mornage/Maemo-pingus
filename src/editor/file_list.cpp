//  $Id: file_list.cpp 3169 2007-09-17 16:05:41Z grumbel $
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
#include "math.hpp"
#include "fonts.hpp"
#include "file_list.hpp"
#include "gui_style.hpp"
#include "../math/vector2i.hpp"

namespace Editor {

FileList::FileList(const Rect& rect)
  : RectComponent(rect),
    current_item(-1),
    click_item(-1),
    page(0),
    num_pages(0)
{
  update_layout();
}

void
FileList::update_layout() 
{
  hspace = rect.get_width()/2;
  vspace = 20;

  num_pages = directory.size() / items_per_page();
  if ((directory.size() % items_per_page()) != 0 || num_pages == 0)
    num_pages += 1;
  
  if (page >= num_pages)
    page = num_pages-1;
}

struct DirectorySorter
{
  bool operator()(const System::DirectoryEntry& lhs,
                  const System::DirectoryEntry& rhs)
  {
    if (lhs.type == rhs.type)
      {
        return lhs.name < rhs.name;
      }
    else
      {
        if (lhs.type == System::DE_DIRECTORY)
          return true;
        else
          return false;
      }
  }
};

void
FileList::set_directory(const std::string& pathname, const std::string& pattern)
{
  directory = System::opendir(pathname, pattern);
  std::sort(directory.begin(), directory.end(), DirectorySorter());

  num_pages = directory.size() / items_per_page();
  if ((directory.size() % items_per_page()) != 0 || num_pages == 0)
    num_pages += 1;

  page = 0;
}

void
FileList::draw(DrawingContext& gc)
{
  GUIStyle::draw_lowered_box(gc, rect, Color(255, 255, 255));

  int end = (page+1) * items_per_page();
  if (end > int(directory.size()))
    end = directory.size();

  int x = rect.left;
  int y = rect.top;
  for(System::Directory::iterator i = directory.begin() + page * items_per_page();
      i != directory.begin() + end; ++i)
    {
      if (i->type == System::DE_DIRECTORY)
        gc.draw(directory_icon, Vector2i(x, y));
      else if (i->type == System::DE_FILE)
        gc.draw(file_icon, Vector2i(x, y));

      if ((click_item == -1 && (i - directory.begin()) == current_item) ||
          (i - directory.begin()) == click_item)
        {
          if (click_item == current_item)
            gc.draw_fillrect(x, y, x + hspace, y + vspace, Color(0, 0, 255));
          else
            gc.draw_rect(x, y, x + hspace, y + vspace, Color(0, 0, 255));
        }
      
      gc.print_left(Fonts::verdana11, x + 4, y + 3,
                    ((i->type == System::DE_DIRECTORY) ? "[DIR]  " : "[FILE] ") + i->name);

      y += 20;
      if (y > rect.bottom - vspace)
        {
          y = rect.top;
          x += hspace;
        }
    }
}

void
FileList::on_primary_button_press (int x, int y)
{
  on_pointer_move(x,y);
  click_item = current_item;
}

void
FileList::on_primary_button_release (int x, int y)
{
  on_pointer_move(x,y);
  if (click_item == current_item && current_item != -1)
    {
      //std::cout << directory[current_item].name << std::endl;
      on_click(directory[current_item]);
    }
  click_item = -1;
}

void
FileList::on_pointer_move (int x, int y)
{
  x = x - rect.left;
  y = y - rect.top;

  current_item = Math::clamp(0, y / vspace, rect.get_height() / vspace - 1)
    + Math::clamp(0, x / hspace, rect.get_width() / hspace - 1) * (rect.get_height()/vspace);

  current_item += page * items_per_page();
  
  if (current_item < 0 || current_item >= int(directory.size()))
    current_item = -1;
}

void
FileList::next_page()
{
  page += 1;
  if (page >= num_pages)
    page = num_pages - 1;
}

void
FileList::prev_page()
{
  page -= 1;
  if (page < 0)
    page = 0;
}

void
FileList::update (float delta)
{
}

int
FileList::items_per_page()
{
  return (rect.get_height()/vspace * 2);
}

bool
FileList::has_more_next_pages()
{
  return (page < num_pages-1);
}

bool
FileList::has_more_prev_pages()
{
  return (page > 0);
}

} // namespace Editor

/* EOF */
