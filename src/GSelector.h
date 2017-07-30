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

#ifndef GSELECTOR_H
#define GSELECTOR_H

#include "Commons.h"
#include "GObject.h"

class GFrame;

/**
 * @class GSelector
 * @author TheIng
 * @date 06/28/17
 * @file GSelector.h
 * @brief The Context Selector.
 * This selection lists, is generally represented by a list or a tree. The first item is the (Main) or root node and represents
 * the main context. 
 */

class GSelector
{
  friend class GFrame;
  GSelector(wxListBox * lb);
  
  wxListBox * listBox;

  class Container : public wxClientData 
  {
  public:
    Weak<GObject> content;
  };
  
public:
  virtual ~GSelector();

  /**
   * @brief Refresh the list
   * When the list is refreshed, it scans the context and checks for the primary objects. If a primary object has a subcontext,
   * a new weak relation is established and the String returned by GPrimary::getString is used to create a selectable node.
   */
  void refresh();
  /**
   * @brief change the current context to the selected one.
   * When a new context is selected, GFrame invokes this function and current selected context in the panel
   * is changed to the new one.
   */
  void selected();
};

#endif // GSELECTOR_H
