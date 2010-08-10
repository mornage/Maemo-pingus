/*  $Id: line_iterator.cpp 2918 2007-08-14 21:53:51Z grumbel $
**
**  Pingus - A free Lemmings clone
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include "line_iterator.hpp"

LineIterator::LineIterator(const std::string& str)
  : first(str.begin()),
    last(str.end()),
    line_end(str.begin())
{
}

LineIterator::LineIterator(std::string::const_iterator first_,
                           std::string::const_iterator last_)
  : first(first_),
    last(last_),
    line_end(first_)
{  
}

bool
LineIterator::next()
{
  if (line_end == last || (line_end+1 == last && *first == '\n'))
    {
      return false;
    }
  else
    {
      if (first != line_end)
        first = line_end + 1;
      
      do {
        ++line_end;
      } while(line_end != last && *line_end != '\n');

      return true;
    }
}

std::string
LineIterator::get()
{
  return std::string(first, line_end);
}

#ifdef __TEST__
// g++ line_iterator.cpp -o line_iterator -D__TEST__  -Wall -Werror -ansi -pedantic
#include <iostream>

void test(const std::string& str)
{
  std::cout << "Testing: " << std::endl;
  std::cout << "in:  \"" << str << "\"" << std::endl;

  std::cout << "out: " << std::flush;

  LineIterator it(str);
  while(it.next())
    std::cout << "\"" << it.get() << "\" " << std::flush;
    
  std::cout << std::endl;
  std::cout << std::endl;
}

int main()
{
  test("Test One");
  test("Test\nTwo");
  test("\nHello\nThree");
  test("Hello Four\n");
  test("Hello\nWorld\nFooBar\n");
  test("Hello\nWorld\nFooBar\n\n");
  test("1");
  return 0;
}
#endif

/* EOF */
