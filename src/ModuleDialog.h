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

#ifndef __MODULEDIALOG_H__
#define __MODULEDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ModuleDialog
///////////////////////////////////////////////////////////////////////////////
class ModuleDialog : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* tabbed;
		wxPanel* panel1;
		wxPanel* mainPanel;
		wxStaticText* textLabel1;
		wxTextCtrl* enterText1;
		wxCheckBox* hasInit;
		wxTextCtrl* editText2;
		wxPanel* panel2;
		wxListBox* listBox111;
		wxButton* button111;
		wxButton* upButton111;
		wxButton* dwButton111;
		wxButton* button211;
		wxStaticText* lab1;
		wxTextCtrl* text1;
		wxStaticText* lab2;
		wxTextCtrl* text2;
		wxStaticText* lab3;
		wxTextCtrl* text3;
		wxStaticText* lab4;
		wxChoice* choice1;
		wxCheckBox* volatileCheck;
		wxTextCtrl* editText22;
		wxPanel* panel3;
		wxListBox* listBox11;
		wxButton* button11;
		wxButton* upButton11;
		wxButton* dwButton11;
		wxButton* button21;
		wxStaticText* lab11;
		wxTextCtrl* text11;
		wxStaticText* lab21;
		wxTextCtrl* text21;
		wxStaticText* lab41;
		wxChoice* choice11;
		wxTextCtrl* editText21;
		wxListBox* listBox12;
		wxButton* button12;
		wxButton* upButton12;
		wxButton* dwButton12;
		wxButton* button22;
		wxStaticText* lab111;
		wxTextCtrl* text111;
		wxStaticText* lab211;
		wxTextCtrl* text211;
		wxPanel* panel4;
		wxListBox* listBox1111;
		wxButton* button1111;
		wxButton* upButton1111;
		wxButton* dwButton1111;
		wxButton* button2111;
		wxStaticText* lab12;
		wxTextCtrl* text12;
		wxStaticText* lab411;
		wxChoice* choice111;
		wxStaticText* lab4111;
		wxTextCtrl* text121;
		wxTextCtrl* editText221;
		wxStdDialogButtonSizer* dialogButtons;
		wxButton* dialogButtonsOK;
		wxButton* dialogButtonsCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ModuleDialogOnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void onModuleName( wxCommandEvent& event ) { event.Skip(); }
		virtual void hasInitOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void onClassComment( wxCommandEvent& event ) { event.Skip(); }
		virtual void selectedAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void newAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void upAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void dwAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void removeAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void nameChangedAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void typeChangerdAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void valueChangerdAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void onVisibilityAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void InterrupSafeAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void commentChangerdAttribute( wxCommandEvent& event ) { event.Skip(); }
		virtual void selectedOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void newOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void upOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void dwOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void removeOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void changedNameOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void changedTypeOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void onVisibilityOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCommentOperation( wxCommandEvent& event ) { event.Skip(); }
		virtual void selectedParameter( wxCommandEvent& event ) { event.Skip(); }
		virtual void newParameter( wxCommandEvent& event ) { event.Skip(); }
		virtual void upParameter( wxCommandEvent& event ) { event.Skip(); }
		virtual void dwParamenter( wxCommandEvent& event ) { event.Skip(); }
		virtual void removeParamenter( wxCommandEvent& event ) { event.Skip(); }
		virtual void changedNameParameter( wxCommandEvent& event ) { event.Skip(); }
		virtual void changedTypeParameter( wxCommandEvent& event ) { event.Skip(); }
		virtual void onTokenSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void newToken( wxCommandEvent& event ) { event.Skip(); }
		virtual void upToken( wxCommandEvent& event ) { event.Skip(); }
		virtual void dwToken( wxCommandEvent& event ) { event.Skip(); }
		virtual void removeToken( wxCommandEvent& event ) { event.Skip(); }
		virtual void changedNameToken( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeToken( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCommentToken( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ModuleDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 872,616 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~ModuleDialog();
	
};

#endif //__MODULEDIALOG_H__
