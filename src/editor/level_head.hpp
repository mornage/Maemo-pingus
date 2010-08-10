//  $Id: level_head.hpp 3075 2007-09-03 23:27:36Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Jason Green <jave27@gmail.com>,
//                     Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_EDITOR_LEVEL_HEAD_HXX
#define HEADER_PINGUS_EDITOR_LEVEL_HEAD_HXX

#include "../gui/component.hpp"


class Vector3f; 
  
namespace GUI {  
class GUIManager;
class InputBox; 
}

namespace Editor {

class LevelImpl;
class PanelButtonHead;
class EditorPanel;  
class LevelHeadCloseButton; 

/** This class draws a box with different input boxes that
 * determine the specific level information which is saved
 * in the <HEAD> section of the XML level file */ 
class LevelHead : public GUI::Component
{
private:
  /** The level we are editing */
  PanelButtonHead* head_button;
   
  LevelImpl *impl;
  
  GUI::GUIManager* gui_manager; 
  
  /** Where this box is drawn*/ 
  Vector3f pos;
  
  // Input boxes for each item of the level impl 
  GUI::InputBox* name;
  GUI::InputBox* desc;
  LevelHeadCloseButton* close_button; 
	
public:

  LevelHead(EditorPanel* p, PanelButtonHead* pbh);
  ~LevelHead();
	
  PanelButtonHead* get_head_button() { return head_button; }
   
  // GUI Component stuff
  bool is_at(int x, int y);
  void draw(DrawingContext& gc);
  void update(float delta); 
};

}	// Editor namespace

#endif

/* EOF */
