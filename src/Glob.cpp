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

#include "Glob.h"
#include <stdlib.h>  
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


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
    if (scriptPath[scriptPath.size()-1]!='/') scriptPath+="/";
}

String Glob::resPath() 
{
    return String(scriptPath);  
}



bool Glob::folderExists(String folder)
{
  if (access(folder.c_str(),X_OK)) return false;
  return true;
}

bool Glob::fileExists(String file)
{
  if (access(file.c_str(),F_OK)) return false;
  return true;
}

String Glob::composePath(String path, String file)
{
  if (path.empty()) return file;
  if (file.empty()) return path;  
  if (path[path.size()-1]!='/') path+="/";
  path+=file;
  return path;
}



bool Glob::makePath(String fullPath)
{
  String::size_type pos=fullPath.rfind('/');
  if (pos==String::npos) return true;
  String newPath=fullPath.substr(0,pos);  
  if (folderExists(newPath)) return true;
  if (!Glob::makePath(newPath)) return false;
  if((mkdir(newPath.c_str(),0777)) && errno!=EEXIST) return false;  
  return true;
}


String Glob::getExecutablePath()
{
    char dest[PATH_MAX];
    memset(dest,0,sizeof(dest)); 
    readlink("/proc/self/exe", dest, PATH_MAX);
    String res(dest);
    String::size_type pos=res.rfind('/');
    if (pos!=String::npos) res=res.substr(0,pos+1);
    else res="/";
    return res;
}
