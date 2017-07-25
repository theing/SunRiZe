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

#ifndef FACTORY_H
#define FACTORY_H

#include "GToolBar.h"

/**
 * @class Factory
 * @author Marco
 * @date 06/28/17
 * @file Factory.h
 * @brief The Objects specific factory.
 * Factory is the interface between the general program structure and the specific implementation. By changin the factory
 * the modules and the code generator, we can change the model as well as the programming language.
 */

class Factory 
{
public:
  /**
   * @brief Fill the toobar with the elements.
   * By choosing an element in the toolbar we create the related empty object in a shared pointer.
   * @param toolbar is the toobar reference
   * @param currentToolbar the number of the required toolbar
   */
  static void createToolbar(GToolBar& toolbar, int currentToolbar);
  /**
   * @brief Create the new object by ID.
   * Each object type has a fixed const char * ID that reports in runtime the type of the object. This function creates a default 
   * object from the requested ID as a pointer to be passed to a shared constructor.
   * @param objectType the obejct ID
   * @return the Object pure pointer.
   */
  static GObject *createObject(const char * objectType);

};



#endif // FACTORY_H
