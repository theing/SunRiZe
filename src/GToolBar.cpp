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

#include "GToolBar.h"
#include "GFrame.h"
#include "Glob.h"

GToolBar::GToolBar(wxFrame *fr,wxToolBar * tb)
{
  toolBar=tb;
  frame=fr;
  selectedItem=-1;
  selection=nullptr;
}

GToolBar::~GToolBar()
{
  for(auto iter:items) {
    int i=iter.first;
    frame->Disconnect( i, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GFrame::toolClicked ) );
  }
}

void GToolBar::addItem(const char *xpm[],const char * type)
{
  wxToolBarToolBase* tb;
  tb=toolBar->AddCheckTool( wxID_ANY, wxT("tool"), wxBitmap(xpm));
  frame->Connect( tb->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GFrame::toolClicked ) );
  items[tb->GetId()]=type;
}


void GToolBar::setToolBox(unsigned tool)
{
  toolBar->ClearTools();
  Factory::createToolbar(*this,tool);
  toolBar->Realize(); 	
}

void GToolBar::clicked(int id)
{
  for(auto iter:items) {
    int i=iter.first;
    toolBar->ToggleTool(i,false);    
    if (i==id) {
      if (selectedItem==i) {
        toolBar->ToggleTool(i,false);
        selectedItem=-1;        
        selection=nullptr;
      }
      else {  
        toolBar->ToggleTool(i,true);
        selectedItem=i;
        selection=Shared<GObject>(Factory::createObject(iter.second));
      }
    }
  }
}

Shared<GObject> & GToolBar::getSelection()
{
  return selection;
}

void GToolBar::setSelection(Shared<GObject>& obj)
{
  clearSelection();
  selection = obj;
}


void GToolBar::clearSelection()
{
  for(auto iter:items) {
    int i=iter.first;
    toolBar->ToggleTool(i,false);    
  }
  selectedItem = -1;
  selection=nullptr;
}
