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

#ifndef __MAINPANEL_H__
#define __MAINPANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/listbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
	protected:
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel1;
		wxListBox* primaryList;
		wxScrolledWindow* m_panel2;
		wxMenuBar* m_menubar1;
		wxMenu* menuFile;
		wxMenu* menuGenerate;
		wxMenu* menuHelp;
		wxToolBar* m_toolBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onCloseEvent( wxCloseEvent& event ) { event.Skip(); }
		virtual void itemSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void panelKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void panelKeyUp( wxKeyEvent& event ) { event.Skip(); }
		virtual void panelMouseEvent( wxMouseEvent& event ) { event.Skip(); }
		virtual void panelPaintEvent( wxPaintEvent& event ) { event.Skip(); }
		virtual void reloadMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void projectOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void exitOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void generateOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void aboutMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 919,630 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 200 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MyFrame1::m_splitter1OnIdle ), NULL, this );
		}
	
};

#endif //__MAINPANEL_H__
