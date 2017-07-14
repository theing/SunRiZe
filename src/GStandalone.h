/*
 * SunRiZe
 * 
 * (c) 2017 by Marco Spreafico
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

#ifndef GSTANDALONE_H
#define GSTANDALONE_H

#include "GObject.h"
#include "GDrawHelper.h"
#include "GJunction.h"
/**
 * @class GStandalone
 * @author Marco
 * @date 06/25/17
 * @file GStandalone.h
 * @brief The STANDALONE Objects class
 * An object that can be placed in a graphical context without any at priori dependence from other objects
 * is defined STANDALONE. For example a STATE in a STATE machine, can be defined as STANDALONE.
 * Regardless of the related attributes that can define the general aspect of the object, a STANDALONE object is always 
 * defined by a single point, that by definition is the center of the object itself that is where the object is placed
 * or moved.
 * The PRIMARY object is a particular type of STANDALONE object with a context builtin.
 */
class GStandalone : public GObject
{
  
protected:
  Point center;
    
public:
  /**
   * @brief is a junction
   * @return false
   */
  virtual bool isJunction() const;
  /**
   * @brief is primary
   * @return false for this class
   * @see GPrimary
   */
  virtual bool isPrimary() const;
  /**
   * @brief Sets the center of the object
   * @param x coordinate of the center
   * @param y coordinate of the center
   */
  void setPoint(int x,int y);
  /**
   * @brief Gets the previously set point
   * @return the Point structure with the center point.
   */
  Point getPoint() const;
  GStandalone();
  virtual ~GStandalone();
  /**
   * @brief Returns the intersecting point
   * This function return the point at the interception between the external perimeter of the object
   * and the hypothetical line between the center of thi object and the passed point.
   * This is used by the JUNCTIONS drawings object to find the point where to draw the arrows or simply set the start/end of line.
   * @param p the point of the line
   * @return The specified intersection point
   */
  virtual Point borderPoint(Point p) = 0;
  /**
   * @brief The implementation for a standalone object
   * It is already abstract because we still don't know the object graphic apperarance.
   * @see GObject::toSelect()
   */
  virtual bool toSelect(int x,int y) = 0 ;
  /**
   * @brief Relative move
   * @param x
   * @param y
   * @see GObject::moveRel
   */
  virtual void moveRel(int x,int y);
  /**
   * @brief getContent
   * A generic STANDALONE object, has the ID, the MODEL definition,the POINT (center) coordinates and then the "SCHEMA"
   * that are the related attribute.
   * @param full is a full content is requested to be returned
   * @return the VAR content enhanced by additive properties.
   */
  virtual Var getContent(bool full);
  /**
   * @brief Load the object from the VAR structure
   * @param v VAR structure
   * @param map the association beween ID and Object to be used by the junctions
   */
  virtual void loadObject(Var & v,Map< int,Shared<GObject> > &map);


  /**
  * @brief check for AutoRing availablility for the model type of junction and fill p1/p2 
  * with the related break points
  * @param GJunction  
  * @param p1 the first point to break
  * @param p2 the second point to break
  * @param p3 the third point to break
  * @return true if the junction is possible, false otherwise
  */

  virtual bool autoRing(GJunction * j, Point &p1, Point &p2, Point &p3) = 0;

  /**
  * @brief check if the specific junction is accepted 
  * @param j the specific junction
  * @param dirIn true if direction IN false if direction OUT
  * @return true if the junction is possible, false otherwise
  */

  virtual bool accept(GJunction * j, bool dirIn)=0;

};

#endif // GSTANDALONE_H
