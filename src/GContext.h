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

#ifndef GCONTEXT_H
#define GCONTEXT_H

#include "Commons.h"
#include "GObject.h"
#include "GPrimary.h"

/**
 * @class GContext
 * @author Marco
 * @date 06/27/17
 * @file GContext.h
 * @brief The graphic context.
 * The SunRiZe structure is based on a single PANEL where the model is designed.
 * The context represents the abstract model to be projected into the panel.
 * Usually we have more than one "level" of context, there is always a main context that represents the whole model, which has
 * PRIMARY objects that contain other non-main contexts.
 * A Context can be viewed as a vector of GObjects with several functions connected to the graphics part of the panel.
 */

class GContext
{
  
  Vector< Shared<GObject> > content;
  int selected;
  unsigned toolbar;
  GPrimary * parent;

public:
  /**
   * @brief Constructor
   * Define a new "main" context that is a context independ from primary objects.
   */
  GContext();
  /**
   * @brief Constructor
   * Define a new context that is connected to a primary object referred to the same primary object.
   * @see the note regarding the GPrimary object reference 
   */
  explicit GContext(GPrimary & p);
  virtual ~GContext();
  
  /**
   * @brief Returns the GPrimary object as a simple pointer.
   * @return the primary object or null if this is the main context.
   * @note we are using a simple pointer here instead of a weak because this is a pointer to the object that own the context, itself. 
   */
  GPrimary * getParent() {
    return parent;
  }
  
  /**
   * @brief Get the toolbar number
   * The toolbar represents the objects that can be inserted into the current drawing,
   * so that those objects depend from the context that is viewable at the moment.
   * @return the toobar number associated with the current context. 
   * @see GToolBar
   */
  unsigned getToolbar() const {
    return toolbar;
  }
  
  /**
   * @brief Setter for the toolbar number
   * @param tool is the number of the toolbar to be associated to the context
   * @see GToolBar
   */
  void setToolbar(unsigned tool) {
    toolbar=tool;
  }
  
  /**
   * @brief The draw function.
   * This function is invoked when the panel is refreshing, the provided function scans the objects into the context and invokes
   * the related draw functions.
   * @param deviceContext the DC (device context) of the panel to draw the GContext.
   */
  void draw(wxDC& deviceContext);
  
  /**
   * @brief Add a new object to the context
   * @param o the shared pointer containing the object by reference.
   */
  void addItem(Shared<GObject> & o);

  
  /**
   * @brief Release the current selected object
   */
	void releaseSelection();

  /**
   * @brief Check if the point belong to an object, in this case select the object.
   * @param x point coordinate
   * @param y point coordinate
   */
	void querySelection(int x,int y);
	
  /**
   * @brief Move the selected object (if one) by the relative increments.
   * @param i relative x increment
   * @param j relative y increment
   * @return false if no object is selected, true otherwise
   */
	bool moveObject(int i, int j);
	
  /**
   * @brief Get the selected object as shared
   * Used to build the relation with the junctions.
   * @return If no object are selected the shared pointer is null
   */
  Shared<GObject> getSelection();
  
  /**
   * @brief Manages the double click
   * Check if the point belong to an object, it invokes the related edit function.
   * @param x point coordinate
   * @param y point coordinate
   */
  
	void queryDoubleClick(int x, int y);

	
  /**
   * @brief returns the entire context list by reference.
   * @return the std::vector< std::shared_ptr<GObject> > context vector by reference.
   */
	Vector<Shared<GObject>> & contextList()
	{
		return content;
	}

  /**
   * @brief manages the backspace key, that is the deletion of a JUNCTION breaking point.
   */
	void keyBackspace();


  /**
   * @brief manages the removal of a standalone object or a junction. 
   * If a junction becomes invalid due to the absence of source or destination, it is removed too.
   */
	void keyRemove();
	
  /**
   * @brief Checks if this is the main context
   * @return true if this is the main context, false if there is an associated primary object
   */
  bool isMainContext() const;
  
  /**
   * @brief Collection of a context.
   * This function, scans all the vector and builds a Var containing an array of Vars given by the getContent function of GObject
   * @param full get the full collection
   * @return the Var representing the collection
   * @note The collect function works with two step, int the first one, collects all the NON-JUNCTION object and in the second one
   * the JUNCTIONS, because those latest objects, needs to have both the ending defined.
   * @see GObject::getContent and GJunction::getContent note
   */
  Var collect(bool full);
  /**
   * @brief Load a collection from a Var.
   * @param v the Var with the collection.
   */
  void loadCollection(Var & v);
  
  /**
   * This function get the maximum size of the context in pixels.
   * @return the context size
   */
  Size getContextSize() const;

};

#endif // GCONTEXT_H
