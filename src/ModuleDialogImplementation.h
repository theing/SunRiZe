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

#ifndef __ModuleDialogImplementation__
#define __ModuleDialogImplementation__

/**
@file
Subclass of ModuleDialog, which is generated by wxFormBuilder.
*/

#include "ModuleDialog.h"
//// end generated include

#include "Var.h"
#include "FieldsHelper.h"

/** Implementing ModuleDialog */
class ModuleDialogImplementation : public ModuleDialog
{
  
  private :
    FieldsHelper fields;
    Var var;
    FieldsHelperListField *attributesList;
    FieldsHelperListField *operationsList;
    FieldsHelperListField *tokensList;
    FieldsHelperListField *parametersList; 

  
	protected:
		// Handlers for ModuleDialog events.
		void ModuleDialogOnInitDialog( wxInitDialogEvent& event );
		void hasInitOnCheckBox( wxCommandEvent& event );
		void selectedAttribute( wxCommandEvent& event );
		void newAttribute( wxCommandEvent& event );
		void upAttribute( wxCommandEvent& event );
		void dwAttribute( wxCommandEvent& event );
		void removeAttribute( wxCommandEvent& event );
		void nameChangedAttribute( wxCommandEvent& event );
		void typeChangerdAttribute( wxCommandEvent& event );
		void valueChangerdAttribute( wxCommandEvent& event );
		void onVisibilityAttribute( wxCommandEvent& event );
		void InterrupSafeAttribute( wxCommandEvent& event );
		void commentChangerdAttribute( wxCommandEvent& event );
		void selectedOperation( wxCommandEvent& event );
		void newOperation( wxCommandEvent& event );
		void upOperation( wxCommandEvent& event );
		void dwOperation( wxCommandEvent& event );
		void removeOperation( wxCommandEvent& event );
		void changedNameOperation( wxCommandEvent& event );
		void changedTypeOperation( wxCommandEvent& event );
		void onVisibilityOperation( wxCommandEvent& event );
		void onCommentOperation( wxCommandEvent& event );
		void selectedParameter( wxCommandEvent& event );
		void newParameter( wxCommandEvent& event );
		void upParameter( wxCommandEvent& event );
		void dwParamenter( wxCommandEvent& event );
		void removeParamenter( wxCommandEvent& event );
		void changedNameParameter( wxCommandEvent& event );
		void changedTypeParameter( wxCommandEvent& event );
		void onTokenSelected( wxCommandEvent& event );
		void newToken( wxCommandEvent& event );
		void upToken( wxCommandEvent& event );
		void dwToken( wxCommandEvent& event );
		void removeToken( wxCommandEvent& event );
		void changedNameToken( wxCommandEvent& event );
		void OnTypeToken( wxCommandEvent& event );
		void onCommentToken( wxCommandEvent& event );
 		void onModuleName( wxCommandEvent& event );
		void OnInitPriority( wxSpinEvent& event );
		void onClassComment( wxCommandEvent& event );
	public:
		/** Constructor */
		ModuleDialogImplementation( wxWindow* parent , Var & v );
	//// end generated class members
  Var & getVar();
};

#endif // __ModuleDialogImplementation__
