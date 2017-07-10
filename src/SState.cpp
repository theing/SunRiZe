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

#include "SState.h"
#include "StateDialogImplementation.h"

SState::SState()
{
  content.getContainer()["name"]="State";
  content.getContainer()["entryaction"]="";
  content.getContainer()["exitaction"]="";
  content.getContainer()["doaction"]="";
}

SState::~SState()
{
  
}

Point SState::borderPoint(Point p)
{
  unsigned height=40;
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

bool SState::toSelect(int x, int y)
{
if (
  (x>=center.x-(int)width/2) && 
  (x<=center.x+(int)width/2) && 
  (y>=center.y-(int)20) && 
  (y<=center.y+(int)20)
  ) return true;
  return false;
}

void SState::edit()
{
  StateDialogImplementation *sdi=new StateDialogImplementation(nullptr,content);
  int ret =sdi->ShowModal();
  if (ret==wxID_OK) content=sdi->getVar();
  delete sdi;
}

void SState::draw(wxDC& deviceContext, bool isSelected)
{
  GDrawHelper dc(deviceContext);
  Size size(dc.textSize(content.getContainer()["name"].getString(),1));
  width=20+size.GetWidth();
  unsigned height=40;
  unsigned top=center.y-height/2;
  unsigned left=center.x-width/2;
  
  
  if (isSelected) {
      dc.fillRoundRect(Rect(left,top,width,height),10,5,0x00ffff);
    
  } else {
      dc.fillRoundRect(Rect(left,top,width,height),10,2,0x00ffff);
  }
  
  String s;
  dc.text(content.getContainer()["name"].getString(),Rect(left,top,width,40),1);
}

void SState::sizeAdapter(Size & size) const
{
	size.x = VMAX(size.x, center.x + width / 2);
	size.y = VMAX(size.y, center.y + 20);
}
