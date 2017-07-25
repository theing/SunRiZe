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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 12 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TransitionDialog.h"

///////////////////////////////////////////////////////////////////////////

TransitionDialog::TransitionDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	statePanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( statePanel, wxID_ANY, wxT("Event") ), wxVERTICAL );
	
	wxString eventTypeChoices[] = { wxT("Condition"), wxT("Time"), wxT("Token") };
	int eventTypeNChoices = sizeof( eventTypeChoices ) / sizeof( wxString );
	eventType = new wxChoice( sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, eventTypeNChoices, eventTypeChoices, 0 );
	eventType->SetSelection( 2 );
	sbSizer4->Add( eventType, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer3->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	choiceType = new wxSimplebook( statePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel5 = new wxPanel( choiceType, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_panel5, wxID_ANY, wxT("Condition") ), wxVERTICAL );
	
	conditionChoice = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( conditionChoice, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel5->SetSizer( sbSizer6 );
	m_panel5->Layout();
	sbSizer6->Fit( m_panel5 );
	choiceType->AddPage( m_panel5, wxT("a page"), false );
	m_panel6 = new wxPanel( choiceType, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_panel6, wxID_ANY, wxT("Time") ), wxHORIZONTAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Timeout :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer5->Add( m_staticText3, 0, wxALL, 5 );
	
	timeChoice = new wxTextCtrl( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( timeChoice, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, wxT("ms"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer5->Add( m_staticText4, 0, wxALL, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	timeFollow = new wxCheckBox( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Time follower"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( timeFollow, 0, wxALL, 5 );
	
	
	sbSizer7->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	m_panel6->SetSizer( sbSizer7 );
	m_panel6->Layout();
	sbSizer7->Fit( m_panel6 );
	choiceType->AddPage( m_panel6, wxT("a page"), false );
	m_panel2 = new wxPanel( choiceType, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Token Name") ), wxVERTICAL );
	
	wxArrayString tokenChoiceChoices;
	tokenChoice = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, tokenChoiceChoices, 0 );
	tokenChoice->SetSelection( 0 );
	sbSizer5->Add( tokenChoice, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( sbSizer5 );
	m_panel2->Layout();
	sbSizer5->Fit( m_panel2 );
	choiceType->AddPage( m_panel2, wxT("a page"), false );
	m_panel51 = new wxPanel( choiceType, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	choiceType->AddPage( m_panel51, wxT("a page"), false );
	
	bSizer6->Add( choiceType, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer3->Add( bSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( statePanel, wxID_ANY, wxT("Transition") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_staticText41 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Guard Condition :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	fgSizer1->Add( m_staticText41, 0, wxALL, 5 );
	
	guardCondition = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( guardCondition, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText411 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Action :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	fgSizer1->Add( m_staticText411, 0, wxALL, 5 );
	
	transitionAction = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	fgSizer1->Add( transitionAction, 0, wxALL|wxEXPAND, 5 );
	
	
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TransitionDialog::StateDialogOnInitDialog ) );
	eventType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TransitionDialog::eventTypeOnChoice ), NULL, this );
}

TransitionDialog::~TransitionDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TransitionDialog::StateDialogOnInitDialog ) );
	eventType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TransitionDialog::eventTypeOnChoice ), NULL, this );
	
}
