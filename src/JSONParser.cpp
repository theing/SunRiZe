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

#include "JSONParser.h"


const char * parseerror="parse error";


JSONParser::JSONParser()
{

}

JSONParser::~JSONParser()
{
}


String JSONParser::toString(Var & val)
{ 
  
  if (val.isArray()) {
    String s;
    if (val.getArray().empty()) return String("[]");
    char comma='[';
    for(Var & y : val.getArray() ) {
      s+=comma;
      comma=',';
      s+=toString(y);
    }
    s+="]";
    return s;
  }
  if (val.isContainer()) {
    String s;
    if (val.getContainer().empty()) return String("{}");
    char comma='{';
    for(auto & y : val.getContainer() ) {
      s+=comma;
      comma=',';
      s+="\""+rencodeStr(y.first)+"\":";
      s+=toString(y.second);
    }
    s+="}";
    return s;    
  }
  if (val.isString()) {
    String s="\""+rencodeStr(val.getString())+"\"";
    return s;  
  }
  if (val.isBoolean()) {
    return (val.getBoolean() ? "true" : "false") ;
  }
  if (val.isNull()) {
    return "null";
  }
  if (val.isFloat()) {
    std::stringstream y;
    y << val.getFloat() ;
    return y.str();
  }
  if (val.isInteger()) {
    std::stringstream y;
    y << val.getInt() ;
    return y.str();
  }
  return "";
  
}


String JSONParser::rencodeStr(String s)
{
  String h;
  for (unsigned i=0;i<s.size();++i) {
    uint8_t ch= (uint8_t) s.at(i);
    
    switch(ch){
      case '\\': h+="\\\\"; break;
      case '\"': h+="\\\""; break;
      case '\n': h+="\\n"; break;
      case '\b': h+="\\b"; break;
      case '\f': h+="\\f"; break;
      case '\r': h+="\\r"; break;
      case '\t': h+="\\t"; break;      
      default:
      {
        if ( ((ch>=0)&&(ch<0x20)) ||(ch==0x7f)) {
          // Unicode characters are always over 0x80
          char x[8];
          sprintf(x,"\\u%04X",ch);
          h+=x;
        }    
        else if ((ch&0xe0)==0xc0) // two char utf8
        {      
          ++i;
          if (i<s.size()) {
            uint8_t ch1 = (uint8_t) s.at(i);
            if ( (ch1&0xc0) ==0x80) {
              uint16_t v=( ( ((uint16_t)ch) & 0x1f ) << 6 ) | ( ((uint16_t)ch1) & 0x3f );
              char x[8];
              sprintf(x,"\\u%04X",v);
              h+=x;      
            }
          }
        }
        else if ( (ch&0xf0) ==0xe0) // 3 char utf8
        {      
          i+=2;
          if (i<s.size()) {
            uint8_t ch1 = (uint8_t) s.at(i-1);
            uint8_t ch2 = (uint8_t) s.at(i);
            if (((ch1&0xc0)==0x80)&&((ch2&0xc0)==0x80)) {
              uint16_t v= ( (((uint16_t)ch) & 0x0f ) << 12 ) | ( (((uint16_t)ch1) & 0x3f) << 6 ) | ( ((uint16_t)ch2) & 0x3f );
              char x[8];
              sprintf(x,"\\u%04X",v);
              h+=x;          
            }
          }
        }
        else h+=(ch&0x7f);
      }
    }
  }    
    
  return h;
}



// Only 16 bit are supported
String JSONParser::toUTF8(unsigned v)
{
  uint8_t t[4];
  if (v<0x80) {
    t[0]=(char) v;
    return String((const char *)t,1);
  }
  if (v<0x800) {
    t[0]=0xc0|(v>>6);
    t[1]=0x80|(v&0x3f);
    return String((const char *)t,2);
  }
  t[0]=0xe0|(v>>12);
  t[1]=0x80|((v>>6)&0x3f);
  t[2]=0x80|(v&0x3f);
  return String((const char *)t,3);    
}



void JSONParser::ignoreBlank() 
  {
    while(strchr(" \n\t\r",tp[p]))
    {
      ++p;
      if (p>=tp.size()) throw Exception(parseerror);      
    }
  }
  
  bool JSONParser::last()
  {
    if (p>=tp.size()-1) return true;
    return false;
  }
  
  
  char JSONParser::next()
  {
    if (p>=tp.size()-1) throw Exception(parseerror);
    return tp[++p];  
  }
  
  char JSONParser::nextNB()
  {
    do
    {
      ++p;
      if (p>=tp.size()) throw Exception(parseerror);      
    }
    while(strchr(" \n\t\r",tp[p]));
    return tp[p];
  }
  
  
  char JSONParser::current()
  {
    if (p>=tp.size()) throw Exception(parseerror);
    return tp[p];
  }
  
  void JSONParser::forward()
  {
    ++p;
  }
  

  Var JSONParser::parseArray()
  {
    Var v;
    v.newArray();
    nextNB();
    while(current()!=']')
    {
      Var v1=parseInit();
      v.getArray().push_back(v1);
      ignoreBlank();
      if (current()==',') nextNB();      
      else if (current()!=']') throw Exception(parseerror);      
    }
    forward();
    return v;
  }



  
  Var JSONParser::parseObject()
  {
    Var v;
    v.newContainer();
    nextNB();
    while(current()!='}')
    {
      if (current()!='\"') throw Exception(parseerror);      
      Var v1=parseString();
      ignoreBlank();
      if (current()!=':') throw Exception(parseerror);
      nextNB();
      Var v2=parseInit();
      v.getContainer()[v1.getString()]=v2;
      ignoreBlank();
      if (current()==',') nextNB();      
      else if (current()!='}') throw Exception(parseerror); 
    }
    forward();
    return v;
  }
  
  
  
  Var JSONParser::parseNumber()
  {
      String w;
      char ch=current();
      while(strchr("1234567890eE.+-",ch))
      {
        w.push_back(ch);
        if (last()) break;
        ch=next();
      }
      std::stringstream st(w);
      if ( (w.find('E')==String::npos)
      &&(w.find('e')==String::npos)
      &&(w.find('.')==String::npos) )
      {
          // Integer
          int64_t l;    
          if (!(st>>l)) throw Exception(parseerror);        
          Var jl(l);
          return jl;
      } else {
          // Floating point number
          double d;
          if (!(st>>d)) throw Exception(parseerror);          
          Var jd(d);
          return jd;
      }
  }
  
  void JSONParser::parseUnicode(String & s)
  {
    String w;
    char ch;
    for(int i=0;i<4;++i) 
    {
      ch=next();
      if (!(strchr("0123456789abcdefABCDEF",ch))) throw Exception(parseerror);
      w.push_back(ch);
    }
    unsigned val;
    sscanf(w.c_str(),"%x",&val);
    s+=toUTF8(val);  
  }
  
  
  void JSONParser::parseBackSlash(String & s)
  {
    char ch=next();
    if (ch=='u') {
        // Special UNICODE char 
        // NOTE : UTF-8 ONLY SUPPORTED
        parseUnicode(s);
      }
      else {
          switch (ch) {      
            case '\\': ch='\\'; break;
            case '\"': ch='\"'; break;
            case 'n': ch='\n'; break;
            case '/': ch='/'; break;
            case 'b': ch='\b'; break;
            case 'f': ch='\f'; break;
            case 'r': ch='\r'; break;
            case 't': ch='\t'; break;
          } 
          s.push_back(ch);
      }
  }
  
  Var JSONParser::parseString()
  {
    String value;
    char ch;
    while((ch=next())!='\"')
    {
      if (ch=='\\')
      {
        parseBackSlash(value);
      }
      else
      {
        value.push_back(ch);
      }
    }
    forward();
    return Var(value);
  }
  
  
  Var JSONParser::parseBool() 
  {
     String w;
     if (current()=='f')
     {
       for(int i=0;i<4;++i) w+=next();
       if (w!="alse") throw Exception(parseerror);       
       Var v(false);       
       forward();
       return v;
     }
     if (current()=='t')
     {
       for(int i=0;i<3;++i) w+=next();
       if (w!="rue") throw Exception(parseerror);       
       Var v(true);       
       forward();
       return v;
     }
     throw Exception(parseerror);       
  }
  
  Var JSONParser::parseNull() 
  {
     String w;
     for(int i=0;i<3;++i) w+=next();
     if (w!="ull") throw Exception(parseerror);       
     forward();
     return Var();
  }
  
  Var JSONParser::parseInit()
  {
    ignoreBlank();
    switch(current())
    {
      case '{':
        // Open Object
        {
          return parseObject();
        }
      case '[':
        {
          return parseArray();
        }
      case '\"':
        {
          return parseString();          
        }
      case 'f':
      case 't':
        {
          return parseBool();          
        }
      case 'n':
        {
          return parseNull();
        } 
    }
    if (strchr("-1234567890",current())) 
    {
        return parseNumber();
    }
    throw Exception(parseerror);
  }
  
  Var JSONParser::fromString(String s)
  {
    p=0;
    tp=s;
    return parseInit();
  }
