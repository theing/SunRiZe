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

#include "SModule.h"
#include "SInitState.h"
#include "ModuleDialogImplementation.h"
#include "GContext.h"

SModule::SModule()
{  
  content.getContainer()["name"]="Module";
  content.getContainer()["hasinit"]=true;
  content.getContainer()["comment"]="";
  content.getContainer()["initpriority"]=5;
  Var v;
  v.newArray();
  content.getContainer()["attributes"]=v;
  content.getContainer()["operations"]=v;
  content.getContainer()["tokens"]=v; 
}

SModule::~SModule()
{
}


Point SModule::borderPoint(Point p)
{
    double dx= p.x-center.x;
		double dy= p.y-center.y;
		if ((dx*dx)+(dy*dy)<10.0) return center; 
		
		if ((int)dx!=0)
		{
			double y=((double)(width/2))*(dy/abs(dx));
			// Use height as a guide
			if (abs(y)>height/2)
			{
				y=((double)(height/2))*(dx/abs(dy));
				return Point((int)(y+center.x) , (int) (SIGNUM(dy)*(height/2)+center.y));
			}
			return Point( (int) (SIGNUM(dx)*(width/2)+center.x), (int) (y+center.y));
		}

		if (dy>0) return Point((int) center.x,(int)(center.y+height/2) );
		return Point((int) center.x,(int)(center.y-height/2) );			
}


bool SModule::toSelect(int x, int y)
{
  if (
  (x>=center.x-(int)width/2) && 
  (x<=center.x+(int)width/2) && 
  (y>=center.y-(int)height/2) && 
  (y<=center.y+(int)height/2)
  ) return true;
  return false;
}

void SModule::draw(wxDC& deviceContext, bool isSelected)
{
  GDrawHelper dc(deviceContext);
  unsigned i; 
  Size size;
  String s;
  size=dc.textSize(content.getContainer()["name"].getString(),1);
  width=130;
  if (width<size.GetWidth()+20) width=size.GetWidth()+20;
  
  unsigned as=content.getContainer()["attributes"].getArray().size();
  unsigned os=content.getContainer()["operations"].getArray().size();
  unsigned ts=content.getContainer()["tokens"].getArray().size();
  height=100+(as+os+ts)*20; //Header+Attributes+Operations+Tokens
  for (i=0;i<as;++i) {
    Var &v=content.getContainer()["attributes"].getArray()[i];
    s=(v.getContainer()["visibility"].getInt()==0) ?  "-": "+" ;
    s+=v.getContainer()["name"].getString();
    s+=":";
    s+=v.getContainer()["type"].getString();
    size=dc.textSize(s,0);
    if (width<size.GetWidth()+20) width=size.GetWidth()+20;

  } 
  for (i=0;i<os;++i) {    
    Var &v=content.getContainer()["operations"].getArray()[i];
    s=(v.getContainer()["visibility"].getInt()==0) ?  "-": "+" ;
    s+=v.getContainer()["name"].getString();
    s+="():";
    s+=v.getContainer()["type"].getString();
    size=dc.textSize(s,0);
    if (width<size.GetWidth()+20) width=size.GetWidth()+20;
  } 
  
  for (i=0;i<ts;++i) {
    Var &v=content.getContainer()["tokens"].getArray()[i];
    s=((v.getContainer()["type"].getInt()==0) ? "(*) " : "($) ");
    s+=v.getContainer()["name"].getString();
    size=dc.textSize(s,0);
    if (width<size.GetWidth()+20) width=size.GetWidth()+20;
  } 
  

  unsigned top=center.y-height/2;
  unsigned left=center.x-width/2;
  
  if (isSelected) {
      dc.fillRect(Rect(left,top,width,height),5,0x00ffff);
    
  } else {
      dc.fillRect(Rect(left,top,width,height),2,0x00ffff);
  }
  
  int p=top;
  dc.text(content.getContainer()["name"].getString(),Rect(left,p,width,40),1);
  p+=40;
  dc.line(Point(left,p),Point(left+width,p),2);
  p+=10;
  for (i=0;i<as;++i) {
    Var &v=content.getContainer()["attributes"].getArray()[i];
    s=(v.getContainer()["visibility"].getInt()==0) ?  "-": "+" ;
    s+=v.getContainer()["name"].getString();
    s+=":";
    s+=v.getContainer()["type"].getString();
    dc.text(s,Rect(left,p,width,20),0,GDrawHelper::ALIGN_LEFT,10);
    p+=20;
  } 
  p+=10;
  dc.line(Point(left,p),Point(left+width,p),2);
  p+=10;
  for (i=0;i<os;++i) {
    Var &v=content.getContainer()["operations"].getArray()[i];
    s=(v.getContainer()["visibility"].getInt()==0) ?  "-": "+" ;
    s+=v.getContainer()["name"].getString();
    s+="():";
    s+=v.getContainer()["type"].getString();
    dc.text(s,Rect(left,p,width,20),0,GDrawHelper::ALIGN_LEFT,10);
    p+=20;
  } 
  p+=10;
  dc.line(Point(left,p),Point(left+width,p),2);
  p+=10;
  for (i=0;i<ts;++i) {
    Var &v=content.getContainer()["tokens"].getArray()[i];
    s=((v.getContainer()["type"].getInt()==0) ? "(*) " : "($) ");
    s+=v.getContainer()["name"].getString();
    dc.text(s,Rect(left,p,width,20),0,GDrawHelper::ALIGN_LEFT,10);
    p+=20;
  } 
}

void SModule::edit()
{
  ModuleDialogImplementation *mdi=new ModuleDialogImplementation(nullptr,content);
  int ret =mdi->ShowModal();
  if (ret==wxID_OK) content=mdi->getVar();
  delete mdi;  
}

String SModule::getString()
{
  return content.getContainer()["name"].getString();
}

void SModule::newContext()
{
    GPrimary::newContext();
    GContext * context= getContext();
    SInitState * object=new SInitState();
    object->setPoint(50,50);
    Shared<GObject> so(object);
    context->addItem(so);    
}

void SModule::sizeAdapter(Size & size) const
{
	size.x = VMAX(size.x,center.x + width / 2);
	size.y = VMAX(size.y,center.y + height / 2);
}

bool SModule::autoRing(GJunction * j, Point &p1, Point &p2, Point &p3)
{
  return false;
}

bool SModule::accept(GJunction * j, bool dirIn)
{
  return true;
}
