//  $Id: level_properties.cpp 3448 2007-11-01 08:37:49Z grumbel $
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
#include <boost/bind.hpp>
#include "string_util.hpp"
#include "label.hpp"
#include "inputbox.hpp"
#include "gui_style.hpp"
#include "editor_level.hpp"
#include "viewport.hpp"
#include "level_properties.hpp"

/*
Level Properties:
Levelname, Description, Author, 
Number of Pingus, Time, Pingus to Save,
Width, Height, (could be handled elsewhere)
Difficulty
Comment
Playable (unneeded)
*/

namespace Editor {

LevelProperties::LevelProperties(EditorScreen* editor_, const Rect& rect)
  : GroupComponent(rect),
    editor(editor_),
    level(0)
{
  int w = rect.get_width() - 120;
  add(new Label   (Rect(Vector2i( 10,  10), Size( 80, 20)), "Author:"), true);
  add(author = new Inputbox(Rect(Vector2i(110,  10), Size(  w, 20))), true);
  add(new Label   (Rect(Vector2i( 10,  32), Size( 80, 20)), "Levelname:"), true);
  add(levelname = new Inputbox(Rect(Vector2i(110,  32), Size(  w, 20))), true);
  add(new Label   (Rect(Vector2i( 10,  54), Size( 80, 20)), "Description:"), true);
  add(description = new Inputbox(Rect(Vector2i(110,  54), Size(  w, 20*3))), true);

  int y = 116;
  add(new Label   (Rect(Vector2i( 10,  y), Size( 80, 20)), "Pingus Count:"), true);
  add(number_of_pingus = new Inputbox(Rect(Vector2i(110,  y), Size(  w, 20))), true);
  add(new Label   (Rect(Vector2i( 10,  y+22), Size( 80, 20)), "Pingus to Save:"), true);
  add(number_to_save = new Inputbox(Rect(Vector2i(110,  y+22), Size(  w, 20))), true);

  add(new Label   (Rect(Vector2i( 10,  y+44), Size( 80, 20)), "Time:"), true);
  add(time = new Inputbox(Rect(Vector2i(110,  y+44), Size(  w, 20))), true);
  add(new Label   (Rect(Vector2i( 10,  y+66), Size( 80, 20)), "Width:"), true);
  add(width = new Inputbox(Rect(Vector2i(110,  y+66), Size(  w, 20))), true);
  add(new Label   (Rect(Vector2i( 10,  y+88), Size( 80, 20)), "Height:"), true);
  add(height = new Inputbox(Rect(Vector2i(110,  y+88), Size(  w, 20))), true);

  add(new Label   (Rect(Vector2i( 10, y+110), Size( 80, 20)), "Difficulty:"), true);
  add(difficulty = new Inputbox(Rect(Vector2i(110, y+110), Size(  w, 20))), true);
  add(new Label   (Rect(Vector2i( 10, y+132), Size( 80, 20)), "Comment:"), true);
  add(comment = new Inputbox(Rect(Vector2i(110, y+132), Size(  w, 20))), true);
  add(new Label   (Rect(Vector2i( 10, y+154), Size( 80, 20)), "Music:"), true);
  add(music = new Inputbox(Rect(Vector2i(110, y+154), Size(  w, 20))), true);

  author->on_change.connect(boost::bind(&LevelProperties::on_author_change, this, _1));
  levelname->on_change.connect(boost::bind(&LevelProperties::on_levelname_change, this, _1));
  description->on_change.connect(boost::bind(&LevelProperties::on_description_change, this, _1));

  number_to_save->on_change.connect(boost::bind(&LevelProperties::on_number_to_save_change, this, _1));
  number_of_pingus->on_change.connect(boost::bind(&LevelProperties::on_number_of_pingus_change, this, _1));

  width->on_change.connect(boost::bind(&LevelProperties::on_width_change, this, _1));
  height->on_change.connect(boost::bind(&LevelProperties::on_height_change, this, _1));
  time->on_change.connect(boost::bind(&LevelProperties::on_time_change, this, _1));
  difficulty->on_change.connect(boost::bind(&LevelProperties::on_difficulty_change, this, _1));
  comment->on_change.connect(boost::bind(&LevelProperties::on_comment_change, this, _1));
  music->on_change.connect(boost::bind(&LevelProperties::on_music_change, this, _1));
}

LevelProperties::~LevelProperties()
{
}

void
LevelProperties::draw_background(DrawingContext& gc)
{
  GUIStyle::draw_raised_box(gc, Rect(0,0,rect.get_width(), rect.get_height()));
}

void
LevelProperties::update(float delta)
{
}

void
LevelProperties::set_level(EditorLevel* level_)
{
  level = level_;
  description->set_text(level->get_description());
  levelname->set_text(level->get_levelname());
  author->set_text(level->get_author());

  number_of_pingus->set_text(StringUtil::to_string(level->get_number_of_pingus()));
  number_to_save->set_text(StringUtil::to_string(level->get_number_to_save()));

  time->set_text(StringUtil::to_string(level->get_time()));
  width->set_text(StringUtil::to_string(level->get_size().width));
  height->set_text(StringUtil::to_string(level->get_size().height));
  difficulty->set_text(StringUtil::to_string(level->get_difficulty()));
  comment->set_text(level->get_comment());
  music->set_text(level->get_music());
}

void
LevelProperties::on_author_change(const std::string& str)
{
  level->set_author(str);
}

void
LevelProperties::on_levelname_change(const std::string& str)
{
  level->set_levelname(str);
}

void
LevelProperties::on_description_change(const std::string& str)
{
  level->set_description(str);
}

void
LevelProperties::on_width_change(const std::string& str)
{
  Size s = level->get_size();
  level->set_size(Size(StringUtil::to<int>(str), s.height));
  editor->get_viewport()->refresh();
}

void
LevelProperties::on_height_change(const std::string& str)
{
  Size s = level->get_size();
  level->set_size(Size(s.width, StringUtil::to<int>(str)));
}

void
LevelProperties::on_number_to_save_change(const std::string& str)
{
  int num;
  if (StringUtil::from_string(str, num))
    {
      level->set_number_to_save(num);
    }
  else
    {
      std::cout << "LevelProperties::on_number_to_save_change: '" << str << "' not an integer" << std::endl;
    }
  
}

void
LevelProperties::on_number_of_pingus_change(const std::string& str)
{
  int num;
  if (StringUtil::from_string(str, num))
    {
      level->set_number_of_pingus(num);
    }
  else
    {
      std::cout << "LevelProperties::on_number_of_pingus_change: '" << str << "' not an integer" << std::endl;
    }
}

void
LevelProperties::on_time_change(const std::string& str)
{
  level->set_time(StringUtil::to<int>(str));
}

void
LevelProperties::on_difficulty_change(const std::string& str)
{
  level->set_difficulty(StringUtil::to<int>(str));
}

void
LevelProperties::on_comment_change(const std::string& str)
{
  level->set_comment(str);
}

void
LevelProperties::on_music_change(const std::string& str)
{ 
  level->set_music(str);
}

void
LevelProperties::update_layout()
{
  GroupComponent::update_layout();

  int w = rect.get_width() - 120; 
  author->set_rect(Rect(Vector2i(110,  10), Size(  w, 20)));
  levelname->set_rect(Rect(Vector2i(110,  32), Size(  w, 20)));
  description->set_rect(Rect(Vector2i(110,  54), Size(  w, 20*3)));
  
  int y = 116;
  number_of_pingus->set_rect(Rect(Vector2i(110,  y), Size(  w, 20)));
  number_to_save->set_rect(Rect(Vector2i(110,  y+22), Size(  w, 20))); 

  time->set_rect(Rect(Vector2i(110,  y+44), Size(  w, 20)));
  width->set_rect(Rect(Vector2i(110,  y+66), Size(  w, 20)));
  height->set_rect(Rect(Vector2i(110,  y+88), Size(  w, 20)));
  
  difficulty->set_rect(Rect(Vector2i(110, y+110), Size(  w, 20)));
  comment->set_rect(Rect(Vector2i(110, y+132), Size(  w, 20)));
  music->set_rect(Rect(Vector2i(110, y+154), Size(  w, 20)));
}

} // namespace Editor

/* EOF */
