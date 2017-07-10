/*
 * SunRiZe
 * 
 * (c) 2017 by Marco Spreafico
 * 
 * This file is part of SunRiZe.
 *
 * SunRiZe is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SunRiZe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Text.h"
#include <stdarg.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <fstream>


Vector<String> Text::split(const String _str, const String _delimiters)
{
  Vector<String> _tokens;
  String::size_type lastPos = _str.find_first_not_of(_delimiters, 0);
  String::size_type pos     = _str.find_first_of(_delimiters, lastPos);

  while ((String::npos != pos) || (String::npos != lastPos))
  {
      _tokens.push_back(_str.substr(lastPos, pos - lastPos));
      lastPos = _str.find_first_not_of(_delimiters, pos);
      pos = _str.find_first_of(_delimiters, lastPos);
  }
  return _tokens;
}

String Text::replace( String _str, const String _find_what, const String _replace_with )
{
  String::size_type pos=0;
  while((pos=_str.find(_find_what, pos))!=String::npos)
  {
      _str.erase(pos, _find_what.length());
      _str.insert(pos, _replace_with);
      pos+=_replace_with.length();
  }
  return _str;
}


String Text::trim(String _str, String _chr)
{
  trimLeft(_str,_chr);
  trimRight(_str,_chr);
  return _str;
}

String Text::trimLeft(String _str, String _chr)
{
  _str.erase (0, _str.find_first_not_of (_chr)) ;
  return _str;
}

String Text::trimRight(String _str, String _chr)
{
  if (_str.find_last_not_of (_chr) == String::npos) _str="";
  else  _str.erase (_str.find_last_not_of (_chr) + 1) ;
  return _str;
}


String Text::padLeft(String _str, char c, unsigned  min)
{
  size_t s;
  s=_str.size();
  if (s<min) {
    return String(min-s,c)+_str;
  }
  return _str;
}

String Text::padRight(String _str, char c, unsigned min)
{
  size_t s;
  s=_str.size();
  if (s<min) {
    return _str+String(min-s,c);
  }
  return _str;
}

String Text::readFile(String _name)
{
  std::ifstream inFile;
  inFile.open(_name);
  if (inFile.fail()) throw OSException();
  std::stringstream buffer;
  buffer << inFile.rdbuf();
  inFile.close();
  return buffer.str();
}

void Text::writeFile(String _name, String _content)
{

  std::ofstream outFile;
  outFile.open(_name);
  if (outFile.fail()) throw OSException();
  outFile << _content;
  outFile.close();

}
