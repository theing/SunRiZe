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

#include "FieldsHelper.h"

FieldsHelper::FieldsHelper()
{
}

FieldsHelper::~FieldsHelper()
{
}


void FieldsHelper::add(Field* field)
{
  fields.push_back(Unique <Field>(field));
}

const Vector<Unique<FieldsHelper::Field> >  & FieldsHelper::getFields()
{
  return fields;
}

void FieldsHelper::load(Var & v)
{
  for (auto & a: fields) a->load(v);
  
}

void FieldsHelper::update(Var & v)
{
  for (auto & a: fields) a->update(v);
}

FieldsHelperTextField::FieldsHelperTextField(String n, wxTextCtrl* c,String d):Field(n)
{
  ctrl=c;
  def=d;
}

void FieldsHelperTextField::update(Var & v)
{
  String val ((ctrl->GetValue()).utf8_str().data());
  v.getContainer()[name]=val;
}

void FieldsHelperTextField::load(Var & v)
{
  String val=v.getContainer()[name].getString();
  ctrl->SetValue(wxString(val.c_str(),wxConvUTF8));
}

void FieldsHelperTextField::deflt(Var & v)
{
  Var val(def);
  v.getContainer()[name]=val;
  ctrl->SetValue(def);
}

void FieldsHelperTextField::enable(bool en)
{
  ctrl->Enable(en);
}


FieldsHelperTextChoiceField::FieldsHelperTextChoiceField(String n, wxChoice* c,String d):Field(n)
{
  ctrl=c;
  def=d;
}

void FieldsHelperTextChoiceField::update(Var & v)
{
  int fd=ctrl->GetSelection();
  if (fd==wxNOT_FOUND)
  {
    Var val(def);
    v.getContainer()[name]=val;
    return;
  }  
  String val ((ctrl->GetString(fd)).utf8_str().data());
  v.getContainer()[name]=val;
}

void FieldsHelperTextChoiceField::load(Var & v)
{
  wxString val(v.getContainer()[name].getString().c_str(),wxConvUTF8);
  int fd=ctrl->FindString(val,true);
  ctrl->SetSelection(fd);
}

void FieldsHelperTextChoiceField::deflt(Var & v)
{
  Var val(def);
  v.getContainer()[name]=val;
  int fd=ctrl->FindString(def,true);
  ctrl->SetSelection(fd);
}
void FieldsHelperTextChoiceField::enable(bool en)
{
  ctrl->Enable(en);
}





FieldsHelperSpinField::FieldsHelperSpinField(String n, wxSpinCtrl* c,int d):Field(n)
{
  ctrl=c;
  def=d;
}

void FieldsHelperSpinField::update(Var & v)
{
  v.getContainer()[name]=ctrl->GetValue();
}

void FieldsHelperSpinField::load(Var & v)
{
  int64_t val=v.getContainer()[name].getInt();
  ctrl->SetValue((int)val);
}

void FieldsHelperSpinField::deflt(Var & v)
{
  Var val(def);
  v.getContainer()[name]=val;
  ctrl->SetValue(def);
}


FieldsHelperCheckField::FieldsHelperCheckField(String n, wxCheckBox* c,bool d):Field(n)
{
  ctrl=c;
  def=d;
}

void FieldsHelperCheckField::update(Var& v)
{
  bool b=ctrl->GetValue();
  v.getContainer()[name]=b;
}

void FieldsHelperCheckField::load(Var& v)
{
  bool b=v.getContainer()[name].getBoolean();
  ctrl->SetValue(b);
}

void FieldsHelperCheckField::deflt(Var & v)
{
  Var val(def);
  v.getContainer()[name]=val;
  ctrl->SetValue(def);
}


FieldsHelperChoiceField::FieldsHelperChoiceField(String n, wxChoice* c,int d):Field(n)
{
  ctrl=c;
  def=d;
}

void FieldsHelperChoiceField::update(Var& v)
{
  v.getContainer()[name]=ctrl->GetSelection();
}

void FieldsHelperChoiceField::load(Var& v)
{
  auto val=v.getContainer()[name].getInt();
  ctrl->SetSelection((int)val);
}

void FieldsHelperChoiceField::deflt(Var & v)
{
  Var val(def);
  v.getContainer()[name]=val;
  ctrl->SetSelection(def);
}


FieldsHelperListField::FieldsHelperListField(String n, wxListBox* c,std::function< String (Var & i) > s):Field(n)
{
  ctrl=c;
  show=s;
  selection=-1;
}

void FieldsHelperListField::update(Var& v)
{
  v.getContainer()[name]=content;
}

void FieldsHelperListField::load(Var& v)
{  
  unselect();
  content.clear();
  for (Var & i : v.getContainer()[name].getArray()) 
  {
    content.push_back(i);
  }
  _showFields();
}

void FieldsHelperListField::select()
{
  if (selection>=0) 
  {
    Var v=content[selection].getContainer();
    for (auto const & f : fieldsHelper.getFields()) 
    {
        f->update(v);
    }
    content[selection]=v;
  }
  selection=ctrl->GetSelection();
  if (selection<0) {
    fieldsHelper.enableFields(false);
    return;
  }
  fieldsHelper.enableFields(true);
  Var v=content[selection].getContainer();
  for (auto const & f : fieldsHelper.getFields()) 
  {
      f->load(v);
  }
}

FieldsHelper * FieldsHelperListField::getFieldsHelper()
{
  return &fieldsHelper;
}

void FieldsHelperListField::newItem()
{
  Var ni;
  selection=-1;
  ni.newContainer();
  for (auto const & f : fieldsHelper.getFields()) 
  {
      f->deflt(ni);
  }
  content.push_back(ni);
  selection=content.size()-1;
  _showFields();
  fieldsHelper.enableFields(true);
}


void FieldsHelperListField::deflt(Var & v)
{
  Var val;
  val.newArray();
  v.getContainer()[name]=val;  
  ctrl->Clear();
  content=VarArray();
  unselect();
}



void FieldsHelperListField::_showFields()
{
  ctrl->Clear();
  wxArrayString wxa;
  for (Var & i : content) 
  {
    wxString s(show(i).c_str(), wxConvUTF8);    
    wxa.Add(s);
  }
  if (!wxa.empty()) ctrl->InsertItems(wxa,0);
  if ((selection>=0)&&(selection<(int)content.size())) ctrl->SetSelection(selection);
}

void FieldsHelperListField::reload()
{
  if (selection<0) return;
  Var v=content[selection].getContainer();
  for (auto const & f : fieldsHelper.getFields()) 
  {
      f->update(v);
  }
  content[selection]=v;
  _showFields();
}

void FieldsHelperListField::remove()
{
  if (selection<0) return;
  auto iter=content.begin();
  iter+=selection;
  content.erase(iter);
  unselect();
  _showFields();
}


void FieldsHelperListField::down()
{
  if (selection<0) return;
  if (selection>(int)content.size()-2) return;
  Var v=content[selection];
  content[selection]=content[selection+1];
  content[selection+1]=v;
  ++selection;
  _showFields();
}

void FieldsHelperListField::up()
{
  if (selection<1) return;
  Var v=content[selection];
  content[selection]=content[selection-1];
  content[selection-1]=v;
  --selection;
  _showFields();
}

void FieldsHelperListField::unselect()
{
  selection=-1;
  Var v2;
  v2.newContainer();
  for (auto const & f : fieldsHelper.getFields()) 
  {
      f->deflt(v2);
  }
  fieldsHelper.enableFields(false);

}

void FieldsHelper::enableFields(bool enable)
{
  for (auto & a: fields) a->enable(enable);
}

void FieldsHelperSpinField::enable(bool en)
{
  ctrl->Enable(en);
}
void FieldsHelperCheckField::enable(bool en)
{
  ctrl->Enable(en);
}

void FieldsHelperChoiceField::enable(bool en)
{
  ctrl->Enable(en);
}
void FieldsHelperListField::enable(bool en)
{
  ctrl->Enable(en);
}