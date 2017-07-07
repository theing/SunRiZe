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

#ifndef MODULE_H
#define MODULE_H

#include "GPrimary.h" // Base class: GStandalone

class SModule : public GPrimary
{
  int width=150;
  int height=100;
  
public:
  SModule();
  virtual ~SModule();

public:
  virtual Point borderPoint(Point p);
  virtual bool toSelect(int x, int y);
  virtual void edit();
  virtual void draw(wxDC& deviceContext,bool isSelected);
  virtual String getString();
  virtual void newContext();
  constexpr static const char * id="module";
  virtual const char * getId() const { return id; }

};

#endif // MODULE_H
