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
#include "JSONParser.h"


GenCode *GenCode::instance=nullptr;



GenCode::Method methods[] = {
	{ "gc_declare", GenCode::declare, DUK_VARARGS},
  { "gc_use", GenCode::usekey, DUK_VARARGS},
  { "gc_line", GenCode::line, DUK_VARARGS},
  { "gc_code", GenCode::block, DUK_VARARGS },
  { "gc_kexp", GenCode::keycode, DUK_VARARGS },
  { "gc_file", GenCode::filename, DUK_VARARGS },
  { "gc_garbage", GenCode::garbage, DUK_VARARGS },
  { "gc_prefix", GenCode::prefixes, DUK_VARARGS },
  { "gc_error", GenCode::error, DUK_VARARGS },
  { "gc_log", GenCode::logger, DUK_VARARGS },
  { NULL, NULL, 0 }
};

void GenCode::execWithErrors(String & exec)
{
  onError = false;
  if (duk_peval_lstring(ctx, exec.c_str(), exec.size()) != 0) 
    if (!onError) 
    {
      String msg("Internal Error : ");
      msg += duk_safe_to_string(ctx, -1);
      MBox::error(msg);
      onError = true;
    }
  duk_pop(ctx);
}

void GenCode::loadMethods(Method * meth)
{
  while (meth->signature)
  {
    duk_push_c_function(ctx, meth->funct, meth->args);
    duk_put_global_string(ctx, meth->signature);
    ++meth;
  }
}

GenCode::GenCode()
{
  startprefix="//+";
  endprefix="//-";
  ctx = duk_create_heap_default();
  loadMethods(methods);
}

GenCode::~GenCode()
{
  duk_destroy_heap(ctx);
}




bool GenCode::generateCode(Var &v)
{  

  // Load Model (JSON)
  String topush("model=");
  topush += JSONParser::toString(v);
  topush += ";";
  execWithErrors(topush);
  if (onError) return false;

  String file=Glob::resPath()+"GenCode.js";
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
  execWithErrors(script);
  if (onError) return false;

  return true;
}




duk_ret_t GenCode::declare(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  String root(duk_to_string(ctx, 0));
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
    return 0;
  }
  GenCode::instance->key=&(ks->second);
  return 0;
}

duk_ret_t GenCode::usekey(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  if (!GenCode::instance->root) return 0;
  String key(duk_to_string(ctx, 0));
  FStruct *fs=GenCode::instance->root;
  auto ks=fs->lines.find(key);
  if (ks==fs->lines.end())
  {
    (fs->lines)[key]=Vector<Row>();
    GenCode::instance->key=&((fs->lines)[key]);
    return 0;
  }
  GenCode::instance->key=&(ks->second);   
  return 0;
}

duk_ret_t GenCode::line(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  if (!GenCode::instance->key) return 0;
  Row r;
  r.type=RLine;
  r.value= duk_to_string(ctx, 0);
  GenCode::instance->key->push_back(r);  
  return 0;
}

duk_ret_t GenCode::block(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  if (!GenCode::instance->key) return 0;
  Row r;
  r.type=RBlock;
  r.value = duk_to_string(ctx, 0);
  GenCode::instance->key->push_back(r);
  return 0;
}

duk_ret_t GenCode::keycode(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  if (!GenCode::instance->key) return 0;
  Row r;
  r.type=RKey;
  r.value = duk_to_string(ctx, 0);
  GenCode::instance->key->push_back(r);
  return 0;
}

duk_ret_t GenCode::logger(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  std::cout << duk_to_string(ctx, 0) << "\n";
  return 0;
}


duk_ret_t GenCode::garbage(duk_context *ctx)
{
  Row r;
  r.type=RGarbage;
  GenCode::instance->key->push_back(r);  
  return 0;
}


duk_ret_t GenCode::filename(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  if (!GenCode::instance->root) return 0;
  String realname=Glob::composePath(GFrame::getInstance().getProjectPath(), duk_to_string(ctx, 0));
  Glob::makePath(realname);
  GenCode::instance->root->name=realname;
  return 0;
}


duk_ret_t GenCode::error(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  GenCode::instance->onError=true;
  MBox::error(String(duk_to_string(ctx, 0)));
  return 0;
}

duk_ret_t GenCode::prefixes(duk_context *ctx)
{
  int  i = duk_get_top(ctx);
  if (i != 1) return 0;
  GenCode::instance->startprefix= duk_to_string(ctx, 0);
  GenCode::instance->endprefix= duk_to_string(ctx, 1);
  return 0;
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

