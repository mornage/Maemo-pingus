//  $Id: credits.cpp 3265 2007-09-30 16:07:08Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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
#include "screen/screen_manager.hpp"
#include "gui/surface_button.hpp"
#include "gui/gui_manager.hpp"
#include "sound/sound.hpp"
#include "stat_manager.hpp"
#include "resource.hpp"
#include "res_descriptor.hpp"
#include "credits.hpp"
#include "fonts.hpp"
#include "gettext.h"
#include "display/display.hpp"
#include "blitter.hpp"

class CreditsOkButton
  : public GUI::SurfaceButton
{
private:
  Credits* parent;
public:
  CreditsOkButton(Credits* p)
    : GUI::SurfaceButton(Display::get_width()/2 + 225,
                         Display::get_height()/2 + 125,
                         ResDescriptor("core/start/ok"),
                         ResDescriptor("core/start/ok_clicked"),
                         ResDescriptor("core/start/ok_hover")),
      parent(p)
  {
  }

  void on_pointer_enter ()
  {
    SurfaceButton::on_pointer_enter();
    Sound::PingusSound::play_sound("tick");
  }

  void on_click() {
    parent->on_escape_press();
    Sound::PingusSound::play_sound("yipee");
  }
};

Credits* Credits::instance_ = 0;

Credits::Credits()
{
  scene_context = new SceneContext();
  fast_scrolling = false;
  background = Resource::load_sprite("core/menu/startscreenbg");
  background.scale(Display::get_width(), Display::get_height());
  pingu = Resource::load_sprite("core/misc/creditpingu");

  gui_manager->add(new CreditsOkButton(this), true);

  font       = Fonts::chalk_normal;
  font_small = Fonts::chalk_large;

  // The credits vector holds the strings to display. The first
  // character of each string is a special character, which indicates
  // the size of the font or other special stuff. "-" means large
  // font, "_" is a small font and "n" means a newline.

  credits.push_back(_("-Idea"));
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("n");

  credits.push_back(_("-Maintaining"));
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("n");

  credits.push_back(_("-Programming"));
  credits.push_back("_David Philippi");
  credits.push_back("_Gervase Lam");
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("_Jason Green");
  credits.push_back("_Jimmy Salmon");
  credits.push_back("_Michael Ploujnikov");
  credits.push_back("_Nehal Mistry");
  credits.push_back("n");

  credits.push_back(_("-Porting (Win32)"));
  credits.push_back("_Alberto Curro");
  credits.push_back("_Bj�rn Christoph Fischer");
  credits.push_back("_Kenneth Gangst�");
  credits.push_back("_Michael K�ser");
  credits.push_back("_Neil Mitchell");
  credits.push_back("_Jason Green");
  credits.push_back("n");

  credits.push_back(_("-Porting (MacOSX)"));
  credits.push_back("_Jason Green");
  credits.push_back("_Sean Heber");
  credits.push_back("n");

  credits.push_back(_("-Gfx"));
  credits.push_back("_Alan Tennent");
  credits.push_back("_Craig Timpany");
  credits.push_back("_Erik S�e S�rensen");
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("_Jarno Elonen");
  credits.push_back("_Joel Fauche");
  credits.push_back("_Mark Collinson");
  credits.push_back("_Michael Mestre");
  credits.push_back("_Stefan Stiasny");
  credits.push_back("_Tom Flavel");
  credits.push_back("n");

  credits.push_back(_("-Music"));
  credits.push_back("_H. Matthew Smith");
  credits.push_back("_Joseph Toscano");
  credits.push_back("_Robbie Ferguson");
  credits.push_back("_Yuri Sucupira");
  credits.push_back("n");

  credits.push_back(_("-Level Design"));
  credits.push_back("_Craig Timpany");
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("_Rune Zedeler");
  credits.push_back("n");

  credits.push_back(_("-Story"));
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("n");

  credits.push_back(_("-Translation"));
  credits.push_back("_Cagri Coltekin");
  credits.push_back("_David Philippi");
  credits.push_back("_Giray Devlet");
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("_Janne Mor�n");
  credits.push_back("_Jarno Elonen");
  credits.push_back("_Karl Ove Hufthammer");
  credits.push_back("_Milan Babuskov");
  credits.push_back("_Philippe Saint-Pierre");
  credits.push_back("_Ricardo Cruz");
  credits.push_back("_Skule Solvang");
  credits.push_back("_Tomas Blaha");
  credits.push_back("n");

  credits.push_back(_("-Special"));
  credits.push_back(_("-Thanks to"));
  credits.push_back("_Adam Gregory");
  credits.push_back("_Andy Balaam");
  credits.push_back("_Bernhard Trummer");
  credits.push_back("_Cagri Coltekin");
  credits.push_back("_David Fauthoux");
  credits.push_back("_David Flores");
  credits.push_back("_David M. Turner");
  credits.push_back("_Debian");
  credits.push_back("_Etienne Marcotte");
  credits.push_back("_Felix Natter");
  credits.push_back("_Francisco 'Pacho' Ramos");
  credits.push_back("_Giray Devlet ");
  credits.push_back("_Giuseppe D'Aqui");
  credits.push_back("_Henri Manson");
  credits.push_back("_Jeff Binder");
  credits.push_back("_Jens Henrik Goebbert");
  credits.push_back("_Jessica Philippi");
  credits.push_back("_John August");
  credits.push_back("_Johnny Taporg");
  credits.push_back("_Jules Bean");
  credits.push_back("_Keir Fraser");
  credits.push_back("_Magnus Norddahl");
  credits.push_back("_Mattias Andersson");
  credits.push_back("_Michael Wand");
  credits.push_back("_Peter Todd");
  credits.push_back("_Peter van Rossum");
  credits.push_back("_Richard Stallman");
  credits.push_back("_Rob Gietema");
  credits.push_back("_Robert Wittams");
  credits.push_back("_Robin Hogan");
  credits.push_back("_Shigeru Miyamoto");
  credits.push_back("_Stefan Ruhnke");
  credits.push_back("_SuSE");
  credits.push_back("_Till Hellweg");
  credits.push_back("_Tim Yamin");
  credits.push_back("_Tuomas (Tigert) Kuosmanen");
  credits.push_back("_Werner Steiner");
  credits.push_back("n");
  credits.push_back("n");
  credits.push_back("n");
  credits.push_back("n");
  credits.push_back("n");

  credits.push_back(_("_And a very Special Thanks"));
  credits.push_back(_("_to all the people who"));
  credits.push_back(_("_contribute to"));
  credits.push_back(_("_Free Software!"));
  credits.push_back("n");
  credits.push_back("n");
  credits.push_back("n");
  credits.push_back("n");
  credits.push_back("n");
  credits.push_back(_("_Thank you for"));
  credits.push_back(_("_playing!"));

  end_offset = -(float)Display::get_height()/2 - 50; // screen height + grace time
  for (std::vector<std::string>::iterator i = credits.begin(); i != credits.end(); ++i)
    {
      switch ((*i)[0])
	{
	case '-':
	  end_offset += font.get_height() + 5;
	  break;
	case '_':
	  end_offset += font_small.get_height() + 5;
	  break;
	case 'n':
	  end_offset += 50;
	  break;
	default:
	  std::cout << "Credits: Syntax error: Unknown format: '" << (*i)[0] << "'" << std::endl;
	  break;
	}
    }
  end_offset = -end_offset;
}

Credits::~Credits ()
{
  StatManager::instance()->set_bool("credits-seen", true);
  delete scene_context;
}

void
Credits::update (float delta)
{
  if (offset < end_offset)
    {
      //ScreenManager::instance()->pop_screen ();
    }
  else
    {
      if (fast_scrolling)
        offset -= 450.0f * delta;
      else
        offset -= 35.0f * delta;
    }
}

void
Credits::draw_background (DrawingContext& gc)
{
  int x;
  int y;
  int yof;

  x = Display::get_width()/2;
  y = (int)offset;

  gc.draw(background, Vector2i(gc.get_width()/2, gc.get_height()/2));
  gc.draw(pingu, Vector2i(gc.get_width()/2, gc.get_height()/2 - 20));
  
  gc.print_right(Fonts::chalk_normal,
                Display::get_width()/2 + 275,
                Display::get_height()/2 + 110,
                _("Exit"));
  
  yof = 0;

  scene_context->clear();
  scene_context->set_cliprect(Rect(0,
                                   static_cast<int>(0.125f * gc.get_height()),
                                   static_cast<int>(gc.get_width()),
                                   static_cast<int>(0.833f * gc.get_height())));
  for (std::vector<std::string>::iterator i = credits.begin(); i != credits.end(); ++i)
    {
      switch ((*i)[0])
	{
	case '-':
	  scene_context->color().print_center(font, x, (y + yof), i->substr(1));
	  yof += font.get_height() + 5;
	  break;
	case '_':
	  scene_context->color().print_center(font_small, x, (y + yof), i->substr(1));
	  yof += font_small.get_height() + 5;
	  break;
	case 'n':
	  yof += 50;
	  break;
	default:
	  std::cout << "Credits: Syntax error: Unknown format: '" << (*i)[0] << "'" << std::endl;
	  break;
	}
    }
  gc.draw(new SceneContextDrawingRequest(scene_context, Vector3f(0,0,100)));
}

void
Credits::on_startup ()
{
  offset = (float)Display::get_height() - 50;
  //PingusSound::play_music("pingus-5.it");
}

Credits*
Credits::instance ()
{
  if (instance_)
    return instance_;
  else
    return instance_ = new Credits ();
}

void
Credits::init()
{
  instance_ = 0;
}

void
Credits::deinit()
{
  delete instance_;
  instance_ = 0;
}

void
Credits::on_pause_press ()
{
}

void
Credits::on_fast_forward_press ()
{
  fast_scrolling = ! fast_scrolling;
}

void
Credits::on_escape_press ()
{
  ScreenManager::instance ()->pop_screen ();
}

/* EOF */
