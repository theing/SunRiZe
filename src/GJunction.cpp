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

#include "GJunction.h"
#include "GStandalone.h"
#include "GFrame.h"

#define NEAR 40
#define PROXY 5
#define CANG 0.2

GJunction::GJunction():line(2)
{
}

GJunction::~GJunction()
{
}

bool GJunction::isJunction() const
{
  return true;
}
bool GJunction::isPrimary() const
{
  return false;
}


bool GJunction::setEnd(Shared<GObject>& end)
{
  GStandalone *gs= dynamic_cast<GStandalone *>(end.get());
  if (source.use_count()==0)
  {
    if (!gs->accept(this,false)) {
      GFrame::getToolBar().clearSelection();
      return false;
    }
    source=end;
    return false;
  }
  if (!gs->accept(this, true)) {
    GFrame::getToolBar().clearSelection();
    return false;
  }
  destination=end;
  if (source.lock()==destination.lock())
  {
    GStandalone *gs = dynamic_cast<GStandalone*>(source.lock().get());
    Point p1, p2, p3;
    if (!gs->autoRing(this, p1, p2, p3)) {
      GFrame::getToolBar().clearSelection();
      return false;
    }
    line = Vector<Point>(5);
    line[1] = p1;
    line[2] = p2;
    line[3] = p3;
  }
  return true;
}

void GJunction::moveRel(int _x, int _y)
{
  px+=_x;
  py+=_y;
  if (u!=-1)
  {
    if ((px-ux)*(px-ux)+(px-uy)*(px-uy)>(NEAR*NEAR))
    {
      if (uk)
      {
          Point a;
          line.insert( line.begin() + u, a );
          uk=false;
      }
      line.at(u).x=px;
      line.at(u).y=py;
    }
  }
}

bool GJunction::toSelect(int _x, int _y)
{
  if ((!source.expired())&&(!destination.expired()))
  {
     int i,j;
     int x,y,w,z,s,r;
     j=line.size()-1;
     double cang;
     for (i=0;i<j;++i)
     {
         w=line.at(i+1).x;
         z=line.at(i+1).y;
         x=line.at(i).x;
         y=line.at(i).y;

          cang=atan2f((float)(z-y),(float)(w-x));
          if(abs(atan2f((float)(_y-y),(float)(_x-x))-cang)<CANG)
          {
              s=(_y-y)*(_y-y)+(_x-x)*(_x-x);
              r=(z-y)*(z-y)+(w-x)*(w-x);

              if (s<r)
              {
                  s=s+(s/PROXY);
                  if (s<r)
                  {
                      uk=true;
                      ux=_x;
                      uy=_y;
                      px=_x;
                      py=_y;
                      u=i+1;
                  }
                  else
                  {
                      uk=false;
                      ux=_x;
                      uy=_y;
                      px=_x;
                      py=_y;
                      u=i+1;
                  }
                  return true;
              }
          }

     }
  }
  return false;
}

void GJunction::removePoint()
{
  if (uk) return;
  line.erase(line.begin()+u);
  
}

Var GJunction::getContent(bool full)
{
  Var ans;
  ans.newContainer();
  ans.getContainer()["model"]=getId();
  ans.getContainer()["id"]=setIndexer();
  ans.getContainer()["source"]=source.lock()->getIndexer();
  ans.getContainer()["destination"]=destination.lock()->getIndexer();  
  VarArray v;  
  for (unsigned i=1;i<line.size()-1;++i)
  {
    v.push_back(Var(line[i].x));
    v.push_back(Var(line[i].y));    
  }
  ans.getContainer()["points"]=v;
  ans.getContainer()["schema"]=content;
  return ans;
}

void GJunction::loadObject(Var& v,Map< int,Shared<GObject> > &map)
{
  setIndexer((int)v.getContainer()["id"].getInt());
  VarArray va=v.getContainer()["points"].getArray();
  line=Vector<Point>(2+va.size()/2);
  for (unsigned i=1;i<line.size()-1;++i)
  {
      Point p(va[(i-1)*2].getInt(),va[(i-1)*2+1].getInt());
      line[i]=p;
  }
  content=v.getContainer()["schema"];  
  int idx=(int)v.getContainer()["source"].getInt();
  source=map[idx];
  idx=(int)v.getContainer()["destination"].getInt();
  destination=map[idx];
}

bool GJunction::validate()
{
  if (source.expired()) return false;
  if (destination.expired()) return false;
  return true;
}

/**
* The Size Adapter, gets the maximum coordinates of the object drawing and adapt the
* declared size to fully contain it.
* @param size the size to adapt
*/
void GJunction::sizeAdapter(Size & size) const
{
	// We suppose that source and destination
	// are covered by the related drawing
	// so we are interested at the fixed points.
	for (unsigned i = 1; i<line.size() - 1; ++i)
	{
		size.x = VMAX(line[i].x, size.x);
		size.y = VMAX(line[i].y, size.y);
	}
	
}

const Weak<GObject> & GJunction::getSource()
{
  return source;
}

const Weak<GObject>& GJunction::getDestination()
{
  return destination;
}
