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

#ifndef __GFrame__
#define __GFrame__


#include "Commons.h"

#include "MainPanel.h"
#include "GToolBar.h"
#include "GPanel.h"
#include "GSelector.h"
#include "Factory.h"

class exitOnMenuSelection;
class GToolBar;
class GFrame;


/**
 * @class GFrame
 * @author Marco
 * @date 06/28/17
 * @file GFrame.h
 * @brief The main frame management (SINGLETON).
 * In order to avoid a too strict dependence by the wxWidgets schema, SunRiZe wraps each part of the general layout,
 * to a more simplified model designed to satisfy the specific requirements.
 * The GFrame class intercepts every action performed on the Main Frame, and execute those action to the specific instance.
 * The available parts are :
 * <ul>
 * <il>GPanel the main panel on the right to draw in</il>
 * <il>GSelector the list/tree view on the left to select the context</il>
 * <il>GToolbar the toobar with the items to place into the drawing</il>
 * </ul>
 * Several action as the menu action are managed directly by the GFrame.
 * @note The GFrame is a SINGLETON with a special design. The main objects toolbar, panel and selector are directly available
 * by static calls, because the are always perfomed after the singleton is allocated except for the Factory that has a special
 * treatment.
 * @see GToolBar , GSelector and GPanel
 */

class GFrame : public MyFrame1
{
  friend GToolBar;
  

  bool changed;
  static GFrame * instance;
  GToolBar toolBar;
  GPanel panel;
  GSelector selector;
  wxFont font[4];
  int indexer;
  static Factory * factory;
  String projectPath;
  GFrame( wxWindow* parent );  

protected:
  void toolClicked( wxCommandEvent& event );
  virtual void panelKeyDown( wxKeyEvent& event );
  virtual void panelKeyUp( wxKeyEvent& event );
  virtual void panelMouseEvent( wxMouseEvent& event );
  virtual void panelPaintEvent( wxPaintEvent& event );
  virtual void itemSelected( wxCommandEvent& event );
  virtual void saveMenuSelection( wxCommandEvent& event );
  virtual void reloadMenuSelection( wxCommandEvent& event );
  virtual void projectOnMenuSelection( wxCommandEvent& event );
  virtual void exitOnMenuSelection( wxCommandEvent& event );
  virtual void generateOnMenuSelection( wxCommandEvent& event );
  virtual void aboutMenuSelection( wxCommandEvent& event );
  virtual void onCloseEvent( wxCloseEvent& event );
public:

  
  /**
   * @brief Get the choosen project path.
   * @return the choosen project path or "" if it does not exists.
   */
  String getProjectPath()
  {
    return projectPath;
  }
  
  /**
   * @brief Creates/Gets the instance of the singleton.
   * @return the GFrame reference.
   */
  static GFrame & getInstance() {
    if (!instance) instance=new GFrame(nullptr);
    return *instance;
  }
  
  
  /**
   * @brief GFrame::getToolBar gets the instance of the toolbar as defined in GFrame
   * @return The instance of the toolbar.
   */
  static GToolBar & getToolBar() {
    return instance->toolBar;
  }
  /**
   * @brief GFrame::getPanel gets the instance of the drawing panel as defined in GFrame
   * @return The instance of the panel.
   */
  static GPanel & getPanel() {
    return instance->panel;
  }
  /**
   * @brief GFrame::getSelector gets the instance of the context selector as defined in GFrame
   * @return The instance of the selector.
   */

  static GSelector & getSelector() {
    return instance->selector;
  }
  
  /**
   * @brief Call this if the model has been changed and need to be saved.
   */
  void dataChanged();
  
  /**
   * @brief Refresh the drawing panel.
   */
  void refreshDraw();
  
  
  /**
   * @brief Get the font by number
   * @param i the number of the font
   * @return the font reference
   * @note GFrame preallocates the system fonts, to be used in the drawn.
   * at the moment we have 4 fonts 10-11-12 and 14 points size.
   */
  wxFont & getFont(int i) {
    return font[i];
  }

  /**
   * @brief Increments and return the unique progressive ID.
   * This is used to identify the GObject in a file or during the code generation.
   * @see GObject::setIndexer , GObject::getIndexer
   * @return the unique ID.
   */
  int getIndexer() { return ++indexer; }
  /**
   * @brief Clear the unique progressive ID to 0, to begin a new phase.
   */
  void clearIndexer() { indexer=0; }

};


#endif // __GFrame__
