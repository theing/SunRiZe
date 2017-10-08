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

#include <iostream>
#include <fstream>
#include "GFrame.h"
#include "GDrawHelper.h"
#include "Factory.h"
#include "JSONParser.h"
#include "MBox.h"
#include "GenCode.h"
#include "Glob.h"
#include "Icon.xpm"
#include "AboutBox.h"
#include <wx/dcmemory.h>
#include "Text.h"

#ifdef LINUX_PORTING
#include <unistd.h>
#endif

#ifdef WINDOWS_PORTING
#define PATH_MAX MAX_PATH
#endif


GFrame * GFrame::instance = nullptr;


GFrame::GFrame( wxWindow* parent )
:
MyFrame1( parent ),toolBar(this,m_toolBar1),panel(m_panel2),selector(primaryList)
{
  // The factory must be initialized before the others
  SetIcon(Icon_xpm);
  toolBar.setToolBox(0);
  changed=false;
  font[0] = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
  font[1] = wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
  font[2] = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
  font[3] = wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);  
  //selector.refresh();
  menuFile->Enable(menuFile->FindItem (wxT("Save")),false);
  menuFile->Enable(menuFile->FindItem (wxT("Reload")),false);
  menuGenerate->Enable(menuGenerate->FindItem (wxT("Generate Code")),false);
  m_toolBar1->Enable(false);
  changed = false;
  ctrlPressed = false;
}

void GFrame::toolClicked( wxCommandEvent& event )
{
  toolBar.clicked(event.GetId());
}

void GFrame::refreshDraw()
{
  m_panel2->Refresh(false);
}

void GFrame::panelKeyDown(wxKeyEvent& event)
{
  int kcode = event.GetKeyCode();
  if (kcode == WXK_CONTROL) {
    ctrlPressed = true;
    return;
  }
  if (ctrlPressed) {
    if ((kcode >= 'A') && (kcode <= 'Z'))
      kcode -= 'A' - 1;
  }
  panel.keyDown(kcode);
}

void GFrame::panelKeyUp(wxKeyEvent& event)
{
  int kcode = event.GetKeyCode();
  if (kcode == WXK_CONTROL) {
    ctrlPressed = false;
    return;
  }
}

void GFrame::panelMouseEvent(wxMouseEvent& event)
{
  // Down
  m_panel2->SetFocus();
  if (event.ButtonDown(wxMOUSE_BTN_LEFT)) {
    wxClientDC dc(m_panel2);
	m_panel2->PrepareDC(dc);
	Point p=event.GetLogicalPosition(dc);
    panel.mouseDown(p);
  }
  else if (event.ButtonDClick(wxMOUSE_BTN_LEFT)) {
    wxClientDC dc(m_panel2);
	m_panel2->PrepareDC(dc);
	Point p=event.GetLogicalPosition(dc);
    panel.mouseDoubleClick(p);
  }
  else if (event.ButtonUp(wxMOUSE_BTN_LEFT)) {
    wxClientDC dc(m_panel2);
	m_panel2->PrepareDC(dc);
    Point p=event.GetLogicalPosition(dc);
    panel.mouseUp(p);
  }
  else if (event.Dragging()) {
    wxClientDC dc(m_panel2);
	m_panel2->PrepareDC(dc);
	Point p=event.GetLogicalPosition(dc);
    panel.mouseDrag(p);
  }

  
}
  
void GFrame::panelPaintEvent( wxPaintEvent& event )
{
  panel.draw();
}

void GFrame::itemSelected(wxCommandEvent& event)
{
  selector.selected();
}

void GFrame::saveMenuSelection(wxCommandEvent& event)
{
  clearIndexer();
  Var v=panel.getMainContext().collect(true);
  String realPath = Glob::composePath(projectPath, "model.srz");
  try 
  {
    if (!Glob::makeBackup(realPath)) {
      if (!MBox::yesno("Cannot make a backup of the old model, continue ?"))
      {
        return;
      }
    }
    Text::writeFile(realPath, JSONParser::toString(v));
  } 
  catch (Exception & e)
  {
    String s = "Error saving the model : ";
    s += e.what();
    MBox::error(s);
  }
  menuFile->Enable(menuFile->FindItem (wxT("Reload")),true);
  menuFile->Enable(menuFile->FindItem (wxT("Save")),false);
  m_toolBar1->Enable(true);
  changed=false;
}


void GFrame::reloadMenuSelection(wxCommandEvent& event)
{  
  String realPath = Glob::composePath(projectPath, "model.srz");
  if (!Glob::fileExists(realPath))
  {
    MBox::error("A previous saved model does not exists.");
    return;
  }

  if (!MBox::yesno("WARNING: this operation will destroy the unsaved model\nto reload the previous version.\nAre you sure to proceed ?"))
  {
    return;
  }

  try {
    String content=Text::readFile(realPath);
    JSONParser json;
    Var v;
    try {
      v = json.fromString(content);
      if (!(v.isArray())) throw std::exception();
    }
    catch (std::exception &e)
    {
      MBox::error("The old model is not valid");
      return;
    }
    // Destroy and do
    panel.getMainContext().loadCollection(v);
    refreshDraw();
    selector.refresh();
    changed = false;
    menuFile->Enable(menuFile->FindItem(wxT("Save")), false);
  }
  catch (Exception &e)
  {
    MBox::error("Cannot read the previous model.");
    return;
  }
}


void GFrame::generateOnMenuSelection(wxCommandEvent& event)
{
  clearIndexer();
  GenCode gc;
  GenCode::init(gc);  
  Var v=panel.getMainContext().collect(false);
  if (gc.generateCode(v)) 
    gc.writeFiles();
}

void GFrame::projectOnMenuSelection(wxCommandEvent& event)
{
	projectPath=MBox::projectDialog();
  if (projectPath!="")
  {
    // Check the existence of the model
    if (!Glob::folderExists(projectPath))
    {
      MBox::error("Cannot access this folder");
      return;
    }
    String realPath = Glob::composePath(projectPath, "model.srz");
    if (Glob::fileExists(realPath))
    {
      String content = Text::readFile(realPath);
      JSONParser json;
      Var v;
      try {
        v = json.fromString(content);
        if (!(v.isArray())) throw std::exception();
      }
      catch (std::exception &e)
      {
        MBox::error("The old model is not valid");
        return;
      }
      panel.getMainContext().loadCollection(v);
      refreshDraw();
      menuFile->Enable(menuFile->FindItem (wxT("Reload")),true);
    }
    else
    {
      bool yesno=MBox::yesno("The model file does not exists into the specified path, do you want to create a new one ?");
	    if (!yesno) {
		    return;
	    }
      menuFile->Enable(menuFile->FindItem(wxT("Save")),true);
    }
    menuGenerate->Enable(menuGenerate->FindItem (wxT("Generate Code")),true);   
  	m_toolBar1->Enable(true);
  }
}

void GFrame::exitOnMenuSelection(wxCommandEvent& event)
{
  wxCloseEvent e; // fake
  onCloseEvent(e);
}

void GFrame::aboutMenuSelection(wxCommandEvent& event)
{
  AboutBox ab(this);
  ab.ShowModal();
}

void GFrame::dataChanged()
{
    if (changed) return;
    changed=true;
    menuFile->Enable(menuFile->FindItem (wxT("Save")),true);
}

void GFrame::onCloseEvent(wxCloseEvent& event)
{
  if (changed)
  {
    int answ=MBox::yesnocancel("The model has changed after the last save.\nDo you want to save the model before leaving ?");
    if (answ==1) // YES
    {
      wxCommandEvent event; // fake
      saveMenuSelection(event);
    }
    if (answ<2) Destroy();
    // DOES NOTHING
  }
  else Destroy();
}
