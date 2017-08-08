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

#ifndef GTOOLBAR_H
#define GTOOLBAR_H

#include "Commons.h"
#include "GObject.h"

class GFrame;

/**
 * @class GToolBar
 * @author TheIng
 * @date 06/28/17
 * @file GToolBar.h
 * @brief The ToolBar containing the GObjects to be placed.
 * 
 */

class GToolBar
{
  
  friend class GFrame;
  GToolBar(wxFrame *fr,wxToolBar* tb);
  
  int selectedItem;
  wxToolBar* toolBar;
  wxFrame *frame;
  // We use int in order to avoid dependency 
  // from this module and the modules enum.
  Map< int , const char * > items;
  Shared<GObject> selection;
  
    
public:
  virtual ~GToolBar();
  /**
   * @brief Add item to toolbar
   * @param resource the resource PNG name
   * @param type the const char * string ID of the current choice
   */

  void addItem(const char *xpm[],const char * type);
  /**
   * @brief Chooses an set which toolbar to show at the moment.
   * It uses the factory to perfom this action/
   * @param tool the toolbar number.
   */
  void setToolBox(unsigned tool);
  /**
   * @brief Invoked by GFrame means that someone has clicked an item.
   * @param id the item to set.
   * @note when the user is pressing a button on the toolbar, the GFrame call this function with the ID of the pressed button.
   * This function gets the const char * ID type, associated with this id and call the factory that returns a simple pointer to
   * a new empty object ot the required type.
   * The pointer is stored in the shared "Selection" and the toolbar maintains the Ownership, until another button is selected
   * and the old content is destroyes, or the toolbar is deselected. If the user places this object into a context, the context
   * become the new owner and the toolbar is deselected by design.
   */
  void clicked(int id);  
  /**
   * @brief Gets the current selection or an empty shared
   * if no selection is perfomed.
   * @return the shared pointer to be passed to the context.
   */
  Shared<GObject> & getSelection();
  /**
   * @brief Clears the selection graphically and by placing the shared to nullptr.
   */
  void clearSelection();
};

#endif // GTOOLBAR_H
