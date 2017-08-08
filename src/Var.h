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

#ifndef Var_H
#define Var_H

#include "Commons.h"
#ifndef _WIN32
#include <bits/wordsize.h>
#endif

#include <sstream>


class Var;

const static char *bad_conv="Wrong type conversion";

/// VarContainer => Association String:Var (DICTIONARY)
typedef Map<String,Var> VarContainer;
/// VarArray => Array of Var (ARRAY)
typedef Vector<Var> VarArray;

/**
 * @class Var
 * @author TheIng
 * @date 06/27/17
 * @file Var.h
 * @brief Untyped polimorphic object.
 * The VAR object implements a JSON type variable regardless the static structure of the C++ language.
 * We can assign to a VAR the following values :
 * <ul>
 * <il>Integer (always cast to int64_t)</il>
 * <il>Real (always cast to double)</il>
 * <il>String</il>
 * <il>A dynamic array of VAR</il>
 * <il>A dynamic association String:VAR </il>
 * </ul>
 * A VAR can be used as a simple C++ variable, as like as std::vectors or similar, when the variable is assigned,
 * the entire content is copied in the new var.
 * <br>
 * We can get back the original value from a VAR with the specific functions, if the type is incompatible an exception
 * is raised.
 */

class Var
{
  
  
  union Value {
    void * null_value;
    String *string_value;
    double *float_value;
    int64_t *integer_value;
    VarArray *array_value;
    VarContainer *container_value;
    bool *boolean_value;
  } value;
  
   enum Types {
    Null_t,
    String_t,
    Integer_t,
    Float_t,
    Boolean_t,
    Array_t,
    Container_t,
  };
  
  Types type;
  
  void _clearVar() {
    if (value.null_value) {
        switch (type) {
          case String_t:
            delete value.string_value;
            break;
          case Float_t:
            delete value.float_value;
            break;
          case Integer_t:
            delete value.integer_value;
            break;
          case Array_t :
            delete value.array_value;
            break;              
          case Container_t:
            delete value.container_value;
            break;
          case Boolean_t:
            delete value.boolean_value;
            break;            
          default:
            break;
        }
    }
  }
  
  void _createVar( const Types t , const Value & val ) {
        type=t;
        switch (type) {
          case String_t:
            value.string_value=new String(*(val.string_value));
            break;
          case Integer_t:
            value.integer_value=new int64_t(*(val.integer_value));
            break;
          case Float_t:
            value.float_value=new double(*(val.float_value));
            break;
          case Array_t :
            value.array_value=new VarArray(*(val.array_value));
            break;              
          case Container_t:
            value.container_value=new VarContainer(*(val.container_value));
            break;
          case Boolean_t:
            value.boolean_value=new bool(*(val.boolean_value));
            break;
          case Null_t:
             value.null_value=nullptr; 
          default:
            break;
        }
  }
  
  
  
public:
  

  /**
   * @brief Var contructor (assigned to nullptr)
   */
  explicit Var() {
    type=Null_t;
    value.null_value=nullptr;
  }

  /**
   * @brief Copy constructor
   * @param val the old var
   */
  Var(const Var & val) {
    _createVar(val.type,val.value);
  }


  /**
   * @brief Destructor
   */
  virtual ~Var() {
    _clearVar();
  }
    

  /**
   * @brief converts integer, boolean or float to int64_t or raises an exception
   * @return the int64_t value by defects from double or 1:0 from booleans
   */
  int64_t toInt() {
    if (type==Integer_t) return *(value.integer_value);
    if (type==Float_t) return (int64_t) *(value.float_value);
    if (type==Boolean_t) return ( *(value.boolean_value) ? 1 : 0 );    
    throw Exception(bad_conv);
  }

  /**
   * @brief converts integer, boolean or float to double or raises an exception
   * @return the double value, 1.00:0.00 from booleans.
   */
  double toFloat() {
    if (type==Integer_t) return (double) *(value.integer_value);
    if (type==Float_t) return *(value.float_value);
    if (type==Boolean_t) return ( *(value.boolean_value) ? 1.00 : 0.00 );    
    throw Exception(bad_conv);
  }
  
  /**
   * @brief converts intenger, boolean or float to boolean or raises an exception
   * @return the boolean value , true from double or integer if !=0 .
   */
  bool toBoolean() {
    if (type==Integer_t) return (*(value.integer_value)!=0);
    if (type==Float_t) return (*(value.float_value)!=0.00);
    if (type==Boolean_t) return *(value.boolean_value);    
    throw Exception(bad_conv);
  }
  
  
  /**
   * @brief strictly returns the integer content
   * @return the int64_t content
   */
  int64_t & getInt() {
    if (type!=Integer_t) throw Exception(bad_conv);
    return *(value.integer_value);
  }

  /**
   * @brief strictly returns the float content
   * @return the double content
   */
  double & getFloat() {
    if (type!=Float_t) throw Exception(bad_conv);
    return *(value.float_value);
  }
    
  /**
   * @brief strictly returns the string content
   * @return the string content
   */    
  String & getString()  {
    if (type!=String_t) throw Exception(bad_conv);
    return *(value.string_value);
  }
  
  /**
   * @brief strictly returns the boolean content
   * @return the boolean content
   */    
  bool & getBoolean() {
    if (type!=Boolean_t) throw Exception(bad_conv);
    return *(value.boolean_value);
  }
  
  /**
   * @brief strictly returns an Array of VAR by reference
   * @return a std::vector<Var> by reference
   */    

  VarArray  & getArray()  {
    if (type!=Array_t) throw Exception(bad_conv);
    return *(value.array_value);
  }
  
  /**
   * @brief strictly returns an Container or Object or Dictionay of VAR by reference
   * @return a std::map< std::string, Var> by reference
   */    
  VarContainer & getContainer() {
    if (type!=Container_t) throw Exception(bad_conv);
    return *(value.container_value);
  }
  
  
  /**
   * @brief Assignment to double
   * @param val the double value to be assigned
   */
  
  Var & operator=(double val ) {
    _clearVar();
    value.float_value=new double(val);
    type=Float_t;
    return *this;
  }

  /**
   * @brief Assignment to int64_t
   * @param val the int64_t value to be assigned
   */
  Var & operator=(int64_t val ) {
    _clearVar();
    value.integer_value=new int64_t(val);
    type=Integer_t;
    return *this;
  }
  
  /**
   * @brief Assignment to int with implicit cast to int64_t
   * @param val the int value to be assigned 
   */

  Var & operator=(int val ) {
    _clearVar();
    value.integer_value=new int64_t(val);
    type=Integer_t;
    return *this;
  }
  
  /**
   * @brief Assignment to boolean
   * @param val the bool value to be assigned 
   */
  Var & operator=(bool val ) {
    _clearVar();
    value.boolean_value=new bool(val);
    type=Boolean_t;
    return *this;
  }
  
  /**
   * @brief Assignment from en existing array
   * @param val the std::vector<Var> by reference
   */

  Var & operator=(VarArray  & val ) {
    _clearVar();
    value.array_value=new VarArray(val);
    type=Array_t;
    return *this;
  }
  
  /**
   * @brief Assignment from en existing container
   * @param val the std::map< std::string, Var> by reference
   */
 
  Var & operator=(VarContainer & val ) {
    _clearVar();
    value.container_value=new VarContainer(val);
    type=Container_t;
    return *this;
  }
  
  /**
   * @brief Assignment to String by reference
   * @param val the std::string value to be assigned 
   */
  Var & operator=(String  & val ) {
    _clearVar();
    value.string_value=new String(val);
    type=String_t;
    return *this;
  }
 
 /**
 * @brief Assignment to const char, implicitely converted to string
 * @param val the const char * value to be assigned 
 */

 Var & operator=(const char * val ) {
    _clearVar();
    value.string_value=new String(val);
    type=String_t;
    return *this;
  }


 /**
 * @brief Assignment to null
 */

  void null() {
    _clearVar();
    value.null_value=nullptr;
    type=Null_t;
  }

  /**
   * @brief check if the content is an integer,boolean or float.
   * @see toInt , toFloat and toBoolean
   * @return true if the content is integer, boolean or float
   */

  bool isNumber() {
    if (type==Integer_t) return true;
    if (type==Float_t) return true;
    if (type==Boolean_t) return true;
    return false;
  }
  /**
   * @brief check if the content is integer
   * @return true if is integer, false otherwise
   */
  bool isInteger() {
    if (type==Integer_t) return true;
    return false;
  }
  /**
   * @brief check if the content is boolean
   * @return true if is boolean, false otherwise
   */
  bool isBoolean() {
    if (type==Boolean_t) return true;
    return false;
  }
  /**
   * @brief check if the content is float
   * @return true if is float, false otherwise
   */
  bool isFloat() {
    if (type==Float_t) return true;
    return false;
  }
  /**
   * @brief check if the content is a std::string
   * @return true if is std::string, false otherwise
   */

  bool isString() {
    if (type==String_t) return true;
    return false;
  }
  /**
   * @brief check if the content is null
   * @return true if is null, false otherwise
   */

  bool isNull() {
    if (type==Null_t) return true;
    return false;
  }
  
  /**
   * @brief check if the content is a Container (Dictionary) of var
   * @return true if is a container, false otherwise
   */
  bool isContainer() {
    if (type==Container_t) return true;
    return false;
  }
  
  /**
   * @brief check if the content is an Array of var
   * @return true if is an array, false otherwise
   */
  bool isArray() {
    if (type==Array_t) return true;
    return false;
  }

  /**
   * @brief constructor from boolean
   * @param val the boolean
   */
  
  explicit Var(bool val ) {
    value.boolean_value=new bool(val);
    type=Boolean_t;
  }
  
  /**
   * @brief constructor from an existing array
   * @param val the std::vector<Var> by reference
   */
  Var(VarArray  & val ) {
    value.array_value=new VarArray(val);
    type=Array_t;
  }
  
  /**
   * @brief constructor from an existing Container or Object or Dictionary
   * @param val the std::map<std::string,Var> by reference
   */
  Var(VarContainer  & val ) {
    value.container_value=new VarContainer(val);
    type=Container_t;
  }
  
  /**
   * @brief this is equivalent to A={} in Python or Javascript
   */
  void newContainer() {
    value.container_value=new VarContainer();
    type=Container_t;
  }

  /**
   * @brief this is equivalent to A=[] in Python or Javascript
   */
  void newArray() {
    value.array_value=new VarArray();
    type=Array_t;
  }

  /**
   * @brief constructor from an existing String
   * @param val the std::string by reference
   */
  Var(String  & val ) {
    value.string_value=new String(val);
    type=String_t;
  }

  /**
   * @brief constructor from an const char * stored as string
   * @param val the const char *
   */
  Var(const char * val ) {
    value.string_value=new String(val);
    type=String_t;
  }
  
  /**
   * @brief constructor from a double
   * @param val the double
   */
  explicit Var(double val ) {
    value.float_value=new double(val);
    type=Float_t;
  }

  /**
   * @brief constructor from a float stored as double
   * @param val the float
   */
  explicit Var(float val ) {
    value.float_value=new double(val);
    type=Float_t;
  }
  
  /**
   * @brief constructor from a int64_t
   * @param val the int64_t
   */
  explicit Var(int64_t val ) {
    value.integer_value=new int64_t(val);
    type=Integer_t;
  }
  
  /**
   * @brief constructor from a int stored as int64_t
   * @param val the int
   */  
  explicit Var(int val ) {
    value.integer_value=new int64_t(val);
    type=Integer_t;
  }
  
  /**
   * @brief Operator =
   * @param val the old var by reference, to be copied in this one.
   */
  Var & operator=(const Var & val) {
    _clearVar();
    _createVar(val.type,val.value);
    return *this;
  }
};

#endif // Var_H
