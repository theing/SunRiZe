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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 12 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainPanel.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MyFrame1::m_splitter1OnIdle ), NULL, this );
	m_splitter1->SetMinimumPaneSize( 50 );
	
	m_panel1 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	primaryList = new wxListBox( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SORT ); 
	bSizer2->Add( primaryList, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	m_scrolledWindow1 = new wxScrolledWindow( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	m_scrolledWindow1->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_panel2 = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer3->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );
	
	
	m_scrolledWindow1->SetSizer( bSizer3 );
	m_scrolledWindow1->Layout();
	bSizer3->Fit( m_scrolledWindow1 );
	m_splitter1->SplitVertically( m_panel1, m_scrolledWindow1, 200 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Reload") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( m_menuItem1 );
	
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( m_menuItem2 );
	
	menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Project") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( m_menuItem3 );
	
	menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( m_menuItem4 );
	
	m_menubar1->Append( menuFile, wxT("File") ); 
	
	menuGenerate = new wxMenu();
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem( menuGenerate, wxID_ANY, wxString( wxT("Generate Code") ) , wxEmptyString, wxITEM_NORMAL );
	menuGenerate->Append( m_menuItem5 );
	
	m_menubar1->Append( menuGenerate, wxT("Generate") ); 
	
	menuHelp = new wxMenu();
	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( menuHelp, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	menuHelp->Append( m_menuItem6 );
	
	m_menubar1->Append( menuHelp, wxT("Help") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar1->Realize(); 
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MyFrame1::onCloseEvent ) );
	primaryList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MyFrame1::itemSelected ), NULL, this );
	m_panel2->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MyFrame1::panelKeyDown ), NULL, this );
	m_panel2->Connect( wxEVT_KEY_UP, wxKeyEventHandler( MyFrame1::panelKeyUp ), NULL, this );
	m_panel2->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_MIDDLE_UP, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_MOTION, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_MIDDLE_DCLICK, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Connect( wxEVT_PAINT, wxPaintEventHandler( MyFrame1::panelPaintEvent ), NULL, this );
	this->Connect( m_menuItem1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::reloadMenuSelection ) );
	this->Connect( m_menuItem2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::saveMenuSelection ) );
	this->Connect( m_menuItem3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::projectOnMenuSelection ) );
	this->Connect( m_menuItem4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::exitOnMenuSelection ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::generateOnMenuSelection ) );
	this->Connect( m_menuItem6->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::aboutMenuSelection ) );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MyFrame1::onCloseEvent ) );
	primaryList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MyFrame1::itemSelected ), NULL, this );
	m_panel2->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MyFrame1::panelKeyDown ), NULL, this );
	m_panel2->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( MyFrame1::panelKeyUp ), NULL, this );
	m_panel2->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_MIDDLE_UP, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_MOTION, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_MIDDLE_DCLICK, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( MyFrame1::panelMouseEvent ), NULL, this );
	m_panel2->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MyFrame1::panelPaintEvent ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::reloadMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::saveMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::projectOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::exitOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::generateOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyFrame1::aboutMenuSelection ) );
	
}
