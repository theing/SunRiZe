/*
 * SunRiZe
 * 
 * (c) 2017 by TheIng ( https://theing.blogspot.com )
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

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "Commons.h"
#include "Var.h"


/**
 * @class JSONParser
 * @author TheIng
 * @date 06/27/17
 * @file JSONParser.h
 * @brief The JSON parser/converter.
 * The JSONParser is a recursive JSON parser working on std::string.
 * By giving a parsable string, the parser creates a Var with the structured content of the json object.
 * A provided static function can do the inverse process, converting a var into a json string.
 * @note UTF8 conversion is supported.
 */
class JSONParser
{
 
  unsigned p;
  String tp;
 
  void ignoreBlank();
  bool last();
  char next();
  char nextNB();
  char current();
  void forward();
  
  Var parseArray();
  Var parseObject();
  Var parseNumber();
  void parseUnicode(String & s);
  void parseBackSlash(String & s);
  Var parseString();  
  Var parseBool();
  Var parseNull();
  Var parseInit();  
  
  String toUTF8(unsigned v);
  static String rencodeStr(String s);  
  
public:
  JSONParser();
  virtual ~JSONParser();
  
  /**
   * @brief Converts a Var to a std::string
   * @param val the Var object by reference
   * @return the resulting string
   */
  static String toString(Var & val);
  /**
   * @brief Parses a string and creates a Var.
   * @param s the string to parse by reference
   * @return the Var object
   */
  Var fromString(String s);
 
  
};


#endif // JSONPARSER_H
