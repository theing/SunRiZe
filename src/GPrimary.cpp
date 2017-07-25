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

#include "GPrimary.h"
#include "GContext.h"

GPrimary::GPrimary()
{
}

GPrimary::~GPrimary()
{
}

bool GPrimary::isPrimary() const
{
  return true;
}

GContext * GPrimary::getContext()
{
  return context.get();
}

void GPrimary::newContext()
{
  context=Unique<GContext>(new GContext(*this));
}

Var GPrimary::getContent(bool full)
{
  Var ans=GStandalone::getContent(full);
  if (context) ans.getContainer()["context"]=context->collect(full);
  return ans;
}

void GPrimary::loadObject(Var& v,Map< int,Shared<GObject> > &map)
{
  GStandalone::loadObject(v,map);
  auto i=v.getContainer().find("context");
  if (i==v.getContainer().end()) return;
  context=Unique<GContext>(new GContext(*this));
  context->loadCollection(i->second);
}
