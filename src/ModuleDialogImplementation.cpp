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

#include "ModuleDialogImplementation.h"
#include <wx/valtext.h>

ModuleDialogImplementation::ModuleDialogImplementation( wxWindow* parent , Var & v)
:
ModuleDialog( parent )
{
  var=v;
}

void ModuleDialogImplementation::ModuleDialogOnInitDialog( wxInitDialogEvent& event )
{
  wxTextValidator tv1(wxFILTER_INCLUDE_CHAR_LIST);
  tv1.SetCharIncludes(wxT("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"));
  wxTextValidator tv2(wxFILTER_INCLUDE_CHAR_LIST);
  tv2.SetCharIncludes(wxT("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_ []*"));
  wxTextValidator tv3(wxFILTER_INCLUDE_CHAR_LIST);
  tv3.SetCharIncludes(wxT("1234567890"));
  
  fields.add(new FieldsHelperTextField("name",enterText1,"Module"));
  fields.add(new FieldsHelperCheckField("hasinit",hasInit,true));
  fields.add(new FieldsHelperTextField("comment",editText2,""));
  enterText1->SetValidator(tv1);
  
  auto showAttribute = [](Var & v) -> String 
  {
      String s=v.getContainer()["type"].getString();
      s+=":";
      s+=v.getContainer()["name"].getString();
      return s;
  };
  
  attributesList=new FieldsHelperListField("attributes",listBox111,showAttribute);
  fields.add(attributesList);
  
  attributesList->getFieldsHelper()->add(new FieldsHelperTextField("name",text1,""));
  attributesList->getFieldsHelper()->add(new FieldsHelperTextField("type",text2,""));
  attributesList->getFieldsHelper()->add(new FieldsHelperTextField("value",text3,""));
  attributesList->getFieldsHelper()->add(new FieldsHelperTextField("comment",editText22,""));
  attributesList->getFieldsHelper()->add(new FieldsHelperCheckField("volatile",volatileCheck,false));
  attributesList->getFieldsHelper()->add(new FieldsHelperChoiceField("visibility",choice1,0));
  text1->SetValidator(tv1);
  text2->SetValidator(tv2);
  
  
  
  auto showOperation = [](Var & v) -> String 
  {
      String s=v.getContainer()["type"].getString();
      s+=":";
      s+=v.getContainer()["name"].getString();
      return s;
  };
  operationsList=new FieldsHelperListField("operations",listBox11,showOperation);
  fields.add(operationsList);
  
  operationsList->getFieldsHelper()->add(new FieldsHelperTextField("name",text11,""));
  operationsList->getFieldsHelper()->add(new FieldsHelperTextField("type",text21,""));
  operationsList->getFieldsHelper()->add(new FieldsHelperTextField("comment",editText21,""));
  operationsList->getFieldsHelper()->add(new FieldsHelperChoiceField("visibility",choice11,0));
  text11->SetValidator(tv1);
  text12->SetValidator(tv2);

  
  auto showParameter = [](Var & v) -> String 
  {
      String s=v.getContainer()["type"].getString();
      s+=":";
      s+=v.getContainer()["name"].getString();
      return s;
  };
  parametersList= new FieldsHelperListField("parameters",listBox12,showParameter);
  operationsList->getFieldsHelper()->add(parametersList);
  
  parametersList->getFieldsHelper()->add(new FieldsHelperTextField("name",text111,""));
  parametersList->getFieldsHelper()->add(new FieldsHelperTextField("type",text211,""));
  
  
  
  
  auto showToken = [](Var & v) -> String 
  {
      String s=(v.getContainer()["type"].getInt()==0) ? "(*) " : "($) ";
      s+=v.getContainer()["name"].getString();
      return s;
  };
  tokensList=new FieldsHelperListField("tokens",listBox1111,showToken);
  fields.add(tokensList);

  tokensList->getFieldsHelper()->add(new FieldsHelperTextField("name",text12,""));
  tokensList->getFieldsHelper()->add(new FieldsHelperTextField("comment",editText221,""));
  tokensList->getFieldsHelper()->add(new FieldsHelperChoiceField("type",choice111,0));
  tokensList->getFieldsHelper()->add(new FieldsHelperTextField("limit",text121,""));
  text12->SetValidator(tv1);
  text121->SetValidator(tv3);

  
  fields.load(var);
  
  
}

void ModuleDialogImplementation::hasInitOnCheckBox( wxCommandEvent& event )
{
}

void ModuleDialogImplementation::selectedAttribute( wxCommandEvent& event )
{
  attributesList->select();
}

void ModuleDialogImplementation::newAttribute( wxCommandEvent& event )
{
  attributesList->newItem();
}

void ModuleDialogImplementation::upAttribute( wxCommandEvent& event )
{
  attributesList->up();
}

void ModuleDialogImplementation::dwAttribute( wxCommandEvent& event )
{
  attributesList->down();
}

void ModuleDialogImplementation::removeAttribute( wxCommandEvent& event )
{
  attributesList->remove();
}

void ModuleDialogImplementation::nameChangedAttribute( wxCommandEvent& event )
{
  attributesList->reload();
}

void ModuleDialogImplementation::typeChangerdAttribute( wxCommandEvent& event )
{
  attributesList->reload();
}

void ModuleDialogImplementation::selectedOperation( wxCommandEvent& event )
{
 operationsList->select();
}

void ModuleDialogImplementation::newOperation( wxCommandEvent& event )
{
 operationsList->newItem();
}

void ModuleDialogImplementation::upOperation( wxCommandEvent& event )
{
 operationsList->up();
}

void ModuleDialogImplementation::dwOperation( wxCommandEvent& event )
{
 operationsList->down();
}

void ModuleDialogImplementation::removeOperation( wxCommandEvent& event )
{
 parametersList->unselect(); 
 operationsList->remove();
}

void ModuleDialogImplementation::changedNameOperation( wxCommandEvent& event )
{
 operationsList->reload();
}

void ModuleDialogImplementation::changedTypeOperation( wxCommandEvent& event )
{
 operationsList->reload();
}

void ModuleDialogImplementation::selectedParameter( wxCommandEvent& event )
{
 parametersList->select();
}

void ModuleDialogImplementation::newParameter( wxCommandEvent& event )
{
  parametersList->newItem();
  operationsList->reload();
}

void ModuleDialogImplementation::upParameter( wxCommandEvent& event )
{
  parametersList->up();
  operationsList->reload();
}

void ModuleDialogImplementation::dwParamenter( wxCommandEvent& event )
{
  parametersList->down();
  operationsList->reload();
}

void ModuleDialogImplementation::removeParamenter( wxCommandEvent& event )
{
  parametersList->remove();
  operationsList->reload();
}

void ModuleDialogImplementation::changedNameParameter( wxCommandEvent& event )
{
  parametersList->reload();
  operationsList->reload();
}

void ModuleDialogImplementation::changedTypeParameter( wxCommandEvent& event )
{
  parametersList->reload();
  operationsList->reload();
}

void ModuleDialogImplementation::newToken( wxCommandEvent& event )
{
  tokensList->newItem();
}

void ModuleDialogImplementation::upToken( wxCommandEvent& event )
{
  tokensList->up();
}

void ModuleDialogImplementation::dwToken( wxCommandEvent& event )
{
  tokensList->down();
}

void ModuleDialogImplementation::removeToken( wxCommandEvent& event )
{
  tokensList->remove();
}

void ModuleDialogImplementation::changedNameToken( wxCommandEvent& event )
{
  tokensList->reload();
}

void ModuleDialogImplementation::valueChangerdAttribute(wxCommandEvent& event)
{
  attributesList->reload();
}

void ModuleDialogImplementation::onVisibilityAttribute(wxCommandEvent& event)
{
  attributesList->reload();
}

void ModuleDialogImplementation::InterrupSafeAttribute(wxCommandEvent& event)
{
  attributesList->reload();
}

void ModuleDialogImplementation::commentChangerdAttribute(wxCommandEvent& event)
{
  attributesList->reload();
}

void ModuleDialogImplementation::onVisibilityOperation(wxCommandEvent& event)
{
  operationsList->reload();
}

void ModuleDialogImplementation::onCommentOperation(wxCommandEvent& event)
{
  operationsList->reload();
}

void ModuleDialogImplementation::onTokenSelected(wxCommandEvent& event)
{
  tokensList->select();
}

void ModuleDialogImplementation::OnTypeToken(wxCommandEvent& event)
{
  tokensList->reload();
}

void ModuleDialogImplementation::onCommentToken(wxCommandEvent& event)
{
  tokensList->reload();
}

void ModuleDialogImplementation::onModuleName(wxCommandEvent& event)
{
  
}

void ModuleDialogImplementation::OnInitPriority(wxSpinEvent& event)
{
}

void ModuleDialogImplementation::onClassComment(wxCommandEvent& event)
{
}

Var& ModuleDialogImplementation::getVar()
{
    fields.update(var);
    return var;
}
