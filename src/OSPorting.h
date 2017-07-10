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

#ifndef _OSPORTING_
#define _OSPORTING_

/*
OS Porting note:

This program has been designed for Linux 64bit and ported to Windows 10 64bit, using the Windows
POSIX emulation functions.
Due to the wxWidgets, I suppose it should run perfectly on MAC_OSX because is a posix system,
but there may be some roughness that must be targeted on the precise system.
The file Glob.h describes a generic interface that must be ported, and the file Glob.cpp contains the full porting.
Please referst to these files if you want to create a specific porting. It shouldn't be that hard. ;)

*/


#if  defined(_MSC_VER)
#define WINDOWS_PORTING 1
#elif  defined(__linux__)
#define LINUX_PORTING
#else
#error THIS PROGRAM CANNOT BE COMPILED FOR THIS TARGET. PLEASE LOOK AT OSPORTING.H
#endif


#endif // _OSPORTING_
