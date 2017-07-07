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

#include "STransition.h"
#include "TransitionDialogImplementation.h"
#include "GStandalone.h"
#include "SInitState.h"
#include "SState.h"
#include "SCondition.h"
#include "math.h"
#include "Glob.h"


static wxBitmap question;

static const char * question_xpm[] = {
"                ",
"                ",
"                ",
"     ......     ",
"   .........    ",
"  ...........   ",
"  ...    .....  ",
"  .        ...  ",
"           ...  ",
"           ...  ",
"          ...   ",
"         ....   ",
"        ....    ",
"       ....     ",
"       ...      ",
"      ...       ",
"      ...       ",
"      ...       ",
"      ...       ",
"                ",
"                ",
"      ...       ",
"      ...       ",
"      ...       ",
"      ...       ",
"                ",
"                ",
"                ",
"                ",
"                "};



/**
 * @brief Since some operating system does not support XPM ...
 */
void xpmConv() 
{
  unsigned short bitRows[30];
  for (int i=0;i<30;++i)
  {
    unsigned short br(0);
    for (int j=0;j<16;++j)
    {
        if (question_xpm[i][j]=='.') br|=0x8000;
        br >>=1;
    }
    bitRows[i]=br;
  }
  question=wxBitmap((const char *)bitRows,16,30,1);
}



STransition::STransition()
{
  if (!question.IsOk()) xpmConv();
  content.getContainer()["event"]=0;
  content.getContainer()["token"]="";
  content.getContainer()["condition"]="";
  content.getContainer()["time"]="";
  content.getContainer()["follower"]=false;
  content.getContainer()["action"]="";
  content.getContainer()["guard"]="";
}

STransition::~STransition()
{
}

void STransition::edit()
{
  TransitionDialogImplementation *tdi=new TransitionDialogImplementation(nullptr,content,source);
  int ret =tdi->ShowModal();
  if (ret==wxID_OK) content=tdi->getVar();
  delete tdi; 
}



void STransition::draw(wxDC& deviceContext, bool isSelected)
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
        unsigned len=0;
        for (i=0;i<j;++i)
        {
            dc.line(line[i],line[i+1],penSize);
            len+=sqrt((line[i+1].x-line[i].x)*(line[i+1].x-line[i].x)+(line[i+1].y-line[i].y)*(line[i+1].y-line[i].y));
        }
        
        // Arrow
        double angle;
        a=line[j];
        angle = atan2(a.y-line[j-1].y,a.x-line[j-1].x);
        Point b(a.x-(int)(15*cos(angle-.3)),a.y-(int)(15*sin(angle-.3)));
        dc.line(a,b,penSize);
        Point c(a.x-(int)(15*cos(angle+.3)),a.y-(int)(15*sin(angle+.3)));
        dc.line(a,c,penSize);
        
        // Check the middle
        
        // Nothing must be shown if source is the Init State
        if (Glob::equal(source.lock()->getId(),SInitState::id)) return;
        
        len/=2;
        if (len<1) return;
        
        unsigned prog=0;
        for (i=0;i<j;++i)
        {
            dc.line(line[i],line[i+1],penSize);
            unsigned rel=sqrt((line[i+1].x-line[i].x)*(line[i+1].x-line[i].x)+(line[i+1].y-line[i].y)*(line[i+1].y-line[i].y));
            prog+=rel;
            if ((prog>=len)&&(rel>2))
            {
                double p=(double)(rel-prog+len)/(double)rel;
                double dx=(double)(line[i+1].x-line[i].x)*p;
                double dy=(double)(line[i+1].y-line[i].y)*p;
                double angle=atan2(abs(line[i+1].x-line[i].x),(line[i+1].y-line[i].y));
                if (line[i+1].x<=line[i].x) angle=2*M_PI-angle;
                if ((angle>M_PI/2)&&(angle<=M_PI*3/2))
                {
                  dx-=cos(angle)*30;
                  dy+=sin(angle)*30;                                    
                }
                else
                {
                  dx+=cos(angle)*30;
                  dy-=sin(angle)*30;                  
                }

                // Nothing must be shown if source is the Init State
                if (Glob::equal(source.lock()->getId(),SCondition::id))
                {
                   dc.text(String("( ")+content.getContainer()["guard"].getString()+" )",Point(line[i].x+(int)dx-10,line[i].y+(int)dy),0);                
                }
                else
                {                  
                  int ind=(int) content.getContainer()["event"].getInt();
                  switch(ind)
                  {
                    case 0:
                      drawCondition(dc,line[i].x+(int)dx,line[i].y+(int)dy);
                      dc.text(String("( ")+content.getContainer()["condition"].getString()+" )",Point(line[i].x+(int)dx+15,line[i].y+(int)dy),0);
                      break;
                    case 1:
                      drawTime(dc,line[i].x+(int)dx,line[i].y+(int)dy);
                      dc.text(content.getContainer()["time"].getString()+" ms",Point(line[i].x+(int)dx+30,line[i].y+(int)dy),0);
                      break;
                    case 2:
                      drawToken(dc,line[i].x+(int)dx,line[i].y+(int)dy);
                      dc.text(content.getContainer()["token"].getString(),Point(line[i].x+(int)dx+25,line[i].y+(int)dy),0);
                      break;                  
                  }
                }
                break;
                
                
            } 
        }
        
        
    }
}


void STransition::drawTime(GDrawHelper &dc,int x, int y)
{
  dc.fillCircle(x,y,20,5,0xffffff);
  dc.line(Point(x,y),Point(x,y-15),7);
  dc.line(Point(x,y),Point(x+5,y+5),7);  
}

void STransition::drawToken(GDrawHelper &dc,int x, int y)
{
  dc.fillCircle(x+7,y-5,7,2,0x000000);
  dc.line(Point(x-10,y-15),Point(x-10,y+15),10);  
}


void STransition::drawCondition(GDrawHelper &dc,int x, int y)
{  
  dc.getDevice().DrawBitmap(question,Point(x-8,y-15));
}
