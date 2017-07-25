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

#ifndef SCONDITION_H
#define SCONDITION_H

#include "GStandalone.h"
#include "Commons.h"

class SCondition : public GStandalone
{
public:
  SCondition();
  virtual ~SCondition();
  virtual Point borderPoint(Point p);
  virtual bool toSelect(int x, int y);
  virtual void edit();
  virtual void draw(wxDC& deviceContext,bool isSelected);
  constexpr static const char * id="condition";
  virtual const char * getId() const { return id; }
  virtual void sizeAdapter(Size & size) const;
  virtual bool autoRing(GJunction * j, Point &p1, Point &p2, Point &p3);
  virtual bool accept(GJunction * j, bool dirIn);
};

#endif // SCONDITION_H
