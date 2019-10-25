/*********************************************************************
* GENCODE C Code Generator for SunRiZe
* (c) Copyright 2017 by Marco Spreafico ( https://theing.blogspot.com )
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/


function gc_codeblock(value)
{
  gc_code(value+"*/");
}

function error( msg ) 
{
  gc_error(msg);
  // This is a fake function that is undefined
  // as error this will stop the program
  stop_the_program();
}

DFS_Full={};
DFS_Result=[];
//Tokens Collect
C_TOKENS={};

function DFS_visit(name)
{
  var value=DFS_Full[name];
  if (value[0]==1)
  {
    // Ignoring cyclic dependencies
    return;
  }
  if (value[0]==0)
  {
    value[0]=1;
    var lst=value[1];
    for (var key in lst)
	  {
      DFS_visit(lst[key]);
	  }
    value[0]=2;
    DFS_Result.splice(0,0,name);
  }
}

function DFS_create()
{
  var flag=true;
  while(flag)
  {
    flag=false;
    for (key in DFS_Full)
	  {
      if (DFS_Full[key][0]==0)
	    {
        flag=true;
        DFS_visit(key);
	    }
	  }
  }
  gc_declare("MAIN_CODE");
  gc_use("INITCODE");
  for (name in DFS_Result)
  {
    gc_line(DFS_Result[name].capitalize()+"_Init();");
  }
}      
      
//Insert multiline comments doxygen compatible
function insertComment( indent, data )
{
  // Ignore empty comments
  if (data == undefined) return;
  if (data == "") return;
  var st=data.split('\n');
  gc_line(indent+"/**");
  for (var dt in st) gc_line(indent+" * "+st[dt]);
  gc_line(indent+" */");
}

//Insert indented multiline code 
function multiline( indent, data )
{
  if (data == undefined) return;
  if (data == "") return;
  var st=data.split('\n');
  for (var dt in st) gc_line(indent+st[dt]);
}

// Splits types declaration to manage
// the C arrays (not the pointers)

function splitType( data )
{
  var p=data.search(/\[.*\]/g);
  var v = [];
  if (p>=0)
  {
    v.push(data.substring(0,p));
    v.push(data.substring(p));
    return v;
  }
  v.push(data);
  v.push("");
  return v;
}    

// Generate the FSM
function generateAutoma( node )
{
  
  var arg=node.schema;
  var name=arg.name;
  var auto=node.context;
  
  gc_declare('CODE_'+name);
    
  // Time reference
  gc_use("imp_attrib");
  gc_line("");
  gc_line("TIMER_DEFINITION("+name+"_Timer)");
  gc_line("");
  // States Enumeration
  gc_line("static enum");
  gc_line("{");
  gc_kexp("  enum_states");
  gc_line("} "+name+"_State;");  
  gc_line("");
  //  Main switch case  
  gc_use("run_keycode")
  gc_line("switch( "+name+"_State )");
  gc_line("{");
  gc_kexp("  doaction_global_switches");
  gc_line("}");
  gc_line("");
  
  var stateTime={};
  var condList={};
  var stateList={};
  var headcomma="";
  var statesGuard = {};
  var curKey = "";
 
  // Content Analyzer
  for (var ii in auto)
  {    
    var i=auto[ii];      
    stateList[i.id]=i;
    st=i.schema;
    
    // State FOUND
    if (i.model=="state")
    {
      if (statesGuard[st.name])
        error("Duplicated state name"+st.name+" in "+name);
      else
        statesGuard[st.name]=true;
      
      // State enumeration
      gc_use('enum_states');
      gc_line(headcomma+"State_"+st.name);      
      headcomma=",";
      
      gc_use('doaction_global_switches');
      gc_line("case State_"+st.name+":");      
      
      // Do Action
      if (st.doaction!="")
        multiline("  ",st.doaction);
      
      // Extra doaction_state_(num)
      gc_kexp("  doaction_state_" + i.id);
      gc_line("break;");
    
      // Entry Action
      gc_use('entryaction_' + i.id);
      // Reset Timer if required
      gc_kexp("resettimer_" + i.id);      
      if (st.entryaction!="")      
        multiline("",st.entryaction);

      // Exit Action
      if (st.exitaction!="")
      {        
        gc_use('exitaction_' + i.id);
        multiline("",st.exitaction);
      }


    }  
    // Condition Code
    else if (i.model=="condition")
    {     
      // The entry action of a condition is a branch
      gc_use('entryaction_' + i.id);
      // Conditional execution
      gc_kexp('branch_condition_' + i.id);
      // Uncoditional execution (else)
      gc_kexp('branch_end_' + i.id);
    }
    // Transition Code
    else if (i.model=="transition")
    {
      
      // Get the origin and the end
      side0=stateList[i.source];
      side1=stateList[i.destination];
                     
      // If the origin is the INIT everything goes into the constructor (init)
      if (side0.model=="initstate")
      {
        curKey='constructor_code';
        if (stateTime[side1.id]==undefined)
        {
          stateTime[side1.id]=true;
          gc_use("resettimer_"+side1.id);
          gc_line("TIMER_RESET("+name+"_Timer)");
        }
      }  
      // If the origin is a condition
      else if (side0.model=="condition")
      {
        // Check the condition
        // Undefined ?
        if (condList[side0.id]==undefined)
        {          
          if (st.guard=="")
          {
            // Ok this is a free transtion
            condList[side0.id]=true;           
          }            
          else
          {
            //Not empty transitions
            condList[side0.id]=false;
          }
        }
        else
        {
          if (st.guard=="")
          {
            if (condList[side0.id])
              error("A Condition must have at most one unguarded exiting transition");
            else
              // Found empty transition
              condList[side0.id]=false;
          }
        }
  
        if (st.guard!="")
        {
          gc_use("branch_condition_" + side0.id);                  
          gc_kexp("branch_condition_"+side0.id+"_"+i.id);
          curKey="branch_condition_"+side0.id+"_"+i.id;
        }
        else
        {
          // Empty guard
          curKey="branch_end_" + side0.id;
        }

      }
      // If the origin is a state
      else if (side0.model=="state")
      {
        gc_use("doaction_state_" + side0.id);
      
        if (st.event>1)
        {
          if (st.token=="")
            error("A Transition exiting from %s has a null token" % side0['schema']['name']);
          var tok=C_TOKENS[st.token];  
          gc_line("TOKEN_CHECK(Token_"+tok.name+")");
          gc_line("{" );
          if (tok.limit=='')
            gc_line("  TOKEN_USE(Token_"+tok.name+")"); 
          else
            gc_line("  TOKEN_USE_LIMIT(Token_"+tok.name+","+tok.limit+")");             
        }
        else if (st.event==0)
        {
          if (st.condition=="")
            error("A Transition exiting from "+side0.schema.name+" has a null condition" );
          gc_line("if ("+st.condition+")");
          gc_line("{" );
        }
        else
        {
          if (st.time=="")
            error("A Transition exiting from "+side0.schema.name+" has a null time");
          gc_line("TIMER_TIMEOUT("+name+"_Timer,"+st.time+")");
          gc_line("{" );
        } 
        gc_kexp("  transition_code_" + i.id);
        gc_line("  break;" );
        gc_line("}" );
        curKey='transition_code_' + i.id;
      }
      // Guard condition on transition
      gc_use(curKey);
      if (st.guard!="")
      {
        gc_line("if ( "+st.guard+" )");
        gc_line("{" );
        gc_kexp("  "+curKey+"_central");
        gc_line("  break;");
        gc_line("}" );
      }
      else
      {
        gc_kexp(curKey+"_central");
      }
      
      // Implementing state transition
      if (side0.model=="state")
      {
        gc_use(curKey+"_central");
        gc_kexp("exitaction_" + side0.id);
        if (st['event']==1)
        {
          if (stateTime[side0.id]==undefined)
          {
            stateTime[side0.id]=true;
            if (!st.follower)
            {
              gc_use("resettimer_"+side0.id);
              gc_line("TIMER_RESET("+name+"_Timer)");
            }
          }
        }      
      }   
      gc_use(curKey+"_central");
      
      if (st.action!="")
        multiline("",st.action);

      if (side1.model=="state")
      {
        gc_line("TRACE_STATE("+name+","+side1.schema.name+")"  );            
        gc_line(name+"_State = State_"+side1.schema.name+";");
      }
      gc_kexp("entryaction_" + side1.id)
    }    
  } 
}


String.prototype.capitalize = function() {
    return this.replace(/(?:^|\s)\S/g, function(a) { return a.toUpperCase(); });
};

// Generate Module

function generateModule( data ) 
{
  var arg=data.schema;
  var name=arg.name;
  var nm = name.toLowerCase();

  if (moduleGuard[nm]!=undefined)
  {
    if (moduleGuard[nm])
      error("Duplicated module name : "+name);
    else
      error("Reserved module name : "+name);
  }
  else moduleGuard[nm]=true;       
  
  // Code
  gc_declare('MAIN_CODE');
  gc_use("imp_attrib");
  // The file names are always capitalized
  gc_line("#include \""+name.capitalize()+".h\"");  
  //Declaring the header skeleton
  gc_declare('HEAD_'+name);
  gc_file("include/"+name.capitalize()+".h");
  gc_line("#ifndef "+name.toUpperCase()+"_H" );
  gc_line("#define "+name.toUpperCase()+"_H" );
  gc_line("#include \"commons.h\"" );
  gc_code("HEADER_PREFIX");
  gc_kexp("head_attrib" );
  gc_kexp("head_code" );
  gc_code("HEADER_POSTFIX");
  gc_line("#endif /*"+name.toUpperCase()+"_H*/" );
  gc_line("#if 0");
  gc_garbage();
  gc_line("#endif");
  
  // Code skeleton
  gc_declare("CODE_"+name);
  insertComment("",arg.comment);
  gc_file("src/"+name.capitalize()+".c");
  gc_kexp("include_imp");
  gc_code("USER_INCLUDES");
  gc_line("");
  gc_kexp("global_linking");
  gc_kexp("imp_attrib");
  gc_kexp("imp_tokens");
  gc_kexp("imp_declarations");  
  gc_line("");
  gc_code("BODY_PREFIX");
  gc_kexp("imp_code");
  gc_code("BODY_POSTFIX");
  gc_line("");
  gc_line("#if 0");
  gc_garbage();
  gc_line("#endif");

  // Include files
  gc_use("include_imp")
  for (var dep in data.dependencies)
    gc_line('#include "'+data.dependencies[dep]+'.h"');
  gc_line('#include "'+name+'.h"');
  
  var attopGuard={};
  attopGuard['State']=false;
  attopGuard['Timer']=false;
  // Attributes 
  for (var at in arg.attributes)
  {
    var att=arg.attributes[at];
    if (att.visibility==1)
    {
      na=att.name;
      if (attopGuard[na]!= undefined)
        error("Duplicated or reserved attribute name "+na+" in "+ name );
      else
        attopGuard[na]=false;
    } 
    
    volatil="";
    if (att.volatile) volatil="volatile ";

          
    v=splitType(att.type);
      
    gc_declare("CODE_"+name);
    gc_use("imp_attrib");
    ifValue="";
    
    if (att.value!="")        
      ifValue=" = "+att.value;
    
    if (att.visibility==0)
    {
      //Private
      insertComment("",att.comment);
      if (v[1]=="")
        gc_line(volatil+"static "+v[0]+" "+att.name+ifValue+";");
      else
        gc_line(volatil+"static "+v[0]+" "+att.name+v[1]+ifValue+";");
    }
    else
    {
      //Public
      insertComment("",att.comment);
      if (v[1]=="")
      {
        gc_line(volatil+v[0]+" "+att.name+ifValue+";");
        gc_declare('HEAD_'+name) 
        gc_use("head_attrib" )
        gc_line("extern "+volatil+v[0]+" "+name+"_"+att.name+";");
      }
      else
      {
        gc_line(volatil+v[0]+" "+att.name+v[1]+ifValue+";");
        gc_declare('HEAD_'+name) 
        gc_use("head_attrib" )
        gc_line("extern "+volatil+v[0]+" "+name+"_"+att.name+v[1]+";");
      }
      gc_declare("CODE_"+name)
      gc_use("global_linking")
      gc_line("#define " + att.name + " " + name + "_" + att.name);
    }
  }

  // Operations
  
  // Do we need a constructor ?
  if ((arg.hasinit) || (data.context!=undefined))
  {    
    gc_declare("HEAD_"+name);
    gc_use("head_code");
    gc_line("void "+name+"_Init();");
    
    gc_declare("CODE_"+name);
    gc_use("imp_code");
    gc_line("void "+name+"_Init()");
    gc_line("{");
    gc_line("TRACE_FUNCTION("+name+","+name+"_Init)");
    gc_code("Init_definitions");  
    gc_kexp("  constructor_code");
    gc_code("Init_code");  
    gc_line("}");
    gc_line("");
    attopGuard.Init=true;
    if (data.context!=undefined)    
      attopGuard.Run=true;
  }   
  
  for (var op in arg.operations)
  {
    
    var ope=arg.operations[op];
    
    if (ope.visibility==1) 
    {      
      var na=ope.name;
      if (attopGuard[na]!=undefined)
      {
        if (attopGuard[na])
          error("Duplicated or reserved operation name "+na+" in "+ name );
        else
          error("An operation has the same name of an attribute "+na+" in "+ name );        
      }
      else
        attopGuard[na]=true
    }
     
    var op=ope.type+" "+ope.name;
    var opglob=ope.type+" "+name+"_"+ope.name;
    if (ope.visibility==0)
      op="static "+op;
    
    
    var opx="( ";
    var bp="";
    var comment = ope.comment;
   
    for (var pr in ope.parameters)
    {
      prm=ope.parameters[pr];
      v=splitType(prm.type);
      opx+=bp+v[0]+" "+prm.name+v[1];
      bp=" , ";
    }
    
    opx=opx+" )";
    op+=opx;
    opglob+=opx;
  
    if (ope.visibility==0)
    {
      // Private
      gc_declare("CODE_"+name);
      gc_use("imp_declarations");
      gc_line(op+";");
      gc_declare("CODE_"+name);
    }
    else 
    {
      // Public
      gc_declare("HEAD_"+name);
      gc_use("head_code");
      gc_line(opglob+";");
      gc_declare("CODE_"+name);
      gc_use("global_linking");
      gc_line("#define "+ope.name+" "+name+"_"+ope.name);
    }
    
    gc_use("imp_code");
    insertComment("",comment);      
    gc_line(op);
    gc_line("{");
    gc_line("TRACE_FUNCTION("+name+","+ope.name+")");
    gc_code(ope.name+"_code");
    gc_line("}");
    gc_line("");
  }
  
  // Tokens
  for (var tk in arg.tokens)
  {
    var tok=arg.tokens[tk];
    if (C_TOKENS[tok.name]!=undefined)
      error("Duplicate token name "+tok.name+" in project");
    else
      C_TOKENS[tok.name]=tok;
    // Put in token list
    if (tok.type==0)
    {
      // Counters
      gc_declare("TOKENS");
      gc_use("tokens_list");
      insertComment("",tok.comment);
      gc_line("TOKEN_REFERENCE(Token_"+tok.name+")");
      gc_declare("CODE_"+name);
      gc_use("imp_tokens");
      gc_line("TOKEN_DEFINITION(Token_"+tok.name+")");
    }
    else
    {
      // Signals
      gc_declare("CODE_"+name);
      gc_use("imp_tokens");
      gc_line("TOKEN_SIGNAL_DEFINITION(Token_"+tok.name+")");
      gc_declare("HEAD_"+name);
      gc_use("head_code");
      insertComment("",tok.comment);
      gc_line("void "+name+"_"+tok.name+"( );");
      gc_declare("CODE_"+name);
      gc_use("imp_code");
      gc_line("void "+name+"_"+tok.name+"( )");
      gc_line("{");
      gc_line("TRACE_FUNCTION("+name+","+tok.name+")");
      gc_code(tok.name+"_code");
      gc_line("  TOKEN_RAISE(Token_" + tok.name + ")");
      gc_line("}");
      gc_line("");
    }
  }

  // Optionally generate FSM code
  if (data["context"]!=undefined)
  {
    gc_declare("MAIN_CODE");
    gc_use("RUNCODE");
    gc_line(name+"_Run();");

    gc_declare("HEAD_"+name);
    gc_use("head_code");
    gc_line("void "+name+"_Run();");

    gc_declare("CODE_"+name);
    gc_use('imp_code');
    gc_line("void "+name+"_Run()");
    gc_line("{");
    gc_line("TRACE_FUNCTION("+name+","+name+"_Run)");  
    gc_code("Run_definitions");
    gc_kexp("  run_keycode");
    gc_line("}");
    gc_line("");
    generateAutoma(data);
  }
}

    
// Collect all the dependencies.
function collectDependencies()
{
  var items = {};
  for (var dt in model)
  {
    var data=model[dt]; 
    if (data.model=='module')
    {
      items[data.id]=data;
      data.dependencies=[];
      DFS_Full[data.schema.name]=[0, [] ];
    }
    if (data.model=='dependency')
	  {
      var src=items[data.source];
      var desName=items[data.destination].schema.name;
      src.dependencies.push(desName);
      if ((src.schema.hasinit) || (src.context!=undefined))
	      DFS_Full[desName][1].push( src.schema.name );	
	  }
  }
}      

  
function preModel()
{
  // Model
  gc_declare("MAIN_CODE");
  gc_file("src/model.c");
  gc_kexp("include_imp");
  gc_code("USER_INCLUDES");
  gc_line("");  
  insertComment("","Model stub produced by SunRiZe");
  gc_kexp("imp_attrib");
  gc_kexp("imp_declarations");  
  gc_line("");  
  gc_code("BODY_PREFIX");
  gc_line("void model_init()" );  
  gc_line("{" );
  gc_kexp("  INITCODE");  
  gc_line("}" );
  gc_line("" );
  gc_line("void model_run()" );  
  gc_line("{" );
  gc_kexp("  RUNCODE");  
  gc_line("}" );
  gc_line("" );
  gc_code("BODY_POSTFIX");
  gc_line("");
  gc_line("#if 0");
  gc_garbage();
  gc_line("#endif");  
  // Tokens
  gc_declare('TOKENS'); 
  gc_file("include/tokens.h");
  gc_line("#ifndef __TOKENS_H" );
  gc_line("#define __TOKENS_H" );
  gc_kexp("tokens_list" );
  gc_line("#endif /*__TOKENS_H*/" );
}

Duktape.errCreate = function (err) {
  try {
    if (typeof err === 'object' &&
      typeof err.message !== 'undefined' &&
      typeof err.lineNumber === 'number') {
      err.message = "Script Error ("+err.lineNumber+") : "+err.message ;
    }
  } catch (e) {
    // ignore; for cases such as where "message" is not writable etc
  }
  return err;
}


try {
  // Main Program      
  moduleGuard = {};
  moduleGuard.commons = false;
  moduleGuard.tokens = false;
  moduleGuard.token = false;
  moduleGuard.defines = false;
  moduleGuard.model = false;

  gc_prefix("/*@@+", "/*@@-");
  preModel();
  collectDependencies();
  for (var ind in model)
    if (model[ind].model == 'module')
      generateModule(model[ind]);
  DFS_create();
} catch (e)
{
  gc_error(e.message);
}
