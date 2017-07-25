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

#include "GDrawHelper.h"
#include "GFrame.h"


GDrawHelper::GDrawHelper(wxDC & dev)
{
  device=&dev;
}

GDrawHelper::~GDrawHelper()
{
}

void GDrawHelper::fillRect(Rect r, int size, Color color)
{
  wxBrush brush(wxColour(color), (color==0xffffff ? wxBRUSHSTYLE_TRANSPARENT : wxBRUSHSTYLE_SOLID )  );
  device->SetBrush(brush);
  wxPen pen=*wxBLACK_PEN;
  pen.SetWidth(size);
  device->SetPen(pen);
  device->DrawRectangle(r);  
}

void GDrawHelper::text(String txt, Point p, int font)
{
  wxPen pen=*wxBLACK_PEN;
  pen.SetWidth(1);
  device->SetPen(pen);
  device->SetFont(GFrame::getInstance().getFont(font));
  device->DrawText(txt,p.x,p.y);
}

Size GDrawHelper::textSize(String txt,int font)
{
  device->SetFont(GFrame::getInstance().getFont(font));
  return device->GetTextExtent(txt);
}

void GDrawHelper::text(String txt, Rect r, int font, Alignment align, int margin)
{
  Size s=textSize(txt,font);
  
  switch(align) {
    case ALIGN_LEFT :
    {
        int td  = (r.height-s.GetHeight())/2;        
        int ld = margin;
        text(txt,Point(r.x+ld,r.y+td),font);
    }
    break;
    case ALIGN_RIGHT :
    {
        int td  = (r.height-s.GetHeight())/2;        
        int ld = r.width-s.GetWidth()-margin;
        text(txt,Point(r.x+ld,r.y+td),font);
    }
    break;
    case ALIGN_CENTER :
    default:
    {
        // Top distance
        int td  = (r.height-s.GetHeight())/2;        
        int ld = (r.width-s.GetWidth())/2;
        text(txt,Point(r.x+ld,r.y+td),font);        
    }
    break;
  }
  
  
}
void GDrawHelper::line(Point p1, Point p2,unsigned size,bool dashed)
{
  wxPen pen;
  if (dashed) pen=*wxBLACK_DASHED_PEN;
  else pen=*wxBLACK_PEN;
  pen.SetWidth(size);
  device->SetPen(pen);
  device->DrawLine(p1,p2);
}

void GDrawHelper::fillCircle(int x, int y, int radius, int size, Color color)
{
  wxBrush brush(wxColour(color), (color==0xffffff ? wxBRUSHSTYLE_TRANSPARENT : wxBRUSHSTYLE_SOLID )  );
  device->SetBrush(brush);
  wxPen pen=*wxBLACK_PEN;
  pen.SetWidth(size);
  device->SetPen(pen);
  device->DrawCircle(x,y,radius);
}

void GDrawHelper::fillRoundRect(Rect r, int radius,int size, Color color)
{
  wxBrush brush(wxColour(color), (color==0xffffff ? wxBRUSHSTYLE_TRANSPARENT : wxBRUSHSTYLE_SOLID )  );
  device->SetBrush(brush);
  wxPen pen=*wxBLACK_PEN;
  pen.SetWidth(size);
  device->SetPen(pen);
  device->DrawRoundedRectangle(r,radius); 
}
void GDrawHelper::fillPolygon(int n, const Point p [], int size, Color color)
{
  wxBrush brush(wxColour(color), (color==0xffffff ? wxBRUSHSTYLE_TRANSPARENT : wxBRUSHSTYLE_SOLID )  );
  device->SetBrush(brush);
  wxPen pen=*wxBLACK_PEN;
  pen.SetWidth(size);
  device->SetPen(pen);
  device->DrawPolygon(n,p);
}
