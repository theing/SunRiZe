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

#include "Factory.h"
#include "SModule.h"
#include "SDependency.h"
#include "SState.h"
#include "SInitState.h"
#include "SCondition.h"
#include "STransition.h"
#include "Glob.h"

#include "Module.xpm"
#include "Dependency.xpm"
#include "State.xpm"
#include "Transition.xpm"
#include "Condition.xpm"


void Factory::createToolbar(GToolBar& toolbar, int currentToolbar)
{
  switch(currentToolbar) {
    case 0:    
      toolbar.addItem(Module_xpm,SModule::id);
      toolbar.addItem(Dependency_xpm,SDependency::id);
      break;
    case 1:    
      toolbar.addItem(State_xpm,SState::id);
      toolbar.addItem(Transition_xpm,STransition::id);
      toolbar.addItem(Condition_xpm,SCondition::id);
      break;
  }
}


GObject* Factory::createObject(const char * objectType)
{
  if (Glob::equal(SModule::id,objectType)) return new SModule();
  if (Glob::equal(SDependency::id,objectType)) return new SDependency();
  if (Glob::equal(SState::id,objectType)) return new SState();
  if (Glob::equal(SCondition::id,objectType)) return new SCondition();
  if (Glob::equal(STransition::id,objectType)) return new STransition();
  if (Glob::equal(SInitState::id,objectType)) return new SInitState();
  return nullptr;
}


