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

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "GFrame.h"
#include "GDrawHelper.h"
#include "Factory.h"
#include "JSONParser.h"
#include "MBox.h"
#include "GenCode.h"
#include "Glob.h"
#include "Icon.xpm"
#include "AboutBox.h"

GFrame * GFrame::instance = nullptr;

GFrame::GFrame( wxWindow* parent )
:
MyFrame1( parent ),toolBar(this,m_toolBar1),selector(primaryList)
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
  char path[PATH_MAX];
  getcwd(path,PATH_MAX);
  currentPath=path;
}

void GFrame::toolClicked( wxCommandEvent& event )
{
  toolBar.clicked(event.GetId());
}

void GFrame::refreshDraw()
{
  m_panel2->Refresh();
}

void GFrame::panelKeyDown(wxKeyEvent& event)
{
  panel.keyDown(event.GetKeyCode());
}

void GFrame::panelKeyUp(wxKeyEvent& event)
{
}

void GFrame::panelMouseEvent(wxMouseEvent& event)
{
  // Down
  m_panel2->SetFocus();
  if (event.ButtonDown(wxMOUSE_BTN_LEFT)) {
    wxClientDC dc(m_panel2);
    Point p=event.GetLogicalPosition(dc);
    panel.mouseDown(p);
  }
  else if (event.ButtonDClick(wxMOUSE_BTN_LEFT)) {
    wxClientDC dc(m_panel2);
    Point p=event.GetLogicalPosition(dc);
    panel.mouseDoubleClick(p);
  }
  else if (event.ButtonUp(wxMOUSE_BTN_LEFT)) {
    wxClientDC dc(m_panel2);
    Point p=event.GetLogicalPosition(dc);
    panel.mouseUp(p);
  }
  else if (event.Dragging()) {
    wxClientDC dc(m_panel2);
    Point p=event.GetLogicalPosition(dc);
    panel.mouseDrag(p);
  }

  
}
  
void GFrame::panelPaintEvent( wxPaintEvent& event )
{
  wxClientDC dc(m_panel2);
  panel.draw(dc);
}

void GFrame::itemSelected(wxCommandEvent& event)
{
  selector.selected();
}

void GFrame::saveMenuSelection(wxCommandEvent& event)
{
  clearIndexer();
  Var v=panel.getMainContext().collect(true);
  std::ofstream outFile;
  outFile.open(Glob::composePath(projectPath,"model.json"));  
  outFile << JSONParser::toString(v);
  outFile.close();
  if (outFile.fail())
  {
    MBox::error("Write error");
  }
  menuFile->Enable(menuFile->FindItem (wxT("Reload")),true);
  menuFile->Enable(menuFile->FindItem (wxT("Save")),false);
  changed=false;
}


void GFrame::reloadMenuSelection(wxCommandEvent& event)
{  
  std::ifstream inFile;
  JSONParser json;
  inFile.open(Glob::composePath(projectPath,"model.json"));
  std::stringstream buffer;
  buffer << inFile.rdbuf();
  inFile.close();
  if (inFile.fail())
  {
    MBox::error("Read error");
    return;
  }
  Var v;
  try {
  v = json.fromString(buffer.str());
  } 
  catch(std::exception &e) 
  {    
    MBox::error("Bad model");
    return;
  }
  if (!(v.isArray())) return;
  panel.getMainContext().loadCollection(v);
  refreshDraw();
  selector.refresh();
  changed=false;
  menuFile->Enable(menuFile->FindItem (wxT("Save")),false);
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
    if (Glob::fileExists(Glob::composePath(projectPath,"model.json")))
    {
      wxCommandEvent event; // fake
      reloadMenuSelection(event);
      menuFile->Enable(menuFile->FindItem (wxT("Reload")),true);
    }
    else
    {
      bool yesno=MBox::yesno("The model file does not exists into the specified path, do you want to create a new one ?");
      if (!yesno) return;
      menuFile->Enable(menuFile->FindItem (wxT("Save")),true);
    }
    menuGenerate->Enable(menuGenerate->FindItem (wxT("Generate Code")),true);   
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
