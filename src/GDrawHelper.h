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

#ifndef GDRAWHELPER_H
#define GDRAWHELPER_H

#include "Commons.h"


/**
 * @class GDrawHelper
 * @author Marco
 * @date 06/28/17
 * @file GDrawHelper.h
 * @brief Abstraction of the drawing essential.
 */

/// Generic redefinition of point
using Point = wxPoint;
/// Generic redefinition of rect
using Rect = wxRect;
/// Generic redefinition of size
using Size = wxSize;

/// This depends from the drawing color order , for example in WX is BBGGRR
#define DHRGB(rr,gg,bb) ((rr)|((gg)<<8)|((bb)<<16))

class GDrawHelper
{
  wxDC * device;
  
  
public:
  
  enum Alignment {
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER
  };
  
  /// Redefinition of Color
  typedef uint32_t Color;
  
  /**
   * New DrawHelper which incorporates the reference to the specific device
   */
  GDrawHelper(wxDC & dev);
  virtual ~GDrawHelper();
  /**
   * @brief Fills a rectangle with a black countour
   * @param r the rectangle
   * @param size the size of the countour line in pixels
   * @param color the fill color 
   */
  void fillRect(Rect r, int size,Color color);
  /**
   * @brief Fills a rounded rectable with a black contour
   * @param r the rectable
   * @param radius of the rounded zone
   * @param size the size of the countour line in pixels
   * @param color the fill color 
   */
  void fillRoundRect(Rect r, int radius,int size,Color color);
  /**
   * @brief Fills a polygonal line
   * @param n the number of points of the polygon
   * @param p the points array of the polygon
   * @param size the size of the countour line in pixels
   * @param color the fill color 
   */
  void fillPolygon(int n, const Point p[],int size,Color color);
  /**
   * @brief Fills a circle
   * @param x center coordinate
   * @param y center coordinate
   * @param radius of the circle
   * @param size the size of the countour line in pixels
   * @param color the fill color 
   */
  void fillCircle(int x,int y,int radius, int size,Color color);
  /**
   * @brief Draws a line
   * @param p1 the first point
   * @param p2 the second point
   * @param size the size of the countour line in pixels
   * @param dashed true if dashed false if not (default false)
   */
  void line(Point p1,Point p2,unsigned size,bool dashed=false );
  /**
   * @brief Shows a text at a specific point
   * @param text the text to show
   * @param p the point
   * @param font the index of the font
   * @see GFrame::getFont
   */
  void text(String text,Point p,int font);
  /**
   * @brief Shows a text vertical centered, then aligned in a rectangle
   * @param text the text to show
   * @param r the rectangle to draw the text
   * @param font the index of the font
   * @param align the horizontal alignment, ALIGN_LEFT, ALIGN_RIGHT or ALIGN_CENTER
   * @param margin if ALIGN_LEFT the left margin, if ALIGN_RIGHT the right margin in PIXELS.
   * @see GFrame::getFont
   */
  void text(String text,Rect r,int font,Alignment align=ALIGN_CENTER,int margin=0);
  /**
   * @brief Gives the text Size in pixels
   * @param text the text to show
   * @param font the index of the font
   * @return the Size of the text string in the current graphics device context
   * @see GFrame::getFont
   */
  Size textSize(String text,int font);
  /**
   * @brief Get the device context.
   * Used to implement specific drawing without using the helper.
   * @return the device context reference.
   */
  wxDC & getDevice() { return *device; }

};

#endif // GDRAWHELPER_H
