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

#ifndef __TRANSITIONDIALOG_H__
#define __TRANSITIONDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/choice.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/simplebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TransitionDialog
///////////////////////////////////////////////////////////////////////////////
class TransitionDialog : public wxDialog 
{
	private:
	
	protected:
		wxPanel* statePanel;
		wxChoice* eventType;
		wxSimplebook* choiceType;
		wxPanel* m_panel5;
		wxTextCtrl* conditionChoice;
		wxPanel* m_panel6;
		wxStaticText* m_staticText3;
		wxTextCtrl* timeChoice;
		wxStaticText* m_staticText4;
		wxCheckBox* timeFollow;
		wxPanel* m_panel2;
		wxChoice* tokenChoice;
		wxPanel* m_panel51;
		wxStaticText* m_staticText41;
		wxTextCtrl* guardCondition;
		wxStaticText* m_staticText411;
		wxTextCtrl* transitionAction;
		wxStdDialogButtonSizer* dialogButtons;
		wxButton* dialogButtonsOK;
		wxButton* dialogButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void StateDialogOnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void eventTypeOnChoice( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TransitionDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 731,427 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~TransitionDialog();
	
};

#endif //__TRANSITIONDIALOG_H__
