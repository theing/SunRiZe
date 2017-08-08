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

#ifndef GOBJECT_H
#define GOBJECT_H

#include "Var.h"
#include "GDrawHelper.h"



/**
 * @class GObject
 * @author TheIng
 * @date 06/25/17
 * @file GObject.h
 * @brief The base abstract class for every graphics object.
 * The SunRiZe data structure is based on two essential concepts :
 * <ul> 
 * <li>the GContext</li>
 * <li>the GObject</li>
 * </ul>
 * A GContext is a container (vector) of GObjects, describing the current "scene".
 * Each GObject has a Var type that is a untyped polimorphic container and some information about the drawing and the relation with
 * other GOobjects.
 * This class is never used direcly, but we need another level of abstration identifying all the possible typology of graphical object,
 * that are the STANDALONE, the JUNCTION objects and the PRIMARY objects that contain new contexts and are selectable by the module
 * list control.
 * @see GJunction, GStandalone and GPrimary
 */


class GObject
{

  int indexer;  
    
public:

  ///The data container 
  Var content;
  
  GObject();
  virtual ~GObject();

  /**
   * @brief Gets the content
   * This function returns the data related to the object in Var format.
   * There is the normal call, that return the essential data to generate the related code only
   * and the full call used to return all data to be stored to identity the graphics object.
   * @param full
   * @return the current object data
   */
  virtual Var getContent(bool full) =0;
  /**
   * @brief Gets the identifier
   * Used by the code generator and the factory.
   * @return a string name indicating the object typology.
   */
  virtual const char * getId() const = 0;
  /**
   * @brief Edits the current object when requested
   * This operations is connected to the double click,
   * and usually requires to build and show the dialog box to edit the specific object parameters.
   */
  virtual void edit() = 0;
  /**
   * @brief Tells the caller if the object is a Junction
   * @return true if is a junction, false otherwise
   */
  virtual bool isJunction() const = 0 ;
  /**
   * @brief Tells the caller if the object is Primary
   * @return true if is a primary, false otherwise
   */
  virtual bool isPrimary() const = 0;
  /**
   * @brief Tells the caller if the object can be deletedon the scene or is prefixed by the system
   * by default an object is always removeable except for the objects embedded into the context by design.
   * @return true if is a removeable, false otherwise
   */
  virtual bool isRemoveable() const ;
  /**
   * @brief Gives the relative movement from the previous placement.
   * @param x the x coordinate increment
   * @param y the y coordinate increment
   */
  virtual void moveRel(int x,int y) = 0;
  /**
   * @brief Tells the caller if the indicated point is over the current object
   * @param x the x coordinate of the point
   * @param y the y coorinate of the point
   * @return true if is in the object space, false otherwise
   */
  virtual bool toSelect(int x,int y) = 0 ;
  /**
   * @brief Draws the object by starting by a device context of wxWidget.
   * @param deviceContext the wxDX of the panel where to draw the object
   * @param isSelected if true the object is graphically represented as "selected".
   */
  virtual void draw(wxDC& deviceContext,bool isSelected) =0;  
  /**
   * @brief Loads the object from the Var data structure
   * @note By loading a context we need to load the STANDALONE/PRIMARY objects before the junction, in order to be sure
   * that the JUNCTION will have the starting and ending point defined, before to be saved.
   * @see GJunction
   * @param v the var data structure representing the object
   * @param map the association between this object and the index of the object.
   * @note the MAP is defined used and destroyed locally into a function, so we can report
   * the shared pointer instead of making weak pointers.
   */
  virtual void loadObject(Var & v,Map< int,Shared<GObject> > &map) = 0;
  
  
  /**
   * @brief Sets the indexer
   * this function reuturns the indexer during the save or code generation operation.
   * a call to this function ask the system to set the indexer and returns it,
   * the basic indexer is autoincremented so that it identifies a unique object.
   * @return the new/current index.
   */
  int setIndexer();
  /**
   * @brief Sets the indexer to previous value
   * this function is used in load operations to reload the unique identifier into the object.
   * The unique identifiers are used by the junction later to reconnect the starting and ending point.
   * @param index the current index to set
   */
  void setIndexer(int index);
  /**
   * @brief Returns the indexed related to this object
   * @return the indexer
   */
  int getIndexer() const;

  /**
   * The Size Adapter, gets the maximum coordinates of the object drawing and adapts the
   * declared size to fully contain it.
   * @param size the size to adapt
   */
  virtual void sizeAdapter(Size & size) const = 0;
  
};

#endif // GOBJECT_H
