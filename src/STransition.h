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

#ifndef STRANSITION_H
#define STRANSITION_H

#include "GJunction.h"

class STransition : public GJunction
{
  
  void drawCondition(GDrawHelper &dc,int x,int y);  
  void drawToken(GDrawHelper &dc,int x,int y);  
  void drawTime(GDrawHelper &dc,int x,int y);
public:
  STransition();
  virtual ~STransition();
  virtual void edit();
  virtual void draw(wxDC& deviceContext,bool isSelected);
  constexpr static const char * id="transition";
  virtual const char * getId() const { return id; }
};


#endif // STRANSITION_H
