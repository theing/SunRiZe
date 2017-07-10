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

#ifndef GFIELD_H
#define GFIELD_H

#include "Commons.h"

/**
 * The generic parent of an informational field, is the GField object.
 * The constructor of this objects, receives a list reference to the container (which has to be inherited by SObject), and it place itself into
 * the list of fields.
 * When a SObject is written or read by the XML or a JSON string is created, all the information are grabbed from the field, which get a name and
 * a value.
 * A GField can be associated to a Dialog Box also, and fill a proper form with its value o grab the value from the field itself.      
 * @author marco
 *
 */

class GField
{
  String name;
protected:
  struct GWrap { };
public:
  GField();
  GField(String name);
  virtual ~GField();
  private String name;	
	
	/**
	 * The GField constructor receives the name.
	 * The proper value will be defined by the extended classes.
	 * @param nam
	 * The name.
	 */
	public GField(String nam) {
		name=nam;
	}
	
	/**
	 * All the value contained in a GField, must be writable in a String or readable by a String.
	 * This is a String Setter for the value.   
	 * @param o
	 * The String with the value.
	 */
	virtual void setStringValue(String o) =0 ;
	
	/**
	 * This is a generic setter of the Value by Object. Integers, Boolean an native types must be wrapped.
	 * @param o
	 * The object whith the value.
	 */
	void setValue(GWrap & o) =0 ;
	
	
	
	/**
	 * This is a generic getter of the Value by Object. Integers, Boolean an native types must be wrapped.
	 * @return
	 * The object with the value.
	 */
	public GWrap & getValue() =0 ;
	
	/**
	 * Get the string name passed by constructor.
	 * @return
	 */
	
	public String getName() {
		return name;
	}
	
	
	/**
	 * This is used by the dialog boxes to ask an update of the value by exiting.
	 */
public :
	void update() =0 ;
	
	/**
	 * A GField always contains its value twice.
	 * If a dialog box asks for the restore action the copy of the value must be restored.
	 * It is used by the cancel button.  
	 */
	void restore() =0 ;

	/**
	 * This method generates the related JSON Object. 
	 * @return
	 * The string with the JSON object.
	 */
	
	public String generateJson(bool full);
		
};

#endif // GFIELD_H
