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

#ifndef GPANEL_H
#define GPANEL_H

#include "Commons.h"
#include "GContext.h"
#include "SModule.h"

class GFrame;

/**
 * @class GPanel
 * @author TheIng
 * @date 06/28/17
 * @file GPanel.h
 * @brief The drawing panel.
 * The drawing panel contains the main context and a weak reference to the current context.
 * This panel receives the drawing (Mouse/keys) actions, by the GFrame and transfers them to the current context.
 */

class GPanel
{

  friend class GFrame;
  GPanel(wxScrolledWindow * ctrl);
  
  wxScrolledWindow * ctrl;
  GContext mainContext;
  GContext * currentContext;  
  Point oldPoint;

  class {

    List< Var > hist;
    List< Var > red;
    Var temp;
    static const List<Var>::size_type maxSize = 10;
    
  public:


    void save(Var & val) {
      temp = val;
    }

    Var load() {
      if (hist.empty()) return Var();
      red.push_back(temp);
      Var res = hist.back();
      hist.pop_back();
      return res;
    }

    Var redo() {
      if (red.empty()) return Var();
      Var res = red.back();
      red.pop_back();
      return res;
    }

    void clear() {
      hist.clear();
      red.clear();
    }

    void commit() {
      if (temp.isNull()) return;
      if (!red.empty()) red.clear();
      while (hist.size() >= maxSize) {
        hist.pop_front();
      }
      hist.push_back(temp);
      temp.null();
    }

  } history;

public:
  virtual ~GPanel();
  /**
   * @brief Sent by the wx system, and used to redraw this panel.
   * @param dc the Panel device context
   */
  void draw();
  /**
   * @brief Sets the current context to a specific one.
   * This also redraws the context to the new one.
   * @param cc the context reference
   */
  void setCurrentContext(GContext & cc) {
    currentContext = &cc;
  }  
  /**
   * @brief Gets the current context
   * @return the current context reference
   */
  GContext & getCurrentContext() {
    return *currentContext;
  }
  /**
   * @brief Gets the contained MAIN context
   * @return the main context reference
   */
  GContext & getMainContext() {
    return mainContext;
  }
  /**
   * @brief Switch or create a context from a primary object
   * This function is connected to a key (Ins by default).
   * When the ins key is pressed while we are keeping a GObject selected,
   * this function is invokes and check the primary object for a context.
   * if the context exists, it is switched as new current context, 
   * if it does not exists it is created, then switched.
   */
  void switchToPrimary();
  /**
   * CopySelected clones the selected item if one and push it into the 
   * toolbar in order to create a copy when the panel is clicked.
   */
  void copySelected();
  /**
   * @brief Manages the mouse LEFT BUTTON down action
   * @param p the mouse pointer position
   */
  void mouseDown(Point & p);
  /**
   * @brief Manages the mouse LEFT BUTTON up action
   * @param p the mouse pointer position
   */
  void mouseUp(Point & p);
  /**
   * @brief Invoked continuously during the drag operation
   * @param p the mouse pointer position
   */
  void mouseDrag(Point & p);
  /**
   * @brief Manages the mouse LEFT BUTTON double click
   * @param p the mouse pointer position
   */
  void mouseDoubleClick(Point & p);
  /**
   * @brief Manages the KEY down
   * @param keycode the related keycode
   */  
  void keyDown(int keycode);

  /**
  * Save full context history
  */
  void saveHistory();

  /**
  * Load full context history to current
  */
  void loadHistory();

  /**
  * Commit changes to history
  */
  void commitHistory();

  /**
  * Clear current history
  */
  void clearHistory();

  /**
  * Redo after loadHistory
  */
  void redoHistory();
};

#endif // GPANEL_H
