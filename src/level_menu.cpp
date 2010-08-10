//  $Id: level_menu.cpp 3438 2007-10-31 13:39:31Z grumbel $
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

#include <boost/format.hpp>
#include "gettext.h"
#include "resource.hpp"
#include "screen/screen_manager.hpp"
#include "fonts.hpp"
#include "display/drawing_context.hpp"
#include "option_menu.hpp"
#include "system.hpp"
#include "display/display.hpp"
#include "level_menu.hpp"
#include "gui/rect_component.hpp"
#include "gui/gui_manager.hpp"
#include "game_session.hpp"
#include "start_screen.hpp"
#include "globals.hpp"
#include "gui/surface_button.hpp"
#include "sound/sound.hpp"

class LevelMenuAbortButton
  : public GUI::SurfaceButton
{
private:
  LevelMenu* parent;

public:
  LevelMenuAbortButton(LevelMenu* p)
    : GUI::SurfaceButton(Display::get_width()/2 - 300,
                         Display::get_height()/2 + 144,
                         ResDescriptor("core/start/back"),
                         ResDescriptor("core/start/back_clicked"),
                         ResDescriptor("core/start/back_hover")),
      parent(p)
  {
  }

  void draw(DrawingContext& gc) {
    SurfaceButton::draw(gc);
    gc.print_center(Fonts::chalk_normal, x_pos + 55, y_pos, _("Abort"));
  }

  void on_click() {
    parent->on_escape_press();
  }

  void on_pointer_enter()
  {
    SurfaceButton::on_pointer_enter();
    Sound::PingusSound::play_sound ("tick");
  }
};

class LevelsetSelector : public GUI::RectComponent
{
private:
  LevelMenu* level_menu;
  typedef std::vector<Levelset*> Levelsets;
  Levelsets levelsets;
  Levelset* current_levelset;
  Sprite marker;

public:
  LevelsetSelector(LevelMenu* level_menu_, const Rect& rect_) 
    : RectComponent(rect_),
      level_menu(level_menu_), current_levelset(NULL)
  {
    marker        = Resource::load_sprite("core/menu/marker");

    std::string path = Pathname("levelsets", Pathname::DATA_PATH).get_sys_path();
    System::Directory directory = System::opendir(path, "*.levelset");
    for(System::Directory::iterator i = directory.begin(); i != directory.end(); ++i)
      {
        levelsets.push_back(new Levelset(Pathname(path + "/" + i->name, Pathname::SYSTEM_PATH)));
      }
  }

  ~LevelsetSelector() 
  {
    for(Levelsets::iterator i = levelsets.begin(); i != levelsets.end(); ++i)
      {
        delete *i;
      }
  }
  
  void draw(DrawingContext& gc)
  {
    gc.push_modelview();
    gc.translate(static_cast<float>(rect.left), static_cast<float>(rect.top));

    gc.print_center(Fonts::chalk_large, rect.get_width()/2, -50, _("Levelsets"));

    //gc.draw_fillrect(Rect(Vector2i(0,0), Size(rect.get_width(), rect.get_height())),
    //                 Color(255, 255, 0, 100));

    int y = 0;
    for(Levelsets::iterator i = levelsets.begin(); i != levelsets.end(); ++i)
      {
        if (*i == current_levelset)
          gc.draw(marker, Vector2i(0, y - 5));

        gc.draw((*i)->get_image(), Vector2i(30, y));

        gc.print_left(Fonts::chalk_normal, 85+30, 15 + y, _((*i)->get_title()));
        gc.print_left(Fonts::chalk_small,  85+50, 40 + y, _((*i)->get_description()));

        gc.print_right(Fonts::chalk_normal, rect.get_width() - 30, 15 + y, (boost::format("%1% %2%%%") % _("Solved:") % (*i)->get_completion()).str());
        gc.print_right(Fonts::chalk_small,  rect.get_width() - 30, 60 + y, (boost::format("%1% %2%") % (*i)->get_level_count() % _("levels")).str());

        //gc.draw(ok_button, 620, y);

        y += 75;
      }
    gc.pop_modelview();
  }

  void on_pointer_move(int x, int y)
  {
    x -= rect.left;
    y -= rect.top;

    if (!levelsets.empty())
      {
        int i = y / 75;

        if (i >= 0 && i < static_cast<int>(levelsets.size()))
          current_levelset = levelsets[i];
        else
          current_levelset = NULL;
      }
  }

  void on_primary_button_press (int x, int y)
  {
    if (current_levelset)
      {
        level_menu->set_levelset(current_levelset);
      }
  }

  void update_layout() {}
};

class LevelSelector : public GUI::RectComponent
{
private:
  LevelMenu* level_menu;
  Sprite marker;
  Sprite marker_locked;
  Levelset* levelset;
  int current_level;
  
public:
  LevelSelector(LevelMenu* level_menu_, const Rect& rect_) 
    : RectComponent(rect_),
      level_menu(level_menu_),
      levelset(0),
      current_level(-1)
  {
    marker        = Resource::load_sprite("core/menu/marker2");
    marker_locked = Resource::load_sprite("core/menu/marker_locked");
  }

  void draw(DrawingContext& gc) 
  {
    gc.push_modelview();
    gc.translate(static_cast<float>(rect.left), static_cast<float>(rect.top));

    gc.print_center(Fonts::chalk_large, rect.get_width()/2, -70, _(levelset->get_title()));

    if (levelset)
      {
        levelset->refresh(); // should be better placed in on_startup() or so
        
        //gc.draw_fillrect(Rect(Vector2i(0,0), Size(rect.get_width(), rect.get_height())),
        //                 Color(255, 255, 0, 100));

        gc.print_left(Fonts::chalk_normal,  30, -32, _("Title"));
        gc.print_right(Fonts::chalk_normal, rect.get_width() - 30, - 32, _("Status"));

        int y = 0;
        for(int i = 0; i < levelset->get_level_count(); ++i)
          {
            if (!levelset->get_level(i)->accessible)
              gc.draw(marker_locked, Vector2i(0, y));
            else if (i == current_level)
              gc.draw(marker, Vector2i(0, y));
                        
            if (maintainer_mode)
              gc.print_left(Fonts::chalk_small, 30, y+4, levelset->get_level(i)->plf.get_resname());
            else
              gc.print_left(Fonts::chalk_small, 30, y+4, _(levelset->get_level(i)->plf.get_levelname()));

            if (levelset->get_level(i)->finished)
              gc.print_right(Fonts::chalk_small, rect.get_width() -30, y+4, _("solved"));
            else
              gc.print_right(Fonts::chalk_small, rect.get_width() -30, y+4, _("unsolved"));

            y += 32;
          }
      }
    
    gc.pop_modelview();
  }

  void set_levelset(Levelset* levelset_)
  {
    levelset = levelset_;
  }

  void on_pointer_move(int x, int y)
  {
    x -= rect.left;
    y -= rect.top;

    current_level = y / 32;
    
    if (current_level < 0 || current_level >= levelset->get_level_count())
      current_level = -1;
  }

  void on_primary_button_press (int x, int y)
  {
    if (current_level != -1)
      {
        if (levelset->get_level(current_level)->accessible)
          {
            ScreenManager::instance()->push_screen(new StartScreen(levelset->get_level(current_level)->plf), true);
          }
      }
  }

  void update_layout() {}
};

LevelMenu::LevelMenu()
  : x_pos((Display::get_width()  - 800)/2),
    y_pos((Display::get_height() - 600)/2)
{
  //background = Resource::load_sprite("core/menu/filedialog");
  background = Resource::load_sprite("core/menu/startscreenbg");
  background.scale(Display::get_width(), Display::get_height());

  ok_button  = Resource::load_sprite("core/start/ok");

  levelset_selector = new LevelsetSelector(this, Rect(Vector2i(x_pos + 100, y_pos + 140), Size(600, 300)));
  level_selector    = new LevelSelector(this, Rect(Vector2i(x_pos + 100, y_pos + 160), Size(600, 300)));

  gui_manager->add(levelset_selector, true);
  gui_manager->add(level_selector,    true);
  gui_manager->add(new LevelMenuAbortButton(this), true);

  level_selector->hide();
}

LevelMenu::~LevelMenu()
{
}

void
LevelMenu::draw_background(DrawingContext& gc)
{
  gc.draw(background, Vector2i(gc.get_width()/2, gc.get_height()/2));
  SDL_Delay(10);
}

void
LevelMenu::on_escape_press()
{
  if (level_selector->is_visible())
    {
      levelset_selector->show();
      level_selector->hide();           
    }
  else
    {
      //std::cout << "OptionMenu: poping screen" << std::endl;
      ScreenManager::instance()->pop_screen();
    }
}

void
LevelMenu::set_levelset(Levelset* levelset)
{
  if (levelset)
    {
      level_selector->set_levelset(levelset);
      levelset_selector->hide();
      level_selector->show();
    }
  else
    {
      levelset_selector->show();
      level_selector->hide();      
    }
}

/* EOF */
