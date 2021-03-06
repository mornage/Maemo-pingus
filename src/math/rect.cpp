/*
**  ClanLib SDK
**  Copyright (c) 1997-2005 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
**    (if your name is missing here, please add it)
*/


#include <cmath>
#include <iostream>
#include "rect.hpp"

#define cl_min(a,b) ((a < b) ? a : b)
#define cl_max(a,b) ((a > b) ? a : b)

Rect Rect::get_rot_bounds(const Vector2i &hotspot, float angle) const
{
#if 0
	//Find the rotated positions of each corner
	Rect retVal(*this);
	Vector2i ul = Vector2i(retVal.left, retVal.top).rotate(hotspot, angle);
	Vector2i ur = Vector2i(retVal.right, retVal.top).rotate(hotspot, angle);
	Vector2i ll = Vector2i(retVal.left, retVal.bottom).rotate(hotspot, angle);
	Vector2i lr = Vector2i(retVal.right, retVal.bottom).rotate(hotspot, angle);
	
	//Use the sidemost corners as the bounds of the new rectangle
	retVal.left = cl_min(cl_min(ul.x, ur.x), cl_min(ll.x, lr.x));
	retVal.right = cl_max(cl_max(ul.x, ur.x), cl_max(ll.x, lr.x));
	retVal.top = cl_min(cl_min(ul.y, ur.y), cl_min(ll.y, lr.y));
	retVal.bottom = cl_max(cl_max(ul.y, ur.y), cl_max(ll.y, lr.y));
	return retVal;
#endif	
        return Rect();
}

Rect Rect::get_rot_bounds(Origin origin, int x, int y, float angle) const
{
	return get_rot_bounds(
		Vector2i(left, top) + calc_origin(origin, get_size()) + Vector2i(x, y),
		angle);
}

std::ostream& operator<<(std::ostream& s, const Rect& rect)
{
  return s << "rect[" << rect.left << ", " << rect.top << ", "
           << rect.right << ", " << rect.bottom << "]";
}

/* EOF */
