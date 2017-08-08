/*
 * SunRiZe
 * 
 * (c) 2017 by Marco Spreafico ( https://theing.blogspot.com )
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

#ifndef TEXT_H
#define TEXT_H
#include "Commons.h"
#include <sstream>

  /**
   * @class Text
   * @author TheIng
   * @date 06/27/17
   * @file Text.h
   * @brief Text utilities.
   */
  class Text
  {
        
  
  public:
    /**
     * @brief Split a string into token and put it in a vector of string
     * @param _str the string to split in several tokens
     * @param _delimiters split when one of the token has met.
     * @param _tokens the vector that needs to be defined before the call and is pushed_back with tokens.
     */
    static Vector<String> split(const String _str, const String _delimiters );
    /**
     * @brief replace in a string all the recurrences of a substring with another substring
     * @param _str the input and output string that is overwritten.
     * @param _find_what string to replace
     * @param _replace_with string to insert instead
     */
    static String replace( String  _str, const String _find_what, const String _replace_with );
    /**
     * @brief remove all the characters of a set on the left and right in a string until the first not in the set.
     * @param _str the input and output string that is overwritten.
     * @param _chr the character set.
     */
    static String trim( String  _str, String _chr );
    /**
     * @brief remove all the characters of a set on the right in a string until the first not in the set.
     * @param _str the input and output string that is overwritten.
     * @param _chr the character set.
     */
    static String trimRight( String _str, String _chr );
    /**
     * @brief remove all the characters of a set on theleft in a string until the first not in the set.
     * @param _str the input and output string that is overwritten.
     * @param _chr the character set.
     */
    static String trimLeft( String _str, String _chr );
    
    /**
     * @brief padLeft is the left fill function.
     * If you need to create a string of a fixed size, you can use padleft to fill on the left a string with
     * a character until the right size is reached. This is good for example to align numbers before printing.
     * @param _str the string to fill, input only.
     * @param c the character used to fill on the left
     * @param min the minimum number of characters to reach.
     * @return the padded string.
     * @note if the input string is greather of the number of chars, it is returned untouched.
     */
    static String padLeft(String  _str,char c,unsigned min);
    /**
     * @brief padRight is the right fill function.
     * If you need to create a string of a fixed size, you can use padright to fill on the right a string with
     * a character until the right size is reached. 
     * @param _str the string to fill, input only.
     * @param c the character used to fill on the right.
     * @param min the minimum number of characters to reach.
     * @return the padded string.
     * @note if the input string is greather of the number of chars, it is returned untouched.
     */
    static String padRight(String _str,char c,unsigned min);

    /**
     * @brief Read and entire file into a string
     * @param _name The File name
     * @return The string with the content of the file
     * @note on IO errors throws an OSException()
     */
    static String readFile(String _name);

    /**
    * @brief write a string in a file
    * @param _name The File name
    * @note on IO errors throws an OSException()
    */
    static void writeFile(String _name, String _content);

  };


#endif // TEXT_H
