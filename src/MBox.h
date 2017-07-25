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

#ifndef MDIALOG_H
#define MDIALOG_H
#include "Commons.h"

/**
 * @class MBox
 * @author Marco
 * @date 06/28/17
 * @file MBox.h
 * @brief Dialog Boxes.
 * This class manages the essential Dialog boxes interface.
 */
class MBox
{
public:
  
  /**
   * @brief Creates a warning box.
   * @param s the message to display
   */
  static void warning(String s);
  /**
   * @brief Creates a error box.
   * @param s the message to display
   */
  static void error(String s);
  /**
   * @brief Creates a yesno box.
   * @param s the message to display
   * @return true for yes , false for no
   */
  static bool yesno(String s);
  /**
   * @brief Creates a yesnocancel box.
   * @param s the message to display
   * @return 1 for yes , 0 for no , 2 for cancel
   */
  static unsigned yesnocancel(String s);
  /**
   * @brief Creates a okcancel box.
   * @param s the message to display
   * @return true for ok , false for cancel
   */
  static bool okcancel(String s);
  /**
   * @brief Allow the user to choose a FOLDER
   * @return the selected folder with path or empty string, if the choice was not performed.
   */
  static String projectDialog();

};

#endif // MDIALOG_H
