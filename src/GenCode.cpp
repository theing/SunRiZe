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

#include <iostream>
#include <fstream>
#include <sstream>
#include "GenCode.h"
#include <stdio.h>
#include "Text.h"
#include "MBox.h"
#include "Glob.h" 
#include "GFrame.h"
#include "stdio.h"


GenCode *GenCode::instance=nullptr;


static struct PyMethodDef methods[] = {
	{ "declare", GenCode::declare, METH_VARARGS, "Declare a new file key"},
  { "use", GenCode::usekey, METH_VARARGS, "Use a new subkey"},
  { "line", GenCode::line, METH_VARARGS, "Add a code line"},
  { "code", GenCode::block, METH_VARARGS, "Add a code block"},
  { "kexp", GenCode::keycode, METH_VARARGS, "Expand a key"},
  { "file", GenCode::filename, METH_VARARGS, "Set filename to key"},
  { "garbage", GenCode::garbage, METH_VARARGS, "Add a code block"},
  { "getmodel", GenCode::getmodel, METH_VARARGS, "Get the model"},
  { "prefix", GenCode::prefixes, METH_VARARGS, "Define the block comments"},
  { "error", GenCode::error, METH_VARARGS, "Raise an error"},
	{ NULL, NULL, 0, NULL }
};

GenCode::GenCode()
{
  startprefix="//+";
  endprefix="//-";
  Py_SetProgramName((char*)"GenCode");
  Py_Initialize();
  Py_InitModule("gc", methods);
}

GenCode::~GenCode()
{
  Py_Finalize();
}




bool GenCode::generateCode(Var &v)
{  
  model=&v;
  String file=Glob::resPath()+"GenCode.pcg";
  SPyObject model(PyDict_New());
  //PyDict_SetItemString(model, "model", varToPython(v));
  onError = false;

  String script;
  try
  {
    script = Text::readFile(file);
  }
  catch (Exception &e)
  {
    String s = "GenCode fails with error : ";
    s+=e.what();
    MBox::error(s);
    return false;
  }
  if (PyRun_SimpleString(script.c_str())) {
    MBox::error("The script has returned an internal error");
  }
  if (onError) return false;
  
  return true;
}




PyObject* GenCode::varToPython(Var& v)
{
    if (v.isInteger())
    {
      PyObject * answ=PyInt_FromLong((long)v.getInt());
      return answ;
    }
    if (v.isFloat())
    {
      PyObject * answ= PyFloat_FromDouble(v.getFloat());
      return answ;
    }
    if (v.isBoolean())
    {
      if (v.getBoolean()) return Py_True;
      else Py_False;
    }
    if (v.isString())
    {
      String s=v.getString();
      PyObject *answ=PyString_FromString(s.c_str());
      return answ;
    }
    if (v.isArray())
    {
      PyObject *answ=PyList_New(v.getArray().size());
      int i=0;
      for (Var & w : v.getArray())
      {
        PyList_SetItem(answ,i++,varToPython(w));        
      }
      return answ;
    } 
    if (v.isContainer())
    {
      PyObject *answ=PyDict_New();
      for (auto & w : v.getContainer())
      {
        PyDict_SetItemString(answ,w.first.c_str(),varToPython(w.second)); 
      }
      return answ;
    }
    Py_RETURN_NONE;
}

PyObject* GenCode::declare(PyObject* self, PyObject* args)
{
  SPyObject arg;
	if(!PyArg_UnpackTuple(args, "declare", 1, 1, &arg)) Py_RETURN_NONE;
  
  char *a=PyBytes_AsString((PyObject*)arg);
  String root(a);
  auto fil=GenCode::instance->files.find(root);  
  if (fil==GenCode::instance->files.end()) 
  {
    // key not found add key
    (GenCode::instance->files)[root]=FStruct();
    GenCode::instance->root=& ((GenCode::instance->files)[root]);
  }
  else
  {
    GenCode::instance->root=&(fil->second);
  }
  FStruct *fs=GenCode::instance->root;
  auto ks=fs->lines.find("");
  if (ks==fs->lines.end())
  {
    (fs->lines)[""]=Vector<Row>();
    GenCode::instance->key=&((fs->lines)[""]);
    Py_RETURN_NONE;
  }
  GenCode::instance->key=&(ks->second);
  Py_RETURN_NONE;
}

PyObject* GenCode::usekey(PyObject* self, PyObject* args)
{
  SPyObject arg;
	if(!PyArg_UnpackTuple(args, "", 1, 1, &arg)) Py_RETURN_NONE;
  char *a=PyBytes_AsString((PyObject*)arg);  
  if (!GenCode::instance->root) Py_RETURN_NONE;
  String key=a;
  FStruct *fs=GenCode::instance->root;
  auto ks=fs->lines.find(key);
  if (ks==fs->lines.end())
  {
    (fs->lines)[key]=Vector<Row>();
    GenCode::instance->key=&((fs->lines)[key]);
    Py_RETURN_NONE;
  }
  GenCode::instance->key=&(ks->second);   
  Py_RETURN_NONE;
}

PyObject* GenCode::line(PyObject* self, PyObject* args)
{
  SPyObject arg;
	if(!PyArg_UnpackTuple(args, "", 1, 1, &arg)) Py_RETURN_NONE;
  char *a=PyBytes_AsString((PyObject*)arg);  
  if (!GenCode::instance->key) Py_RETURN_NONE;
  Row r;
  r.type=RLine;
  r.value=a;
  GenCode::instance->key->push_back(r);  
  Py_RETURN_NONE;
}

PyObject* GenCode::block(PyObject* self, PyObject* args)
{
  SPyObject arg;
	if(!PyArg_UnpackTuple(args, "", 1, 1, &arg)) Py_RETURN_NONE;
  char *a=PyBytes_AsString((PyObject*)arg);  
  if (!GenCode::instance->key) Py_RETURN_NONE;
  Row r;
  r.type=RBlock;
  r.value=a;
  GenCode::instance->key->push_back(r);  
  Py_RETURN_NONE;
}

PyObject* GenCode::keycode(PyObject* self, PyObject* args)
{
  SPyObject arg;
	if(!PyArg_UnpackTuple(args, "", 1, 1, &arg)) Py_RETURN_NONE;
  char *a=PyBytes_AsString((PyObject*)arg);  
  if (!GenCode::instance->key) Py_RETURN_NONE;
  Row r;
  r.type=RKey;
  r.value=a;
  GenCode::instance->key->push_back(r);  
  Py_RETURN_NONE;
}




PyObject* GenCode::garbage(PyObject* self, PyObject* args)
{
  Row r;
  r.type=RGarbage;
  GenCode::instance->key->push_back(r);  
  Py_RETURN_NONE;
}


PyObject* GenCode::filename(PyObject* self, PyObject* args)
{
  SPyObject arg;
	if(!PyArg_UnpackTuple(args, "", 1, 1, &arg)) Py_RETURN_NONE;
  char *a=PyBytes_AsString((PyObject*)arg);  
  if (!GenCode::instance->root) Py_RETURN_NONE;
  String realname=Glob::composePath(GFrame::getInstance().getProjectPath(),a);
  Glob::makePath(realname);
  GenCode::instance->root->name=realname;
  Py_RETURN_NONE;
}


PyObject* GenCode::error(PyObject* self, PyObject* args)
{
  SPyObject arg;
  GenCode::instance->onError=true;
	if(!PyArg_UnpackTuple(args, "", 1, 1, &arg)) Py_RETURN_NONE;
  char *a=PyBytes_AsString((PyObject*)arg);  
  MBox::error(String(a));
  Py_RETURN_NONE;
}

PyObject* GenCode::prefixes(PyObject* self, PyObject* args)
{
  SPyObject arg1,arg2;
	if(!PyArg_UnpackTuple(args, "", 2, 2, &arg1,&arg2)) Py_RETURN_NONE;
  GenCode::instance->startprefix=PyBytes_AsString((PyObject*)arg1);  
  GenCode::instance->endprefix=PyBytes_AsString((PyObject*)arg2);
  Py_RETURN_NONE;
}


void GenCode::preserveCode(String & name)
{
  String text;
  try {
    text = Text::readFile(name);
  }
  catch (Exception &e)
  {
    return;
  }
  oldFile=Text::split(text,"\n");
  String currentkey="";
  for (String &s : oldFile)
  {
    String ts=Text::trimLeft(s," \t");
    if (currentkey=="")
    {
      if (ts.find(startprefix)==0)
      {
        currentkey=Text::trimRight(ts.substr(startprefix.size())," \t\r\n");
        codeBlocks[currentkey]=Vector<String>();
      }
    }
    else
    {
      if (ts.find(endprefix+currentkey)==0)
      {
        currentkey="";
      }
      else
      {
        codeBlocks[currentkey].push_back(s);
      }      
    }    
  }
}

void GenCode::writeFiles()
{
    for (auto & fs  : files)
    { 
#ifdef WINDOWS_PORTING
      // In order to maintain a single script we use the "posix" folder conventions, so in windows, we need
      // to change all the slashes with backslashes
      String realName = Text::replace(fs.second.name, "/", "\\");
#else // I suppse this is always valid if it is not windows
      String realName = fs.second.name;
#endif
      bool fileExists = Glob::fileExists(realName);
      if (fileExists) preserveCode(realName);
      std::ofstream outFile;           
      Vector<String> fill;
      auto keyfind=fs.second.lines.find("");
      if (keyfind!=fs.second.lines.end())
      {    
        forward(0,fill,fs.second,(*keyfind).second);
        if (fileExists)
        {
          if (fill==oldFile) continue; // The files matches, we don't need to overwrite
          if (!Glob::makeBackup(realName)) {
            String err = "Failed to create a backup of ";
            err += realName;
            err += " , aborted !";
            MBox::error(err);
            return;
          }
        }
        else
        {
          Glob::makePath(realName);
        }
        String join;         
        for(String & s : fill)
        {
          join += s;
          join += "\n";
        }
        try 
        {
          Text::writeFile(realName, join);
        }
        catch (Exception &e)
        {
          String err = "Failed to save ";
          err += realName;
          err += " , aborted !";
          MBox::error(err);
          return;
        }
      }
    }
}

void GenCode::forward(unsigned indent, Vector<String> &fill,FStruct& root, Vector<Row>& key)
{
  for ( Row & row  : key)
  {
    switch(row.type)
    {
      case RLine:
        fill.push_back(String(indent,' ')+row.value);
        break;
      case RBlock:
      {
        String r=row.value;
        unsigned pos=row.value.find_first_not_of(" \t");
        if (pos==String::npos) break;
        String key=Text::trim(row.value.substr(pos)," \t\n\r");
        auto cb=codeBlocks.find(key);
        fill.push_back(startprefix+key);
        if (cb!=codeBlocks.end())
        {
          for (String & c: cb->second)
          {
            fill.push_back(c);
          }
          codeBlocks.erase(cb);
        }
        fill.push_back(endprefix+key);        
      }
      break;
      case RGarbage:
      {
        for (auto & cb:codeBlocks)
        {
          fill.push_back(startprefix+cb.first);        
          for (String & c: cb.second)
          {
            fill.push_back(c);
          }
          fill.push_back(endprefix+cb.first);        
        }
        codeBlocks.clear();
      }
      break;
      case RKey:
      {
        String r=row.value;
        unsigned pos=row.value.find_first_not_of(" \t");
        if (pos==String::npos) break;
        String key=Text::trim(row.value.substr(pos)," \t\n\r");
        auto keyfind=root.lines.find(key);
        if (keyfind==root.lines.end()) break;
        forward(indent+pos, fill,root, keyfind->second); 
      }
      break;
        
    }
  }
}

PyObject* GenCode::getmodel(PyObject* self, PyObject* args)
{
  return GenCode::instance->varToPython(*(GenCode::instance->model));
}
