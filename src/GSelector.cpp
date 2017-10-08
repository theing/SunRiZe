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

#include "GSelector.h"
#include "GFrame.h"

GSelector::GSelector(wxListBox *lb):listBox(lb)
{
  listBox->Clear();  
  listBox->Append(wxT("(Main)"));  
}

GSelector::~GSelector()
{
}

void GSelector::refresh()
{
  listBox->Clear();  
  // This does not have data
  listBox->Append(wxT("(Main)"));
  for (Shared<GObject> & item : GFrame::getPanel().getMainContext().contextList())
  {
    if ((item)&&(item->isPrimary()))
    {         
      GPrimary * primary=dynamic_cast<GPrimary*>(item.get());
      if (primary->getContext())
      {
        GSelector::Container *cont = new GSelector::Container();
        cont->content=item;
        listBox->Append(primary->getString(),cont);
      }
    }
  }
}

void GSelector::selected()
{
  if (!listBox->HasClientObjectData()) return;
  int i=listBox->GetSelection();
  if (i<0) return;
  GFrame::getToolBar().clearSelection();
  GSelector::Container *cont=dynamic_cast<GSelector::Container*>(listBox->GetClientObject(i));
  if (cont)
  {
    // primary 
    if (!(cont->content.expired()))
    {      
      GPrimary * primary=dynamic_cast<GPrimary *>((cont->content).lock().get());
      if (primary->getContext())
      {
        GFrame::getPanel().clearHistory();
        GFrame::getPanel().setCurrentContext( *(primary->getContext()) );
        GFrame::getToolBar().setToolBox(1);
        GFrame::getInstance().refreshDraw();                
      }
    }
  }
  else
  {
    // main
    GFrame::getPanel().clearHistory();
    GFrame::getPanel().setCurrentContext(GFrame::getPanel().getMainContext());
    GFrame::getToolBar().setToolBox(0);
    GFrame::getInstance().refreshDraw();
  }
  
}
