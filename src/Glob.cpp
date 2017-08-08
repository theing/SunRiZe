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

#include "Glob.h"
#include <stdlib.h>  
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


#ifdef LINUX_PORTING
#include <unistd.h>
#endif


#ifdef WINDOWS_PORTING
  #include <direct.h>
  #include <windows.h>
  #define SEPARATION_CHAR '\\'
#else
  // I suppose this is always valid except for windows
  #define SEPARATION_CHAR '/'
#endif



String Glob::scriptPath;

bool Glob::equal(const char* a, const char* b)
{
  if (a==b) return true;
  return (!strcmp(a,b));
}



void Glob::init()
{
    char * path=getenv("SCRIPT_PATH");
    if ((!path)||(!folderExists(path))) 
    {
      scriptPath=getExecutablePath();
    }
    else
    {
      scriptPath=path;      
    }
    if (scriptPath[scriptPath.size()-1]!=SEPARATION_CHAR) scriptPath+=SEPARATION_CHAR;
}

String Glob::resPath() 
{
    return String(scriptPath);  
}


bool Glob::folderExists(String folder)
{
#ifdef WINDOWS_PORTING
	if (_access(folder.c_str(), 0)) return false;
	return true;
#endif
#ifdef LINUX_PORTING
  if (access(folder.c_str(),X_OK)) return false;
  return true;
#endif
}

bool Glob::fileExists(String file)
{
#ifdef WINDOWS_PORTING
	if (_access(file.c_str(), 0)) return false;
	return true;
#endif
#ifdef LINUX_PORTING
  if (access(file.c_str(),F_OK)) return false;
  return true;
#endif
}

String Glob::composePath(String path, String file)
{
	if (path.empty()) return file;
	if (file.empty()) return path;
	if (path[path.size() - 1] != SEPARATION_CHAR) path += SEPARATION_CHAR;
	path += file;
	return path;
}



bool Glob::makePath(String fullPath)
{
  String::size_type pos = fullPath.rfind(SEPARATION_CHAR);
  if (pos == String::npos) return true;
  String newPath = fullPath.substr(0, pos);
  if (folderExists(newPath)) return true;
  if (!Glob::makePath(newPath)) return false;
#ifdef WINDOWS_PORTING
  if (_mkdir(newPath.c_str())) return false;
#endif
#ifdef LINUX_PORTING
  if (mkdir(newPath.c_str(),0777)) return false; 
#endif
  return true;
}

/*
   WARNING : This function gets the EXECUTABLE path that is not standard.
   The implementation is different for each operating system
*/

String Glob::getExecutablePath()
{
#ifdef WINDOWS_PORTING
	char dest[ MAX_PATH ];
	GetModuleFileNameA(NULL, (LPSTR) dest, MAX_PATH);
	String res(dest);
  String::size_type pos = res.rfind('\\');
  if (pos != String::npos) res = res.substr(0, pos + 1);
  return res;
#endif

#ifdef LINUX_PORTING
    char dest[PATH_MAX];
    memset(dest,0,sizeof(dest)); 
    readlink("/proc/self/exe", dest, PATH_MAX);
    String res(dest);
    String::size_type pos=res.rfind('/');
    if (pos!=String::npos) res=res.substr(0,pos+1);
    else res="/";
    return res;
#endif
}



bool Glob::makeBackup(String fullPath)
{
  // Standard linux backup extensions (also valid for all the operating systems)
  String backup = fullPath + "~";
  // If the file does not exists, it cannot be considered an error
  if (!fileExists(fullPath)) return true;
  if (rename(fullPath.c_str(), backup.c_str())) return false;
  return true;
}
