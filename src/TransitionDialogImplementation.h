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

#ifndef __TransitionDialogImplementation__
#define __TransitionDialogImplementation__

/**
@file
Subclass of TransitionDialog, which is generated by wxFormBuilder.
*/

#include "TransitionDialog.h"

//// end generated include
 
#include "GObject.h"
#include "Var.h"
#include "FieldsHelper.h"

/** Implementing TransitionDialog */
class TransitionDialogImplementation : public TransitionDialog
{
  private :
    FieldsHelper fields;
    unsigned eventable;
    Var var;
	protected:
		// Handlers for TransitionDialog events.
		virtual void StateDialogOnInitDialog( wxInitDialogEvent& event );
		virtual void eventTypeOnChoice( wxCommandEvent& event );
	public:
		/** Constructor */
		TransitionDialogImplementation( wxWindow* parent , Var & v, Weak<GObject> &source);
	//// end generated class members
  Var & getVar();
	
};

#endif // __TransitionDialogImplementation__