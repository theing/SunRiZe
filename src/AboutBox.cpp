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

#include "Commons.h"


#include "AboutBox.h"
#include "Icon.xpm"

AboutBox::AboutBox( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_bitmap1 = new wxStaticBitmap( this, wxID_ANY, wxBitmap( Icon_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_bitmap1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("- SunRiZe v." VERSION_STRING " -\nOpen model MDD with scriptable code generator.\n- (c) 2017 by Marco Spreafico -\n"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_ELLIPSIZE_MIDDLE );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.\n See <http://www.gnu.org/licenses/>"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_ELLIPSIZE_MIDDLE );
	m_staticText2->Wrap( 400 );
	bSizer1->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button1 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutBox::m_button1OnButtonClick ), NULL, this );
}

AboutBox::~AboutBox()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutBox::m_button1OnButtonClick ), NULL, this );
	
}
