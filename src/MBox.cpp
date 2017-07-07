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

#include "MBox.h"
#include "GFrame.h"
#include <wx/msgdlg.h>
#include <wx/dirdlg.h>


void MBox::error(String content)
{
  wxString m(content);
  wxMessageDialog mb(&GFrame::getInstance(),m,wxT("SunRiZe Error"),wxICON_ERROR);
  mb.ShowModal();
}

void MBox::warning(String content)
{
  wxString m(content);
  wxMessageDialog mb(&GFrame::getInstance(),m,wxT("SunRiZe Warning"),wxICON_ERROR);
  mb.ShowModal();
}

String MBox::projectDialog()
{
    wxDirDialog openFileDialog(&GFrame::getInstance(), _("Set the project folder"));
    if (openFileDialog.ShowModal() == wxID_CANCEL) return "";        
    return  String (openFileDialog.GetPath().utf8_str().data());
}

bool MBox::yesno(String s)
{
  wxString m(s);
  wxMessageDialog mb(&GFrame::getInstance(),m,wxT("SunRiZe Question"),wxICON_QUESTION|wxYES_NO|wxNO_DEFAULT);
  if (mb.ShowModal()==wxID_YES) return true;
  return false;
}

unsigned MBox::yesnocancel(String s)
{
  wxString m(s);
  wxMessageDialog mb(&GFrame::getInstance(),m,wxT("SunRiZe Question"),wxICON_QUESTION|wxYES_NO|wxCANCEL|wxCANCEL_DEFAULT);
  int ans =mb.ShowModal();
  if (ans==wxID_YES) return 1;
  if (ans==wxID_NO) return 0;
  return 2;
}

bool MBox::okcancel(String s)
{
  wxString m(s);
  wxMessageDialog mb(&GFrame::getInstance(),m,wxT("SunRiZe Question"),wxICON_QUESTION|wxOK|wxCANCEL|wxCANCEL_DEFAULT);
  if (mb.ShowModal()==wxID_OK) return true;
  return false;
}
