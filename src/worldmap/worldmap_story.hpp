//  $Id: worldmap_story.hpp 2986 2007-08-17 16:20:09Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_WORLDMAP_STORY_HXX
#define HEADER_PINGUS_WORLDMAP_STORY_HXX

#include <vector>
#include <string>
#include "../res_descriptor.hpp"

	
	class FileReader;

	class StoryPage
	{
	public:
		StoryPage() {}

		StoryPage(ResDescriptor arg_image, std::string arg_text, std::string arg_name = "")
			: image(arg_image), text(arg_text), page_name(arg_name)
		{
		
		}

		ResDescriptor image;
		std::string   text;
		std::string		page_name;
	};

namespace WorldMapNS {

	class WorldMapStory
	{
	public:
		WorldMapStory(const FileReader &reader);
		~WorldMapStory() { }

		std::string get_title() const { return title; }
		std::string get_music() const { return music; }
		std::vector<StoryPage> get_pages() const { return pages; }

	private:
		std::string title;
		std::string music;
		std::vector<StoryPage> pages;

	};	// class WorldMapStory

}	// namespace WorldmapNS

#endif

/*EOF*/
