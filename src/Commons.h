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

#ifndef _COMMONS_
#define _COMMONS_

/**
 * COMMONS definition and codestyles used into the project
 */

#include "OSPorting.h"

#define VERSION_STRING "0.2.170813"
#define VERSION_NUMBER 3

#include <stdint.h>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <utility>
#include <iostream>
#include <functional>


#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <memory>
#include <type_traits>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/listbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <wx/font.h>
#include <math.h>

#include "_Exception.h"

#define VMIN(x,y) ((x<y) ? x : y)
#define VMAX(x,y) ((x>y) ? x : y)



typedef std::string String;

template <typename T,typename K> using Pair = std::pair< T,K >;
template <typename T,typename K> using Map = std::map< T,K >;
template <typename T> using List = std::list< T >;
template <typename T> using Vector = std::vector< T >;
template <typename T> using Stack = std::stack< T >;

template <typename T> using Shared = std::shared_ptr< T >;
template <typename T> using Weak = std::weak_ptr< T >;
template <typename T> using Unique = std::unique_ptr< T >;

#define SIGNUM(x) ( (x)==0 ? 0 : ( (x)<0 ? -1 : 1 )  )


#endif // _COMMONS_