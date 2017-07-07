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

#include <wx/wx.h>
#include "GFrame.h"
#include "Glob.h"

// application class
class MyApp : public wxApp
{
public:
	// function called at the application initialization
	virtual bool OnInit();

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{        
    Glob::init();
    GFrame::getInstance().Show(true);
    return true;
}