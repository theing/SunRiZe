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

#include "GPanel.h"
#include "GFrame.h"
#include "GJunction.h"

GPanel::GPanel(wxScrolledWindow * ctrl)
{
  this->ctrl = ctrl;
  setCurrentContext(mainContext); 
}

GPanel::~GPanel()
{
}


void GPanel::draw()
{
  Size s=ctrl->GetVirtualSize();
  Size s2 = currentContext->getContextSize();
  if ((s2.x > s.x) || (s2.y > s.y))
  {
	  ctrl->SetVirtualSize(s2);
  }
  wxClientDC dc(ctrl);
  ctrl->DoPrepareDC(dc);
  dc.Clear();
  currentContext->draw(dc);
}

void GPanel::mouseDrag(Point& p)
{  
	if (currentContext->moveObject(p.x - oldPoint.x, p.y - oldPoint.y))
	{
		GFrame::getInstance().refreshDraw();
		GFrame::getInstance().dataChanged();
	}
	oldPoint = p;
  }

void GPanel::mouseUp(Point& p)
{
  currentContext->releaseSelection();
  GFrame::getInstance().refreshDraw();
}

void GPanel::mouseDown(Point& p)
{
  oldPoint=p;
  // The shared pointer is evaluated
  if (GFrame::getToolBar().getSelection()) 
  {
      // Check if standalone
      if (GFrame::getToolBar().getSelection()->isJunction())
      {
        currentContext->querySelection(p.x,p.y);     
        // It must be a standalone object
        Shared<GObject> sel=currentContext->getSelection();
        if (!sel) return;
        if (sel->isJunction()) return;
        bool toplace=dynamic_cast<GJunction*>(GFrame::getToolBar().getSelection().get())->setEnd(sel);        
        if (toplace) {
          GFrame::getPanel().getCurrentContext().addItem(GFrame::getToolBar().getSelection());
          GFrame::getToolBar().clearSelection();
          if (currentContext->isMainContext()) GFrame::getSelector().refresh();
        }
        return;
      }
      else
      {
          dynamic_cast<GStandalone*>(GFrame::getToolBar().getSelection().get())->setPoint(p.x,p.y);
          GFrame::getPanel().getCurrentContext().addItem(GFrame::getToolBar().getSelection());
          GFrame::getToolBar().clearSelection();
          if (currentContext->isMainContext()) GFrame::getSelector().refresh();
          return;
      }
  }
  currentContext->querySelection(p.x,p.y);
  GFrame::getInstance().refreshDraw();
}
void GPanel::mouseDoubleClick(Point& p)
{
  currentContext->queryDoubleClick(p.x,p.y);
  GFrame::getInstance().refreshDraw();
  if (currentContext->isMainContext()) GFrame::getSelector().refresh();
}

void GPanel::keyDown(int keycode)
{
  switch(keycode)
  {
    case WXK_BACK:
      getCurrentContext().keyBackspace();
      return;
    case WXK_INSERT :
    case WXK_NUMPAD_INSERT:
      switchToPrimary();
      return;
    case WXK_DELETE :
    case WXK_NUMPAD_DELETE :
      getCurrentContext().keyRemove();
      return;
    return;
  
  }
  
}

void GPanel::switchToPrimary()
{
  Shared<GObject> item = currentContext->getSelection();
  if (!item) return;
  if (!item->isPrimary()) return;
  GPrimary * primary=dynamic_cast<GPrimary*>(item.get());
  if (!primary->getContext()) primary->newContext();
  currentContext=primary->getContext();
  GFrame::getToolBar().setToolBox(1);
  GFrame::getInstance().refreshDraw();
  GFrame::getSelector().refresh();
}
