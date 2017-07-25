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

#include "StateDialogImplementation.h"
#include <wx/valtext.h>

StateDialogImplementation::StateDialogImplementation( wxWindow* parent , Var & v)
:
StateDialog( parent )
{
  var=v;
}

void StateDialogImplementation::StateDialogOnInitDialog( wxInitDialogEvent& event )
{
  wxTextValidator tv1(wxFILTER_ALPHANUMERIC);
  fields.add(new FieldsHelperTextField("name",nameText,"State"));
  nameText->SetValidator(tv1);
  
  fields.add(new FieldsHelperTextField("entryaction",entryAction,""));
  fields.add(new FieldsHelperTextField("exitaction",exitAction,""));
  fields.add(new FieldsHelperTextField("doaction",doAction,""));
  fields.load(var);
}


Var& StateDialogImplementation::getVar()
{
    fields.update(var);
    return var;
}