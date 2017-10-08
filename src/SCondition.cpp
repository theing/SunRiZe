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

#include "SCondition.h"
#include "Glob.h"

#define DIM 20

SCondition::SCondition()
{
}

SCondition::~SCondition()
{
}

Point SCondition::borderPoint(Point p)
{
    double dx=p.x-center.x;
		double dy=p.y-center.y;
		if ((dx*dx)+(dy*dy)<10) return center; 		
		double alpha=atan2(abs(dy), abs(dx));
		double r=((double)DIM)/(cos(alpha)+sin(alpha));
		return Point( (int)(r*cos(alpha)*SIGNUM(dx) +center.x ),(int) ( r*sin(alpha)*SIGNUM(dy) +center.y));
		
}

bool SCondition::toSelect(int x, int y)
{
    double dx=x-center.x;
		double dy=y-center.y;
		if ((dx*dx)+(dy*dy)<10) return true; 
		
		double alpha=atan2(abs(dy), abs(dx));
		double r=((double)DIM)/(cos(alpha)+sin(alpha));
    
		if ((dx*dx)+(dy*dy)<=(r*r)) return true;
		return false;
}

bool SCondition::edit()
{
  return false;
}

void SCondition::draw(wxDC& deviceContext, bool isSelected)
{
    GDrawHelper dc(deviceContext);
    Point p[4]={ {center.x-DIM,center.y },{center.x,center.y-DIM},{center.x+DIM,center.y},{center.x,center.y+DIM} };
    if (isSelected)
      dc.fillPolygon(4, p, 5,0x00ffff);		
    else
      dc.fillPolygon(4, p, 2,0x00ffff);		
}

void SCondition::sizeAdapter(Size & size) const
{
	size.x = VMAX(size.x, center.x + DIM);
	size.y = VMAX(size.y, center.y + DIM);

}

bool SCondition::autoRing(GJunction * j, Point & p1, Point & p2, Point & p3)
{
  return false;
}

bool SCondition::accept(GJunction * j, bool dirIn)
{
  return true;
}

