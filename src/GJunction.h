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

#ifndef GJUNCTION_H
#define GJUNCTION_H

#include "GObject.h" // Base class: GObject
#include "GDrawHelper.h"

/**
 * @class GJunction
 * @author TheIng
 * @date 06/27/17
 * @file GJunction.h
 * @brief JUNCTION between GObjects.
 * In a drawing, two objects can be connected, to indicate some kind of relation. For example a dependency, or aggregation.
 * The GJunction object implements the basic behaviour for this kind of objects.
 * Since a JUNCTION is not STANDALONE, it can't be put freely onto the drawing without specifying the "source" and "destination"
 * that are two existing and compatible objects. These objects are connected with a weak pointer to the context object instance, so
 * that if a STANDALONE object is removed, all the junctions connected to it become invalid and are removed too.
 * @note Since the Junction is always a LINE with some kind of stretch and arrows the generic layout of selection and moving is pre
 * defined, as well as the source and destination management. 
 */

class GJunction : public GObject
{
  
  int u,ux,uy,px,py;
  bool uk;

protected :
  Vector<Point> line;
  Weak<GObject> source;
  Weak<GObject> destination;
  
public:
  /**
   * @brief Moves relatively.
   * A junction is moved by moving the source or the destination. By dragging from a different point of the junction this function
   * creates a new fixed moveable point to break the line.
   * @param x increment coordinate
   * @param y increment coordinate
   */
  virtual void moveRel(int x, int y);
  /**
   * @brief Selection of the line.
   * This function checks the proximity of the given coordinated to the line.
   * @param x coordinate
   * @param y corrdinate
   * @return true if the selected point is near the line.
   */
  virtual bool toSelect(int x, int y);
  /**
   * @brief Removes a breaking point created by moveRel wile this point is selected.
   */
  void removePoint();
  GJunction();
  virtual ~GJunction();
  /**
   * @brief is a Junction
   * @return true
   */
  virtual bool isJunction() const;
  /**
   * @brief is a Primary
   * @return false
   */
  virtual bool isPrimary() const ;
  /**
   * @brief Sets one end of a Junction.
   * The first time this function is called, it set the begin, the second time it set the end of the line.
   * @param end the reference of the shared pointer of the standalone object representing the end.
   * @return false if setting the begin, true if setting the end.
   */
  bool setEnd(Shared<GObject> & end);
  /**
   * @brief Gets the content var.
   * The full version returns the ID the MODEL, the SOURCE, the DESTINATION and a vector of BREAKING POINTS.
   * @note We cannot save a pointer in a VAR ( or JSON), so to explicitate the connections we use the ID that is unique for
   * each OBJECT. The reason because the NON-JUNCTIONS object are always collected before the JUNCTIONS, is to give this
   * number a value.
   * @param full is the full request.
   * @return the content
   */
  virtual Var getContent(bool full); 
   /**
   * @brief Creates the object from the passed Var and creates/fills the related context if one.
   * @param v the Var
   * @param map the association between index and GObjects.
   */
  virtual void loadObject(Var & v,Map< int,Shared<GObject> > &map); 
  
  /**
   * @brief Check if source and destination have references.
   * @return true if valid, false if not
   */
  bool validate();
  
  virtual void sizeAdapter(Size & size) const;

  /**
  * @brief Source Getter.
  * @return the const reference to the source weak
  */
  const Weak<GObject> & getSource();
  /**
  * @brief Destination Getter.
  * @return the const reference to the destination weak
  */
  const Weak<GObject> & getDestination();
};

#endif // GJUNCTION_H
