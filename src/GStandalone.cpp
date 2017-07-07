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

#include "GStandalone.h"
#include "Commons.h"

GStandalone::GStandalone()
{
}

GStandalone::~GStandalone()
{
}


bool GStandalone::isJunction() const
{
  return false;
}

bool GStandalone::isPrimary() const
{
  return false;
}
Point GStandalone::getPoint() const
{
  return center;
}

void GStandalone::setPoint(int x, int y)
{
  center=Point(x,y);
}

void GStandalone::moveRel(int x, int y)
{
    center.x+=x;
    center.y+=y;
}

Var GStandalone::getContent(bool full)
{
  Var ans;
  ans.newContainer();
  ans.getContainer()["model"]=getId();
  ans.getContainer()["id"]=setIndexer();
  VarArray v;
  v.push_back(Var(center.x));
  v.push_back(Var(center.y));
  ans.getContainer()["point"]=v;
  ans.getContainer()["schema"]=content;
  return ans;
}

void GStandalone::loadObject(Var& v,Map< int,Shared<GObject> > &map)
{
  setIndexer((int)v.getContainer()["id"].getInt());
  VarArray va=v.getContainer()["point"].getArray();
  center=Point(va[0].getInt(),va[1].getInt());
  content=v.getContainer()["schema"];
}



	
