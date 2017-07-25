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

#ifndef __STATEDIALOG_H__
#define __STATEDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class StateDialog
///////////////////////////////////////////////////////////////////////////////
class StateDialog : public wxDialog 
{
	private:
	
	protected:
		wxPanel* statePanel;
		wxTextCtrl* nameText;
		wxStaticText* m_staticText4;
		wxTextCtrl* entryAction;
		wxStaticText* m_staticText41;
		wxTextCtrl* exitAction;
		wxStaticText* m_staticText411;
		wxTextCtrl* doAction;
		wxStdDialogButtonSizer* dialogButtons;
		wxButton* dialogButtonsOK;
		wxButton* dialogButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void StateDialogOnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		
	
	public:
		
		StateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 715,412 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~StateDialog();
	
};

#endif //__STATEDIALOG_H__
