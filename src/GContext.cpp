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

#include "GContext.h"
#include "GFrame.h"
#include "GJunction.h"
#include "MBox.h"

GContext::GContext(GPrimary & p):parent(&p)
{
  selected=-1;
}

GContext::GContext() : parent(nullptr)
{
  selected=-1;
}

GContext::~GContext()
{
}

void GContext::addItem(Shared<GObject> & o)
{
  GFrame::getInstance().dataChanged();
	content.push_back(o);
  selected=-1;
}

void GContext::releaseSelection()
{
  selected=-1;
}

void GContext::querySelection(int x, int y)
{
  for (int i=0; i<(int)content.size() ; ++i ) {
    if (content[i]->toSelect(x, y))
    {
      selected=i;
      return;
    }
  }
  selected=-1;
}


bool GContext::moveObject(int i, int j)
{    
    if (selected>=0) {
        content[selected]->moveRel(i, j);
        GFrame::getInstance().dataChanged();
        return true;
		}
		return false;

}

void GContext::queryDoubleClick(int x, int y)
{
  selected=-1;
  for (int i=0; i<(int)content.size() ; ++i ) {
    if (content[i]->toSelect(x, y))
    {
	    GFrame::getInstance().dataChanged();
      content[i]->edit();
      break;
    }
  }
}

void GContext::keyBackspace()
{   
		if (selected<0) return;
    if (!(content[selected]->isJunction())) return ;
    dynamic_cast<GJunction*>(content[selected].get())->removePoint(); 
    GFrame::getInstance().dataChanged();
    selected=-1;
    GFrame::getInstance().refreshDraw();
}


void GContext::keyRemove()
{
  if (MBox::yesno("Are you sure to delete this object ?"))
  {
    if (selected<0) return;
    if (!(content[selected]->isRemoveable())) return;
    content.erase(content.begin()+selected);
    for (auto i=content.begin();i!=content.end();)
    {
      if ((*i)->isJunction())
      {
        GJunction * junction=dynamic_cast<GJunction *>((*i).get());
        if (!junction->validate()) {
          content.erase(i);
          continue;
        }
      }
      ++i;
    }
    GFrame::getInstance().dataChanged();
    GFrame::getSelector().refresh();    
  }
  selected=-1;  
  GFrame::getInstance().refreshDraw();
}


void GContext::draw(wxDC& deviceContext)
{
  for (int i=0; i<(int)content.size() ; ++i ) {    
    content[i]->draw(deviceContext,(i==selected));
  }
}

Shared<GObject>  GContext::getSelection()
{
   if (selected<0) return Shared<GObject>();
   return content[selected];
}

bool GContext::isMainContext() const
{
  return (!parent);
}

Var GContext::collect(bool full)
{
  // To ensure junctions are properly indexed
  // standalone must be collected before.
  selected=-1;
  Var array;
  array.newArray();
  for (auto item:content)
  {
    if (!item->isJunction())
    array.getArray().push_back(item->getContent(full));
  }
  for (auto item:content)
  {
    if (item->isJunction())
    array.getArray().push_back(item->getContent(full));
  }
  return array;
}


void GContext::loadCollection(Var& v)
{
  selected=-1;
  content.clear();
  Map<int,Shared<GObject> > map;
  VarArray va=v.getArray();
  // Collect objects and index
  for (Var & item : va)
  {
    GObject * object=Factory::createObject(item.getContainer()["model"].getString().c_str());
    if (object)
    {
      Shared<GObject> gobj(object);
      int idx=(int)item.getContainer()["id"].getInt();
      map[idx]=gobj;
    }
  }
  Shared<GObject> go;
  // Create context
  for (Var & item : va)
  {
    int idx=(int)item.getContainer()["id"].getInt();
    go=map[idx];
    go->loadObject(item,map);
    content.push_back(go);    
  }
}
