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

#ifndef GPRIMARY_H
#define GPRIMARY_H

#include "GStandalone.h" // Base class: GStandalone

class GContext;

/**
 * @class GPrimary
 * @author Marco
 * @date 06/25/17
 * @file GPrimary.h
 * @brief Defines a Primary Object
 * A PRIMARY Object is a special STANDALONE object that "can have" an associated context.
 * In order to differentiate, between the global context, and a context contained into a primary object, we define the MAIN context
 * associated with a proper TOOLBAR, and the SUBCONTEXT (NOT MAIN) associated with a different TOOBAR. 
 * For example we can define a PRIMARY Object, MODULE as a single instance of a class, and when we put this instance
 * in the MAIN context, we can ask to assign the module a SUBCONTEXT that will be selectable and it will contains the related state
 * machine for example.
 * @note the context is associated to a std::unique_ptr because is is stricly related to the primary object. Since the tool does not
 * allows to delete a object when we are visualizing his subcontext by design, it is safe to place the reference to the primary object, into 
 * the context itself as a simple pointer, to give the items into the subcontext the capability to access the parent object parameters,
 * without perfioming the heaviest shared pointers operations and checks. When the primary object will be deleted, the context and the
 * related GObjects are deleted too, so they will not need to access the parent object data anymore.
 */

class GPrimary : public GStandalone
{
  Unique<GContext> context;
public:
  GPrimary();
  virtual ~GPrimary();
  /**
   * @brief isPrimary
   * @return true
   */
  bool isPrimary() const;
  /**
   * @brief Gets the description
   * It is used to show the name of the object into the selector, to be choosen as context.
   * @return the string description
   */
  virtual String getString()= 0;
  /**
   * @brief Returns the context as simple pointer to be used immediately
   * @return the context as pointer
   */
  GContext * getContext();
  /**
   * @brief Creates a new empty context for this object 
   * @note the "this" of this object is automatically stored into the new context as parent.
   */
  virtual void newContext();
  /**
   * @brief Gets the context var
   * This var contains the same data of a STANDALONE object in addiction to an
   * array of var representing the objects in the subcontext, stored as "context" in the object itself. 
   * @param full
   * @return the Var of the object
   */
  virtual Var getContent(bool full);
  /**
   * @brief Creates the object from the passed Var and creates/fills the related context if one.
   * @param v the Var
   * @param map the association between index and GObjects.
   */
  virtual void loadObject(Var & v,Map< int,Shared<GObject> > &map);
};

#endif // GPRIMARY_H
