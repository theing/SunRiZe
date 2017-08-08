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

#ifndef GLOB_H
#define GLOB_H

#include "Commons.h"

/**
 * @class Glob
 * @author TheIng
 * @date 06/29/17
 * @file Glob.h
 * @brief Globals requests and tools.
 */

class Glob
{
  static String scriptPath;
  
public:
  /**
  * @brief Equality of two strings
  * @param a
  * @param b
  * @return true if equal
  */
  static bool equal(const char *a,const char *b);
  
  /**
   * @brief get the resource path as passed by the environment
   * @return the path contained in SUNRIZE_HOME/modules or the <current folder>/modules
   */
  static String resPath();
  
  /**
   * @brief Initializes globals, used by main
   */
  static void init();
  
  /**
   * @brief Checks the existence of a folder
   * @param folder the folder name
   * @return true if the folder exists and it is accessible, false otherwise
   */
  static bool folderExists(String folder);

  /**
   * @brief Checks the pure existence of a file
   * @param file the file name
   * @return true if the file exists, false otherwise
   */
  static bool fileExists(String file);
  
  /**
   * @brief Composes a path by starting from a folder path and a file name
   * @param path the folder path
   * @param file the file name
   * @return the full path string.
   */
  static String composePath(String path,String file);
  
  /**
   * @brief Builds the full path of the file if it does not exists.
   * @param fullPath the full path of the file
   * @note this function ignores everything there is after the trailing '/'. To make a path for /tmp/a for example you need
   * to indicate /tmp/a/ , to make a path for the file /tmp/a/hello.tmp you can pass /tmp/a/hello.tmp ad the path /tmp/a will
   * be created.
   */
  static bool makePath(String fullPath);

  /**
   * @brief Get the path of the executable file
   * @return the path of the executable file as string or an empty string
   */
  static String getExecutablePath();

  /**
   * @brief Make a backup file of the passed file name
   * @return: false if backup cannot be done
   */
  static bool makeBackup(String fullPath);

};

#endif // GLOB_H
