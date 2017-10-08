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

#include "SDependency.h"
#include "GStandalone.h"
#include "math.h"

SDependency::SDependency()
{
}

SDependency::~SDependency()
{
}

bool SDependency::edit()
{
  return false;
}

void SDependency::draw(wxDC& deviceContext, bool isSelected)
{	    
    if ((!source.expired())&&(!destination.expired()))
    {
        GDrawHelper dc(deviceContext);
        unsigned penSize=2;
        if (isSelected) penSize=4;

        // Simplification
        GStandalone * cls =  dynamic_cast<GStandalone*> (source.lock().get());
        GStandalone *cld = dynamic_cast<GStandalone*> (destination.lock().get());

        int j=line.size()-1;
        line[j]=cld->getPoint();
        
        Point a;

        a=cls->borderPoint(line[1]);
        line[0]=a;

        a=cld->borderPoint(line[j-1]);
        line[j]=a;
       
        int i;
        for (i=0;i<j;++i)
        {
            dc.line(line[i],line[i+1],penSize,true);
        }
        
        // Arrow
        double angle;
        a=line[j];
        angle = atan2(a.y-line[j-1].y,a.x-line[j-1].x);
        Point b(a.x-(int)(15*cos(angle-.3)),a.y-(int)(15*sin(angle-.3)));
        dc.line(a,b,penSize);
        Point c(a.x-(int)(15*cos(angle+.3)),a.y-(int)(15*sin(angle+.3)));
        dc.line(a,c,penSize);
        
    }
}
