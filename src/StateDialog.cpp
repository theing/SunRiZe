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

#include "StateDialog.h"

///////////////////////////////////////////////////////////////////////////

StateDialog::StateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	statePanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( statePanel, wxID_ANY, wxT("Name") ), wxVERTICAL );
	
	nameText = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( nameText, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( statePanel, wxID_ANY, wxT("Do Action") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_staticText4 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Entry Action :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALL, 5 );
	
	entryAction = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	fgSizer1->Add( entryAction, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText41 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Exit Action :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	fgSizer1->Add( m_staticText41, 0, wxALL, 5 );
	
	exitAction = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	fgSizer1->Add( exitAction, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText411 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Do Action :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	fgSizer1->Add( m_staticText411, 0, wxALL, 5 );
	
	doAction = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	fgSizer1->Add( doAction, 0, wxALL|wxEXPAND, 5 );
	
	
	sbSizer8->Add( fgSizer1, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( sbSizer8, 5, wxEXPAND, 5 );
	
	
	statePanel->SetSizer( bSizer3 );
	statePanel->Layout();
	bSizer3->Fit( statePanel );
	mainSizer->Add( statePanel, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* underSizer;
	underSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	
	underSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	dialogButtons = new wxStdDialogButtonSizer();
	dialogButtonsOK = new wxButton( underSizer->GetStaticBox(), wxID_OK );
	dialogButtons->AddButton( dialogButtonsOK );
	dialogButtonsCancel = new wxButton( underSizer->GetStaticBox(), wxID_CANCEL );
	dialogButtons->AddButton( dialogButtonsCancel );
	dialogButtons->Realize();
	
	underSizer->Add( dialogButtons, 3, wxEXPAND, 5 );
	
	
	underSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	mainSizer->Add( underSizer, 0, wxEXPAND, 0 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( StateDialog::StateDialogOnInitDialog ) );
}

StateDialog::~StateDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( StateDialog::StateDialogOnInitDialog ) );
	
}
