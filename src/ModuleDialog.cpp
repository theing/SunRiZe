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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May 12 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ModuleDialog.h"

///////////////////////////////////////////////////////////////////////////

ModuleDialog::ModuleDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	tabbed = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	panel1 = new wxPanel( tabbed, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* p1sizer;
	p1sizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* overSizer;
	overSizer = new wxStaticBoxSizer( new wxStaticBox( panel1, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	mainPanel = new wxPanel( overSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* panelSizer1;
	panelSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* textSizer1;
	textSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	textLabel1 = new wxStaticText( mainPanel, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	textLabel1->Wrap( -1 );
	textSizer1->Add( textLabel1, 0, wxALL, 5 );
	
	enterText1 = new wxTextCtrl( mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	textSizer1->Add( enterText1, 1, wxALL, 5 );
	
	
	panelSizer1->Add( textSizer1, 1, wxEXPAND, 5 );
	
	wxBoxSizer* aSizer1111;
	aSizer1111 = new wxBoxSizer( wxHORIZONTAL );
	
	
	aSizer1111->Add( 0, 0, 1, wxEXPAND, 5 );
	
	hasInit = new wxCheckBox( mainPanel, wxID_ANY, wxT("Has Init"), wxDefaultPosition, wxDefaultSize, 0 );
	hasInit->SetValue(true); 
	aSizer1111->Add( hasInit, 0, wxALL, 5 );
	
	
	panelSizer1->Add( aSizer1111, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* editSizer1;
	editSizer1 = new wxStaticBoxSizer( new wxStaticBox( mainPanel, wxID_ANY, wxT("Comment") ), wxHORIZONTAL );
	
	editText2 = new wxTextCtrl( editSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	editSizer1->Add( editText2, 100, wxALL|wxEXPAND, 5 );
	
	
	panelSizer1->Add( editSizer1, 4, wxEXPAND, 5 );
	
	
	mainPanel->SetSizer( panelSizer1 );
	mainPanel->Layout();
	panelSizer1->Fit( mainPanel );
	overSizer->Add( mainPanel, 1, wxEXPAND | wxALL, 5 );
	
	
	p1sizer->Add( overSizer, 1, wxEXPAND, 5 );
	
	
	panel1->SetSizer( p1sizer );
	panel1->Layout();
	p1sizer->Fit( panel1 );
	tabbed->AddPage( panel1, wxT("Modules"), true );
	panel2 = new wxPanel( tabbed, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* p2sizer;
	p2sizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* listSizer111;
	listSizer111 = new wxStaticBoxSizer( new wxStaticBox( panel2, wxID_ANY, wxEmptyString ), wxHORIZONTAL );
	
	listBox111 = new wxListBox( listSizer111->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	listSizer111->Add( listBox111, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* ctrlList111;
	ctrlList111 = new wxBoxSizer( wxVERTICAL );
	
	button111 = new wxButton( listSizer111->GetStaticBox(), wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList111->Add( button111, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* updwSizer11;
	updwSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	upButton111 = new wxButton( listSizer111->GetStaticBox(), wxID_ANY, wxT("UP"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer11->Add( upButton111, 0, wxALL, 5 );
	
	dwButton111 = new wxButton( listSizer111->GetStaticBox(), wxID_ANY, wxT("DW"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer11->Add( dwButton111, 0, wxALL, 5 );
	
	
	ctrlList111->Add( updwSizer11, 0, wxEXPAND, 5 );
	
	button211 = new wxButton( listSizer111->GetStaticBox(), wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList111->Add( button211, 0, wxALL|wxEXPAND, 5 );
	
	
	listSizer111->Add( ctrlList111, 0, wxEXPAND, 5 );
	
	
	p2sizer->Add( listSizer111, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* attSizer;
	attSizer = new wxStaticBoxSizer( new wxStaticBox( panel2, wxID_ANY, wxT("Description") ), wxVERTICAL );
	
	wxBoxSizer* attSizerLR;
	attSizerLR = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* attSizerL;
	attSizerL = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* aSizer1;
	aSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	lab1 = new wxStaticText( attSizer->GetStaticBox(), wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	lab1->Wrap( -1 );
	aSizer1->Add( lab1, 1, wxALL, 5 );
	
	text1 = new wxTextCtrl( attSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	aSizer1->Add( text1, 6, wxALL, 5 );
	
	
	attSizerL->Add( aSizer1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* eSizer2;
	eSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	lab2 = new wxStaticText( attSizer->GetStaticBox(), wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	lab2->Wrap( -1 );
	eSizer2->Add( lab2, 1, wxALL, 5 );
	
	text2 = new wxTextCtrl( attSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	eSizer2->Add( text2, 6, wxALL, 5 );
	
	
	attSizerL->Add( eSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* eSizer3;
	eSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	lab3 = new wxStaticText( attSizer->GetStaticBox(), wxID_ANY, wxT("Value"), wxDefaultPosition, wxDefaultSize, 0 );
	lab3->Wrap( -1 );
	eSizer3->Add( lab3, 1, wxALL, 5 );
	
	text3 = new wxTextCtrl( attSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	eSizer3->Add( text3, 6, wxALL, 5 );
	
	
	attSizerL->Add( eSizer3, 0, wxEXPAND, 5 );
	
	
	attSizerLR->Add( attSizerL, 2, wxEXPAND, 5 );
	
	wxBoxSizer* attSizerR;
	attSizerR = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* eSizer4;
	eSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	lab4 = new wxStaticText( attSizer->GetStaticBox(), wxID_ANY, wxT("Visibility"), wxDefaultPosition, wxDefaultSize, 0 );
	lab4->Wrap( -1 );
	eSizer4->Add( lab4, 0, wxALL, 5 );
	
	wxString choice1Choices[] = { wxT("Private"), wxT("Public") };
	int choice1NChoices = sizeof( choice1Choices ) / sizeof( wxString );
	choice1 = new wxChoice( attSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, choice1NChoices, choice1Choices, 0 );
	choice1->SetSelection( 0 );
	eSizer4->Add( choice1, 1, wxALL, 5 );
	
	
	attSizerR->Add( eSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* cBoxSizerR;
	cBoxSizerR = new wxBoxSizer( wxHORIZONTAL );
	
	
	cBoxSizerR->Add( 0, 0, 1, wxEXPAND, 5 );
	
	volatileCheck = new wxCheckBox( attSizer->GetStaticBox(), wxID_ANY, wxT("Interrupt Safe"), wxDefaultPosition, wxDefaultSize, 0 );
	cBoxSizerR->Add( volatileCheck, 0, wxALL, 5 );
	
	
	attSizerR->Add( cBoxSizerR, 1, wxEXPAND, 5 );
	
	
	attSizerLR->Add( attSizerR, 1, wxEXPAND, 5 );
	
	
	attSizer->Add( attSizerLR, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* editSizer12;
	editSizer12 = new wxStaticBoxSizer( new wxStaticBox( attSizer->GetStaticBox(), wxID_ANY, wxT("Comment") ), wxHORIZONTAL );
	
	editText22 = new wxTextCtrl( editSizer12->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	editSizer12->Add( editText22, 100, wxALL|wxEXPAND, 5 );
	
	
	attSizer->Add( editSizer12, 1, wxEXPAND, 5 );
	
	
	p2sizer->Add( attSizer, 1, wxEXPAND, 5 );
	
	
	panel2->SetSizer( p2sizer );
	panel2->Layout();
	p2sizer->Fit( panel2 );
	tabbed->AddPage( panel2, wxT("Attributes"), false );
	panel3 = new wxPanel( tabbed, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* p2sizer1;
	p2sizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* listSizer11;
	listSizer11 = new wxStaticBoxSizer( new wxStaticBox( panel3, wxID_ANY, wxEmptyString ), wxHORIZONTAL );
	
	listBox11 = new wxListBox( listSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	listSizer11->Add( listBox11, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* ctrlList11;
	ctrlList11 = new wxBoxSizer( wxVERTICAL );
	
	button11 = new wxButton( listSizer11->GetStaticBox(), wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList11->Add( button11, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* updwSizer1;
	updwSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	upButton11 = new wxButton( listSizer11->GetStaticBox(), wxID_ANY, wxT("UP"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer1->Add( upButton11, 0, wxALL, 5 );
	
	dwButton11 = new wxButton( listSizer11->GetStaticBox(), wxID_ANY, wxT("DW"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer1->Add( dwButton11, 0, wxALL, 5 );
	
	
	ctrlList11->Add( updwSizer1, 0, wxEXPAND, 5 );
	
	button21 = new wxButton( listSizer11->GetStaticBox(), wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList11->Add( button21, 0, wxALL|wxEXPAND, 5 );
	
	
	listSizer11->Add( ctrlList11, 0, wxEXPAND, 5 );
	
	
	p2sizer1->Add( listSizer11, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* attSizer1;
	attSizer1 = new wxStaticBoxSizer( new wxStaticBox( panel3, wxID_ANY, wxT("Description") ), wxHORIZONTAL );
	
	wxBoxSizer* attSizer1L;
	attSizer1L = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* aSizer11;
	aSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	lab11 = new wxStaticText( attSizer1->GetStaticBox(), wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	lab11->Wrap( -1 );
	aSizer11->Add( lab11, 1, wxALL, 5 );
	
	text11 = new wxTextCtrl( attSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	aSizer11->Add( text11, 6, wxALL, 5 );
	
	
	attSizer1L->Add( aSizer11, 0, wxEXPAND, 5 );
	
	wxBoxSizer* eSizer21;
	eSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	lab21 = new wxStaticText( attSizer1->GetStaticBox(), wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	lab21->Wrap( -1 );
	eSizer21->Add( lab21, 1, wxALL, 5 );
	
	text21 = new wxTextCtrl( attSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	eSizer21->Add( text21, 6, wxALL, 5 );
	
	
	attSizer1L->Add( eSizer21, 0, wxEXPAND, 5 );
	
	wxBoxSizer* eSizer41;
	eSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	lab41 = new wxStaticText( attSizer1->GetStaticBox(), wxID_ANY, wxT("Visibility"), wxDefaultPosition, wxDefaultSize, 0 );
	lab41->Wrap( -1 );
	eSizer41->Add( lab41, 1, wxALL, 5 );
	
	wxString choice11Choices[] = { wxT("Private"), wxT("Public") };
	int choice11NChoices = sizeof( choice11Choices ) / sizeof( wxString );
	choice11 = new wxChoice( attSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, choice11NChoices, choice11Choices, 0 );
	choice11->SetSelection( 0 );
	eSizer41->Add( choice11, 2, wxALL, 5 );
	
	
	eSizer41->Add( 0, 0, 4, wxEXPAND, 5 );
	
	
	attSizer1L->Add( eSizer41, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* editSizer11;
	editSizer11 = new wxStaticBoxSizer( new wxStaticBox( attSizer1->GetStaticBox(), wxID_ANY, wxT("Comment") ), wxHORIZONTAL );
	
	editText21 = new wxTextCtrl( editSizer11->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	editSizer11->Add( editText21, 100, wxALL|wxEXPAND, 5 );
	
	
	attSizer1L->Add( editSizer11, 1, wxEXPAND, 5 );
	
	
	attSizer1->Add( attSizer1L, 1, wxEXPAND, 5 );
	
	wxBoxSizer* attSizer1R;
	attSizer1R = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* listSizer12;
	listSizer12 = new wxStaticBoxSizer( new wxStaticBox( attSizer1->GetStaticBox(), wxID_ANY, wxEmptyString ), wxHORIZONTAL );
	
	listBox12 = new wxListBox( listSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	listSizer12->Add( listBox12, 2, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* ctrlList12;
	ctrlList12 = new wxBoxSizer( wxVERTICAL );
	
	button12 = new wxButton( listSizer12->GetStaticBox(), wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList12->Add( button12, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* updwSizer2;
	updwSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	upButton12 = new wxButton( listSizer12->GetStaticBox(), wxID_ANY, wxT("UP"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer2->Add( upButton12, 0, wxALL, 5 );
	
	dwButton12 = new wxButton( listSizer12->GetStaticBox(), wxID_ANY, wxT("DW"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer2->Add( dwButton12, 0, wxALL, 5 );
	
	
	ctrlList12->Add( updwSizer2, 0, wxEXPAND, 5 );
	
	button22 = new wxButton( listSizer12->GetStaticBox(), wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList12->Add( button22, 0, wxALL|wxEXPAND, 5 );
	
	
	listSizer12->Add( ctrlList12, 0, wxEXPAND, 5 );
	
	
	attSizer1R->Add( listSizer12, 1, wxEXPAND, 5 );
	
	wxBoxSizer* parameterSizer;
	parameterSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* aSizer111;
	aSizer111 = new wxBoxSizer( wxHORIZONTAL );
	
	lab111 = new wxStaticText( attSizer1->GetStaticBox(), wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	lab111->Wrap( -1 );
	aSizer111->Add( lab111, 1, wxALL, 5 );
	
	text111 = new wxTextCtrl( attSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	aSizer111->Add( text111, 6, wxALL, 5 );
	
	
	parameterSizer->Add( aSizer111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* eSizer211;
	eSizer211 = new wxBoxSizer( wxHORIZONTAL );
	
	lab211 = new wxStaticText( attSizer1->GetStaticBox(), wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	lab211->Wrap( -1 );
	eSizer211->Add( lab211, 1, wxALL, 5 );
	
	text211 = new wxTextCtrl( attSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	eSizer211->Add( text211, 6, wxALL, 5 );
	
	
	parameterSizer->Add( eSizer211, 0, wxEXPAND, 5 );
	
	
	attSizer1R->Add( parameterSizer, 0, wxEXPAND, 5 );
	
	
	attSizer1->Add( attSizer1R, 1, wxEXPAND, 5 );
	
	
	p2sizer1->Add( attSizer1, 1, wxEXPAND, 5 );
	
	
	panel3->SetSizer( p2sizer1 );
	panel3->Layout();
	p2sizer1->Fit( panel3 );
	tabbed->AddPage( panel3, wxT("Operations"), false );
	panel4 = new wxPanel( tabbed, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* p2sizer2;
	p2sizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* listSizer1111;
	listSizer1111 = new wxStaticBoxSizer( new wxStaticBox( panel4, wxID_ANY, wxEmptyString ), wxHORIZONTAL );
	
	listBox1111 = new wxListBox( listSizer1111->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	listSizer1111->Add( listBox1111, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* ctrlList1111;
	ctrlList1111 = new wxBoxSizer( wxVERTICAL );
	
	button1111 = new wxButton( listSizer1111->GetStaticBox(), wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList1111->Add( button1111, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* updwSizer111;
	updwSizer111 = new wxBoxSizer( wxHORIZONTAL );
	
	upButton1111 = new wxButton( listSizer1111->GetStaticBox(), wxID_ANY, wxT("UP"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer111->Add( upButton1111, 0, wxALL, 5 );
	
	dwButton1111 = new wxButton( listSizer1111->GetStaticBox(), wxID_ANY, wxT("DW"), wxDefaultPosition, wxDefaultSize, 0 );
	updwSizer111->Add( dwButton1111, 0, wxALL, 5 );
	
	
	ctrlList1111->Add( updwSizer111, 0, wxEXPAND, 5 );
	
	button2111 = new wxButton( listSizer1111->GetStaticBox(), wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	ctrlList1111->Add( button2111, 0, wxALL|wxEXPAND, 5 );
	
	
	listSizer1111->Add( ctrlList1111, 0, wxEXPAND, 5 );
	
	
	p2sizer2->Add( listSizer1111, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* attSizer2;
	attSizer2 = new wxStaticBoxSizer( new wxStaticBox( panel4, wxID_ANY, wxT("Description") ), wxVERTICAL );
	
	wxBoxSizer* attSizerLR1;
	attSizerLR1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* attSizerL1;
	attSizerL1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* aSizer12;
	aSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	lab12 = new wxStaticText( attSizer2->GetStaticBox(), wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	lab12->Wrap( -1 );
	aSizer12->Add( lab12, 2, wxALL, 5 );
	
	text12 = new wxTextCtrl( attSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	aSizer12->Add( text12, 14, wxALL, 5 );
	
	
	attSizerL1->Add( aSizer12, 0, wxEXPAND, 5 );
	
	wxBoxSizer* eSizer411;
	eSizer411 = new wxBoxSizer( wxHORIZONTAL );
	
	lab411 = new wxStaticText( attSizer2->GetStaticBox(), wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	lab411->Wrap( -1 );
	eSizer411->Add( lab411, 2, wxALL, 5 );
	
	wxString choice111Choices[] = { wxT("Counter"), wxT("Signal") };
	int choice111NChoices = sizeof( choice111Choices ) / sizeof( wxString );
	choice111 = new wxChoice( attSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, choice111NChoices, choice111Choices, 0 );
	choice111->SetSelection( 1 );
	eSizer411->Add( choice111, 3, wxALL, 5 );
	
	
	eSizer411->Add( 0, 0, 6, wxEXPAND, 5 );
	
	lab4111 = new wxStaticText( attSizer2->GetStaticBox(), wxID_ANY, wxT("Limit :"), wxDefaultPosition, wxDefaultSize, 0 );
	lab4111->Wrap( -1 );
	eSizer411->Add( lab4111, 2, wxALL, 5 );
	
	text121 = new wxTextCtrl( attSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	eSizer411->Add( text121, 3, wxALL, 5 );
	
	
	attSizerL1->Add( eSizer411, 1, wxEXPAND, 5 );
	
	
	attSizerLR1->Add( attSizerL1, 4, wxEXPAND, 5 );
	
	wxBoxSizer* attSizerR1;
	attSizerR1 = new wxBoxSizer( wxVERTICAL );
	
	
	attSizerR1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	attSizerLR1->Add( attSizerR1, 1, wxEXPAND, 5 );
	
	
	attSizer2->Add( attSizerLR1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* editSizer121;
	editSizer121 = new wxStaticBoxSizer( new wxStaticBox( attSizer2->GetStaticBox(), wxID_ANY, wxT("Comment") ), wxHORIZONTAL );
	
	editText221 = new wxTextCtrl( editSizer121->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	editSizer121->Add( editText221, 100, wxALL|wxEXPAND, 5 );
	
	
	attSizer2->Add( editSizer121, 1, wxEXPAND, 5 );
	
	
	p2sizer2->Add( attSizer2, 1, wxEXPAND, 5 );
	
	
	panel4->SetSizer( p2sizer2 );
	panel4->Layout();
	p2sizer2->Fit( panel4 );
	tabbed->AddPage( panel4, wxT("Token"), false );
	
	mainSizer->Add( tabbed, 1, wxEXPAND | wxALL, 5 );
	
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
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ModuleDialog::ModuleDialogOnInitDialog ) );
	enterText1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onModuleName ), NULL, this );
	hasInit->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ModuleDialog::hasInitOnCheckBox ), NULL, this );
	editText2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onClassComment ), NULL, this );
	listBox111->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::selectedAttribute ), NULL, this );
	button111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newAttribute ), NULL, this );
	upButton111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upAttribute ), NULL, this );
	dwButton111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwAttribute ), NULL, this );
	button211->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeAttribute ), NULL, this );
	text1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::nameChangedAttribute ), NULL, this );
	text2->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::typeChangerdAttribute ), NULL, this );
	text3->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::valueChangerdAttribute ), NULL, this );
	choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ModuleDialog::onVisibilityAttribute ), NULL, this );
	volatileCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ModuleDialog::InterrupSafeAttribute ), NULL, this );
	editText22->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::commentChangerdAttribute ), NULL, this );
	listBox11->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::selectedOperation ), NULL, this );
	button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newOperation ), NULL, this );
	upButton11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upOperation ), NULL, this );
	dwButton11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwOperation ), NULL, this );
	button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeOperation ), NULL, this );
	text11->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameOperation ), NULL, this );
	text21->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedTypeOperation ), NULL, this );
	choice11->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ModuleDialog::onVisibilityOperation ), NULL, this );
	editText21->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onCommentOperation ), NULL, this );
	listBox12->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::selectedParameter ), NULL, this );
	button12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newParameter ), NULL, this );
	upButton12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upParameter ), NULL, this );
	dwButton12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwParamenter ), NULL, this );
	button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeParamenter ), NULL, this );
	text111->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameParameter ), NULL, this );
	text211->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedTypeParameter ), NULL, this );
	listBox1111->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::onTokenSelected ), NULL, this );
	button1111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newToken ), NULL, this );
	upButton1111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upToken ), NULL, this );
	dwButton1111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwToken ), NULL, this );
	button2111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeToken ), NULL, this );
	text12->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameToken ), NULL, this );
	choice111->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ModuleDialog::OnTypeToken ), NULL, this );
	text121->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameToken ), NULL, this );
	editText221->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onCommentToken ), NULL, this );
}

ModuleDialog::~ModuleDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( ModuleDialog::ModuleDialogOnInitDialog ) );
	enterText1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onModuleName ), NULL, this );
	hasInit->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ModuleDialog::hasInitOnCheckBox ), NULL, this );
	editText2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onClassComment ), NULL, this );
	listBox111->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::selectedAttribute ), NULL, this );
	button111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newAttribute ), NULL, this );
	upButton111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upAttribute ), NULL, this );
	dwButton111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwAttribute ), NULL, this );
	button211->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeAttribute ), NULL, this );
	text1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::nameChangedAttribute ), NULL, this );
	text2->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::typeChangerdAttribute ), NULL, this );
	text3->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::valueChangerdAttribute ), NULL, this );
	choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ModuleDialog::onVisibilityAttribute ), NULL, this );
	volatileCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ModuleDialog::InterrupSafeAttribute ), NULL, this );
	editText22->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::commentChangerdAttribute ), NULL, this );
	listBox11->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::selectedOperation ), NULL, this );
	button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newOperation ), NULL, this );
	upButton11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upOperation ), NULL, this );
	dwButton11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwOperation ), NULL, this );
	button21->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeOperation ), NULL, this );
	text11->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameOperation ), NULL, this );
	text21->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedTypeOperation ), NULL, this );
	choice11->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ModuleDialog::onVisibilityOperation ), NULL, this );
	editText21->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onCommentOperation ), NULL, this );
	listBox12->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::selectedParameter ), NULL, this );
	button12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newParameter ), NULL, this );
	upButton12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upParameter ), NULL, this );
	dwButton12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwParamenter ), NULL, this );
	button22->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeParamenter ), NULL, this );
	text111->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameParameter ), NULL, this );
	text211->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedTypeParameter ), NULL, this );
	listBox1111->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( ModuleDialog::onTokenSelected ), NULL, this );
	button1111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::newToken ), NULL, this );
	upButton1111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::upToken ), NULL, this );
	dwButton1111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::dwToken ), NULL, this );
	button2111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ModuleDialog::removeToken ), NULL, this );
	text12->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameToken ), NULL, this );
	choice111->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ModuleDialog::OnTypeToken ), NULL, this );
	text121->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::changedNameToken ), NULL, this );
	editText221->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ModuleDialog::onCommentToken ), NULL, this );
	
}
