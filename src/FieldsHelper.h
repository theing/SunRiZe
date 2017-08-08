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

#ifndef FIELDSHELPER_H
#define FIELDSHELPER_H
#include "Var.h"
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/choice.h>

/**
 * @class FieldsHelper
 * @author TheIng
 * @date 06/28/17
 * @file FieldsHelper.h
 * @brief The fields helper for the Properties (Edit) Dialog Boxes with the related inner classes.
 * The fields helper is a connection between the dialog fields and the Var contained in each GObject.
 * This class and the related inner classes manage the values changes and the opening/closing of a edit dialog box.
 * 
 */
class enable;
class FieldsHelper
{


public:

  /**
   * @class Field
   * @author TheIng
   * @date 06/28/17
   * @file FieldsHelper.h
   * @brief The generic field abstract class/interface
   */
  class Field {    
  protected:  
      String name;
  public:
      /**
       * @brief The field name
       * @param n name of the field in the VAR
       */
      Field(String n):name(n){}
      virtual ~Field() {}
      /**
       * @brief Updates the field value to the VAR
       * @param v the var
       */
      virtual void update(Var & v)=0;
      /**
       * @brief Loads the VAR value into the field
       * @param v the Var
       */
      virtual void load(Var & v)=0;
      /**
       * @brief Loads the field and update the VAR with the default value 
       * @param v the Var
       */
      virtual void deflt(Var & v)=0;
      /**
       * @brief Enable the control
       * @param en true enable,false disable
       */
      virtual void enable(bool en)=0;
  };

private :
  
  Vector< Unique<Field> > fields; 

public:

  /**
   * @brief Get the vector of the fields association by reference.
   * @return the std::vector< std::unique_ptr<Field> > reference
   */
  const Vector< Unique<Field> > & getFields();  
  FieldsHelper();
  virtual ~FieldsHelper();
  /**
   * @brief Add a field.
   * @param field to add as pointer, the helper will take care to destroy it
   */
  void add(Field *field);
  /**
   * @brief Load the VAR values into the fields when a new dialog is shown
   * @param var the var to load in.
   */
  void load(Var & var);
  /**
   * @brief Update the var with the current fields values.
   * @param var the var to set to.
   */
  void update(Var & var);
  /**
   * @brief enable/disable the connected fields
   * @param enable true enable, false disable
   */
  void enableFields(bool enable);

};

  /**
   * @class FieldsHelperTextChoiceField
   * @author TheIng
   * @date 06/28/17
   * @file FieldsHelper.h
   * @brief This field associates a VAR string with the text content of a simple combo box.
   * @see Field
   */
  class FieldsHelperTextChoiceField : public FieldsHelper::Field {
      wxChoice * ctrl;
      String def;
  public:
      FieldsHelperTextChoiceField(String n,wxChoice *c,String d);
      virtual void update(Var & v);
      virtual void load(Var & v);      
      virtual void deflt(Var & v);
      virtual void enable(bool en);
  };
  
  
  /**
   * @class FieldsHelperTextField
   * @author TheIng
   * @date 06/28/17
   * @file FieldsHelper.h
   * @brief This field associates a VAR string with a text field.
   * @see Field
   */
  class FieldsHelperTextField : public FieldsHelper::Field {
      wxTextCtrl * ctrl;
      String def;
  public:
      FieldsHelperTextField(String n,wxTextCtrl *c,String d);
      virtual void update(Var & v);
      virtual void load(Var & v);      
      virtual void deflt(Var & v);
      virtual void enable(bool en);
  };
  
  
  /**
   * @class FieldsHelperSpinField
   * @author TheIng
   * @date 06/28/17
   * @file FieldsHelper.h
   * @brief This field associates a VAR integer with a SPIN control numeric value.
   * @see Field
   */
  class FieldsHelperSpinField : public FieldsHelper::Field {
      wxSpinCtrl * ctrl;
      int def;
  public:
      FieldsHelperSpinField(String n,wxSpinCtrl *c,int d);
      virtual void update(Var & v);
      virtual void load(Var & v);
      virtual void deflt(Var & v);      
      virtual void enable(bool en);
  };
  
  /**
   * @class FieldsHelperCheckField
   * @author TheIng
   * @date 06/28/17
   * @file FieldsHelper.h
   * @brief This field associates a VAR boolean with a CHECKBOX
   * @see Field
   */
  
  class FieldsHelperCheckField : public FieldsHelper::Field {
      wxCheckBox * ctrl;
      bool def;
  public:
      FieldsHelperCheckField(String n,wxCheckBox *c,bool d);
      virtual void update(Var & v);
      virtual void load(Var & v);      
      virtual void deflt(Var & v);      
      virtual void enable(bool en);
  };
  
  /**
   * @class FieldsHelperChoiceField
   * @author TheIng
   * @date 06/28/17
   * @file FieldsHelper.h
   * @brief This field associates a VAR integer, with a position of a combo box selection.
   * @see Field
   */
  
  class FieldsHelperChoiceField : public FieldsHelper::Field {
      wxChoice * ctrl;
      int def;
  public:
      FieldsHelperChoiceField(String n,wxChoice *c,int d);
      virtual void update(Var & v);
      virtual void load(Var & v);            
      virtual void deflt(Var & v);      
      virtual void enable(bool en);
  };
  
  /**
   * @class FieldsHelperListField
   * @author TheIng
   * @date 06/28/17
   * @file FieldsHelper.h
   * @brief This special field associates an ARRAY of VAR to a specific set of FIELDS managing all the aspects of the contextual
   * list selection with specific methods.
   * @see Field
   */
  
 class FieldsHelperListField : public FieldsHelper::Field {
      wxListBox * ctrl;
      // The vararray containing data
      VarArray content;
      std::function< String (Var & i) > show;
      FieldsHelper fieldsHelper;
      int selection;    
      void _showFields();
      
public:      
      
      /**
       * @brief The field helper constructor.
       * @param s is the lambda function returning the string name to place into the list.
       */
      FieldsHelperListField(String n,wxListBox *c,std::function< String (Var & i) > s);
      virtual void update(Var & v);
      virtual void load(Var & v);
      virtual void deflt(Var & v);  
      virtual void enable(bool en);      
      /**
       * @brief Manages the selection of a list
       */
      void select();
      /**
       * @brief Reloads all the items
       */
      void reload();
      /**
       * @brief Creates a new item with the default values
       */
      void newItem();
      /**
       * @brief Remove an item from the list
       */
      void remove();
      /**
       * @brief Unselect the current item
       */
      void unselect();
      /**
       * @brief Send the current item up to one position (if possible)
       */
      void up();
      /**
       * @brief Send the current item down to one position (if possible)
       */
      void down(); 
      /**
       * @brief The list field helper.
       * This class instances another field helper to manage the sub fields.
       * @return the internal fields helper by reference.
       */
      FieldsHelper * getFieldsHelper();
      
  };

#endif // FIELDSHELPER_H
