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

#include "SInitState.h"
#include "GDrawHelper.h"
#include "math.h"

SInitState::SInitState()
{
}

SInitState::~SInitState()
{
}

Point SInitState::borderPoint(Point p)
{
  double dx=p.x-center.x;
  double dy=p.y-center.y;
  if ((dx*dx)+(dy*dy)<10) return center; 
  double alpha=atan2(abs(dy), abs(dx));
  return Point( (int)(15*cos(alpha)*SIGNUM(dx) +center.x ),(int) ( 15*sin(alpha)*SIGNUM(dy) +center.y) );				
}


bool SInitState::toSelect(int x, int y)
{
  double dx=x-center.x;
  double dy=y-center.y;
  if ((dx*dx)+(dy*dy)<=(15*15)) return true;
  return false;	
}

void SInitState::edit()
{
}

void SInitState::draw(wxDC& deviceContext, bool isSelected)
{
  GDrawHelper dc(deviceContext);
  if (isSelected)
    dc.fillCircle(center.x,center.y,15,5,0x000000);
  else
    dc.fillCircle(center.x,center.y,15,2,0x000000);
}

bool SInitState::isRemoveable() const
{
  return false;
}
