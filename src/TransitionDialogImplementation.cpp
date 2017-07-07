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

#include "TransitionDialogImplementation.h"
#include "SCondition.h"
#include "SInitState.h"
#include "GContext.h"
#include "GFrame.h"
#include "JSONParser.h"
#include "Glob.h"

TransitionDialogImplementation::TransitionDialogImplementation( wxWindow* parent, Var & v ,Weak<GObject> &source)
:
TransitionDialog( parent )
{
  var=v;
  eventable=0;
  if (Glob::equal(SCondition::id,source.lock()->getId())) eventable=1;
  else if (Glob::equal(SInitState::id,source.lock()->getId())) eventable=2;  
}

void TransitionDialogImplementation::StateDialogOnInitDialog( wxInitDialogEvent& event )
{
  fields.add(new FieldsHelperChoiceField("event",eventType,0));
  fields.add(new FieldsHelperTextChoiceField("token",tokenChoice,""));
  fields.add(new FieldsHelperTextField("time",timeChoice,""));
  fields.add(new FieldsHelperTextField("condition",conditionChoice,""));
  fields.add(new FieldsHelperCheckField("follower",timeFollow,false));
  fields.add(new FieldsHelperTextField("guard",guardCondition,""));
  fields.add(new FieldsHelperTextField("action",transitionAction,""));
  fields.load(var);
  GContext * w = & (GFrame::getPanel().getCurrentContext());
  VarArray tok(w->getParent()->content.getContainer()["tokens"].getArray());
  for (Var & v : tok)
  {
    wxString arg(v.getContainer()["name"].getString());
    tokenChoice->Append(arg);
  }
  
  
  switch(eventable)
  {
    case 0:
    {
      int fd=(int) var.getContainer()["event"].getInt();
      choiceType->SetSelection(fd);
      if (fd==2)
        {
          guardCondition->Enable(true);
          tokenChoice->SetStringSelection(var.getContainer()["token"].getString());
        }
      else guardCondition->Enable(false);
    }
    break;
    case 2:
      guardCondition->Enable(false);
      guardCondition->SetValue(wxT(""));
    case 1:
    {
      eventType->SetSelection(wxNOT_FOUND);
      choiceType->SetSelection(3);
      eventType->Enable(false);
    }
    break;    
  }

}




void TransitionDialogImplementation::eventTypeOnChoice( wxCommandEvent& event )
{
  if (eventable!=0) {
    choiceType->SetSelection(3);
    return;
  }
  int fd=eventType->GetSelection();
  choiceType->SetSelection(fd);
  choiceType->Refresh();
  if (fd==2)
    {
      guardCondition->Enable(true);
      tokenChoice->SetStringSelection(var.getContainer()["token"].getString());
    }
  else guardCondition->Enable(false);
}

Var& TransitionDialogImplementation::getVar()
{
    fields.update(var);
    return var;
}