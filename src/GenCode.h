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

#ifndef GENCODE_H
#define GENCODE_H
#include "Commons.h"
#include <Python.h>
#include "Var.h"

/**
 * @class GenCode
 * @author TheIng
 * @date 06/27/17
 * @file GenCode.h
 * @brief The code generator
 * The code generator is a support and integration class for the scripting language. This class implements, several functions in native
 * language to be used by the code generator, and are based on two foundamental concepts :
 * <ul>
 * <li>Code preservation</li>
 * <li>Forward substitution</li>
 * </ul>
 * <br>
 * The code preservation strategy, allows the scripting language to insert special "KEY-CODES" that the language compiler
 * see as comments. The code between these two KEY-CODES in the editing phase is preserved when the code is load and replaced
 * when the code is saved. Is a block of code is not indicated into the new generated code, it goes to the garbage that can be 
 * placed someweher into a inactive piece of code (for example in C between a #IF 0 - #ENDIF ). The new generated code is never
 * overwritten if is exactly the same of the old file, so the MAKE process will continue to run properly.
 * <br>
 * The forward substitution allows the scrips to define the code as an algebraic language, by rules instead of by the sequence.
 * With the forward tracking/substitution we can define keys like "ENTRY_ACTION_MYSTATE" or "INCLUDE_PART" to be placed in our code
 * and the in other parts of the script, we can "add" rows, code or others KEYS to this parts. At the end, when the code is produced,
 * the keys are automatically substituted.
 * <br>
 * See at the user manual for further explanations.
 */
class GenCode
{
  
  static GenCode *instance;
  
  enum Property
  {
    RLine,
    RBlock,
    RKey,
    RGarbage
  };
  
  /// Definition of a line of code
  struct Row
  {
    Property type;
    String value;
  };
  
  /// Definition of a file.
  /// Keys are related to a specific file
  struct FStruct
  {
    String name;
    Map< String,Vector<Row> > lines;
  };
  
  // Fast access
  FStruct * root=nullptr;
  Vector<Row> * key=nullptr;
  
  /// The full bunch of files into the model
  Map<String,FStruct> files;
  /// Forward Recursive algorithm
  void forward(unsigned indent,Vector<String> &fill,FStruct & root,Vector<Row> & key);

  /// Convert a var to a script compatible object
  PyObject * varToPython(Var & v);
  Var * model;

  /// The old file to preserve temporarely
  Vector<String> oldFile;
  /// The code blocks by the key
  Map< String,Vector<String> > codeBlocks;
  
  /// The start and end prefix for a codeblock
  String startprefix,endprefix; 
  /// Preserve the code for the file name
  void preserveCode(String & name);
  /// onError flag to stop the code generation
  bool onError;
  
public:


  /**
   * @brief Static instance
   * @note The python language integration requires static functions. Gencode is not a singleton by design, so we need to
   * save its reference, when we instance it inside a function.
   * @param g the current GenCode instance
   */
  static void init(GenCode &g) {
    instance = &g;
  }

  GenCode();
  virtual ~GenCode();
  /**
   * @brief Generate all the code into the memory.
   * @param v the entire model
   * @return true if the code has been properly generated, false if an error is raised during the process
   */
  bool generateCode(Var & v);
  /**
   * @brief Write the code from memory to disk without overwriting unchanged files.
   */
  void writeFiles();
  
  /**
   * @brief Declare the current KEYFILE
   */
  static PyObject* declare(PyObject* self, PyObject* args);
  /**
   * @brief Use a specific KEY of the current KEYFILE for the following code
   */
  static PyObject* usekey(PyObject* self, PyObject* args);
  /**
   * @brief Insert a line of code
   */
  static PyObject* line(PyObject* self, PyObject* args);
  /**
   * @brief Insert a KEYCODE of code
   */
  static PyObject* block(PyObject* self, PyObject* args);
  /**
   * @brief Insert a KEY into the code
   */
  static PyObject* keycode(PyObject* self, PyObject* args);
  /**
   * @brief Specify the filename associated with the current KEYFILE
   */  
  static PyObject* filename(PyObject* self, PyObject* args);
  /**
   * @brief Bring the model inside the scripting language
   */
  static PyObject* getmodel(PyObject* self, PyObject* args);
  /**
   * @brief Define a prefix for the language KEYCODE
   */
  static PyObject* prefixes(PyObject* self, PyObject* args);
  /**
   * @brief Insert the remaining KEYCODEs not used yet
   */
  static PyObject* garbage(PyObject* self, PyObject* args);
  /**
   * @brief Raise an error to the code generator
   * Usually followed by an exit into the scripting language
   */
  static PyObject* error(PyObject* self, PyObject* args);  
};

class SPyObject {
  PyObject *ptr;
public:
  SPyObject() { }
  SPyObject(PyObject *p) { ptr=p; }
  ~SPyObject() { /*Py_XDECREF(ptr);*/ }
  PyObject **operator &() { return &ptr; }
  operator PyObject *() { return ptr; }
};
  

#endif // GENCODE_H
