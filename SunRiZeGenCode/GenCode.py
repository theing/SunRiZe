######################################################################
# GENCODE C Code Generator for SunRiZe
# (c) Copyright 2017 by Marco Spreafico (TheIng).
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
######################################################################

import gc
gc.prefix("/*@@+","/*@@-");
model=gc.getmodel();


def gc_code(value) :
  gc.code(value+"*/")

def error( msg ) :
  gc.error(msg)
  exit()

# Depth First Sorting
DFS_Full={}
DFS_Result=[]

#Tokens Collect
C_TOKENS={}

def DFS_visit(name) :
  global DFS_Full
  global DFS_Result
  value=DFS_Full[name]
  if value[0]==1 :
    # Ignoring cyclic dependencies
    return
  if value[0]==0 :
    value[0]=1
    lst=value[1]
    for key in lst :
      DFS_visit(key)
    value[0]=2
    DFS_Result.insert(0,name) 

def DFS_create() :
  global DFS_Full
  global DFS_Result
  flag=True
  while(flag) :
    flag=False
    for key in DFS_Full :
      if DFS_Full[key][0]==0 :
        flag=True
        DFS_visit(key)
  gc.declare("MAIN_CODE")
  gc.use("INITCODE")
  for name in DFS_Result :
    gc.line(name.capitalize()+"_Init();");
      
    
# Collect all the dependencies.
def collectDependencies() :
  global model
  global DFS_Full
  items = {}
  for data in model :
    if data['model']=='module' :
      items[data['id']]=data
      data['dependencies']=[]
      DFS_Full[data['schema']['name']]=[0, [] ]
    if data['model']=='dependency' :
      src=items[data['source']]
      des=items[data['destination']]['schema']['name']
      src['dependencies'].append(des)
      if src['schema']['hasinit'] or src.has_key('context') :
        DFS_Full[des][1].append( src['schema']['name'] )   
      
      
#Insert multiline comments doxygen compatible
def insertComment( indent,data ) :
  st=data.split('\n')
  gc.line(indent+"/**")
  for dt in st :
    gc.line(indent+" * "+dt)
  gc.line(indent+" */")

#Insert indented multiline code 
def multiline( indent,data ) :
  st=data.split('\n')
  for dt in st :
    gc.line(indent+dt)

# Splits types declaration to manage
# the C arrays (not the pointers)
def splitType( data ) :
  p=data.find("[");
  if p>=0 :
    v=[]
    v.append(data[:p])
    v.append(data[p:])
    return v
  v=[]
  v.append(data)
  v.append("")
  return v
    

# Generate the FSM
def generateAutoma( node ) :
  
  arg=data['schema']
  name=arg['name']
  auto=data['context']
  
  gc.declare('CODE_'+name)
    
  
  # Time reference
  gc.use("imp_attrib")
  gc.line("");
  gc.line("TIMER_DEFINITION("+name+"_Timer)");
  gc.line("");
  # States Enumeration
  gc.line("static enum");
  gc.line("{");
  gc.kexp("  enum_states");
  gc.line("} "+name+"_State;");  
  gc.line("");
  
  # Main switch case  
  gc.use("run_keycode")
  gc.line("switch( "+name+"_State )");
  gc.line("{");
  gc.kexp("  doaction_global_switches");
  gc.line("}");
  gc.line("");
  
  stateTime={}
  condList={}
  stateList={}
  headcomma=""
  
  statesGuard={}
 
  # Content Analyzer
  for i in auto :    
        
    stateList[i['id']]=i;
    st=i['schema']
    
    # State FOUND
    if i['model']=="state" :
      
      if statesGuard.has_key(st['name']) :
        error("Duplicated state name"+st['name']+" in "+name)
      else :
        statesGuard[st['name']]=True;
      
      # State enumeration
      gc.use('enum_states')
      gc.line(headcomma+"State_"+st['name']);      
      headcomma=",";
      
      gc.use('doaction_global_switches')
      gc.line("case State_"+st['name']+":")      
      # Do Action
      if st['doaction']!="" :
        multiline("  ",st['doaction'])
      # Extra doaction_state_(num)
      gc.kexp("  doaction_state_%d" % i['id'])
      gc.line("break;")
    
      # Entry Action
      gc.use('entryaction_%d' % i['id'])
      # Reset Timer if required
      gc.kexp("resettimer_%d" % i['id'])      
      if st['entryaction']!="" :      
        multiline("",st['entryaction']);

      # Exit Action
      if st['exitaction']!="" :      
        gc.use('exitaction_%d' % i['id'])
        multiline("",st['exitaction']);
      
    # Condition Code
    elif i['model']=="condition" :
      
      # The entry action of a condition is a branch
      gc.use('entryaction_%d' % i['id'])
      # Conditional execution
      gc.kexp('branch_condition_%d'% i['id'])
      # Uncoditional execution (else)
      gc.kexp('branch_end_%d'% i['id'])

    # Transition Code
    elif i['model']=="transition" :
      
      # Get the origin and the end
      side0=stateList[i['source']];
      side1=stateList[i['destination']];
                     
      # If the origin is the INIT everything goes into the constructor (init)
      if side0['model']=="initstate" :
        curKey='constructor_code'
        if not stateTime.has_key(side1['id']) :
          stateTime[side1['id']]=True;
          gc.use("resettimer_%d"%side1['id'])
          gc.line("TIMER_RESET("+name+"_Timer)");
        
      # If the origin is a condition
      elif side0['model']=="condition" :
		
        # Check the condition
        # Undefined ?
        if not condList.has_key(side0['id']) :          
          if st['guard']=="" :
            # Ok this is a free transtion
            condList[side0['id']]=True;            
          else :
            # Not empty transitions
            condList[side0['id']]=False;            
        else :
          if st['guard']=="" :
            if condList[size0['id']] :
              error("A Condition must have at most one unguarded exiting transition");
            else :
              # Found empty transition
              condList[side0['id']]=False;
        
  
        if st['guard']!="" :
          gc.use("branch_condition_%d" % side0['id'])                  
          gc.kexp("branch_condition_%d_%d" % (side0['id'],i['id']))
          curKey="branch_condition_%d_%d" % (side0['id'],i['id'])
        else :
          # Empty guard
          curKey="branch_end_%d" % side0['id']
    
      # If the origin is a state
      elif side0['model']=="state" :
        gc.use("doaction_state_%d" % side0['id'])
      
        if st['event']>1 :
          if st['token']=="" :
            error("A Transition exiting from %s has a null token" % side0['schema']['name'])
          tok=C_TOKENS[st['token']]  
          gc.line("TOKEN_CHECK(Token_"+tok['name']+")");
          gc.line("{" );
          if tok['limit']=='' :
            gc.line("  TOKEN_USE(Token_"+tok['name']+")"); 
          else :
            gc.line("  TOKEN_USE_LIMIT(Token_"+tok['name']+","+tok['limit']+")");             
        elif st['event']==0 :
          if st['condition']=="" :
            error("A Transition exiting from %s has a null condition" % side0['schema']['name'])
          gc.line("if ("+st['condition']+")");
          gc.line("{" );
        else :
          if st['time']=="" :
            error("A Transition exiting from %s has a null time" % side0['schema']['name'])
          gc.line("TIMER_TIMEOUT("+name+"_Timer,"+st['time']+")");
          gc.line("{" );

        gc.kexp("  transition_code_%d" % i['id']);
        gc.line("  break;" );
        gc.line("}" );
        curKey='transition_code_%d' % i['id'];
      
      # Guard condition on transition
      gc.use(curKey)
      if st["guard"]!="" and st['event']==2 :
        gc.line("if ( "+st['guard']+" )");
        gc.line("{" );
        gc.kexp("  "+curKey+"_central");
        gc.line("  break;");
        gc.line("}" );
      else :
        gc.kexp(curKey+"_central");
    
      # Implementing state transition
      if side0['model']=="state" :
        gc.use(curKey+"_central")
        gc.kexp("exitaction_%d" % side0['id']);
        if st['event']==1 :
          if not stateTime.has_key(side0['id']) :
            stateTime[side0['id']]=True;
            if not st['follower'] :
              gc.use("resettimer_%d"%side0['id'])
              gc.line("TIMER_RESET("+name+"_Timer)");
            else :
              gc.use("exitaction_%d" % side0['id']);
              gc.line("TIMER_FOLLOW("+name+"_Timer,"+st['time']+")");
              gc.use(curKey+"_central")
              gc.use("follower_reset_%d" % side0['id'])              
              gc.line("TIMER_RESET("+name+"_Timer)");
              
          
      gc.use(curKey+"_central")
      
      if st['action']!="" :
        multiline("",st['action'])

      if side1['model']=="state" :
        gc.line("TRACE_STATE("+name+","+side1['schema']['name']+")"  )            
        gc.line(name+"_State = State_"+side1['schema']['name']+";")
      
      if st['event']==1 and not st['follower'] :
        gc.kexp("follower_reset_%d" % side1['id'])        
      gc.kexp("entryaction_%d" % side1['id'])


# Generate the MODULE

moduleGuard={}
moduleGuard['commons']=False;
moduleGuard['tokens']=False;
moduleGuard['token']=False;
moduleGuard['defines']=False;
moduleGuard['model']=False;


def generateModule( data ) :
  arg=data['schema']
  name=arg['name']
  
  nm=name.lower()
  if moduleGuard.has_key(nm) :
    if moduleGuard[nm] :
      error("Duplicated module name : "+name)
    else :
      error("Reserved module name : "+name)
  else :
    moduleGuard[nm]=True       
  
  
  gc.declare('MAIN_CODE')
  gc.use("imp_attrib")
  # The file names are always capitalized
  gc.line("#include \""+name.capitalize()+".h\"")
    
  # Declaring the header skeleton
  gc.declare('HEAD_'+name) 
  gc.file("include/"+name.capitalize()+".h")
  gc.line("#ifndef "+name.upper()+"_H" )
  gc.line("#define "+name.upper()+"_H" )
  gc.line("#include \"commons.h\"" )
  gc_code("HEADER_PREFIX")
  gc.kexp("head_attrib" )
  gc.kexp("head_code" )
  gc_code("HEADER_POSTFIX")
  gc.line("#endif /*"+name.upper()+"_H*/" )
  gc.line("#if 0");
  gc.garbage();
  gc.line("#endif");
  
  # Declaring the code skeleton
  gc.declare("CODE_"+name)
  insertComment("",arg['comment']);
  gc.file("src/"+name.capitalize()+".c")
  gc.kexp("include_imp")
  gc_code("USER_INCLUDES");
  gc.line("");  
  gc.kexp("imp_attrib")
  gc.kexp("imp_tokens")
  gc.kexp("imp_declarations")  
  gc.line("");  
  gc_code("BODY_PREFIX");
  gc.kexp("imp_code")
  gc_code("BODY_POSTFIX");
  gc.line("");
  gc.line("#if 0");
  gc.garbage();
  gc.line("#endif");

  # Include files
  gc.use("include_imp")
  for dep in data['dependencies'] :
    gc.line('#include "'+dep+'.h"');
  gc.line('#include "'+name+'.h"');
  
  attopGuard={}
  attopGuard['State']=False
  attopGuard['Timer']=False
  
  # Attributes 
  for att in arg['attributes'] :
    
    if att['visibility']==1 :
      na=att['name']
      if attopGuard.has_key(na) :
        error("Duplicated or reserved attribute name "+na+" in "+ name )
      else :
        attopGuard[na]=False  
      
    
    volatile="";
    if (att['volatile']) :
      volatile="volatile ";

          
    v=splitType(att["type"]);
      
    gc.declare("CODE_"+name)
    gc.use("imp_attrib")
    ifValue=""
    if att["value"]!="" :        
      ifValue=" = "+att["value"]
    
    if att["visibility"]==0 :
      #Private
      gc.declare("CODE_"+name)
      gc.use("imp_attrib")
      insertComment("",att["comment"]);
      if att["value"]=="":
        if v[1]=="" :
          gc.line(volatile+"static "+v[0]+" "+att["name"]+ifValue+";");
        else :
          gc.line(volatile+"static "+v[0]+" "+att["name"]+v[1]+ifvalue+";");
    else :
      #Public
      insertComment("",att["comment"]);
      if v[1]=="" :
        gc.line(volatile+v[0]+" "+name+"_"+att["name"]+ifValue+";");
        gc.declare('HEAD_'+name) 
        gc.use("head_attrib" )
        gc.line("extern "+volatile+" "+v[0]+" "+name+"_"+att["name"]+";");
      else :
        gc.line(volatile+v[0]+" "+name+"_"+att["name"]+v[1]+ifValue+";");
        gc.declare('HEAD_'+name) 
        gc.use("head_attrib" )
        gc.line("extern "+volatile+v[0]+" "+name+"_"+att["name"]+v[1]+";");

  # Operations
  
  # We need a constructor ?
  if arg['hasinit'] or data.has_key('context') :    
    gc.declare("HEAD_"+name)
    gc.use("head_code");
    gc.line("void "+name+"_Init();");
    
    gc.declare("CODE_"+name)
    gc.use("imp_code");
    gc.line("void "+name+"_Init()");
    gc.line("{");
    gc.line("TRACE_FUNCTION("+name+","+name+"_Init)");
    gc_code("Init_definitions");  
    gc.kexp("  constructor_code")
    gc_code("Init_code");  
    gc.line("}");
    gc.line("");
    attopGuard["Init"]=True
    if data.has_key('context') :    
      attopGuard["Run"]=True
      
  for ope in arg["operations"] :
    
    if att['visibility']==1 :    
      na=ope['name']
      if attopGuard.has_key(na) :
        if attopGuard(na) :
          error("Duplicated or reserved operation name "+na+" in "+ name )
        else :
          error("An operation has the same name of an attribute "+na+" in "+ name )        
      else :
        attopGuard[na]=True  
    
    
    op="static "+ope["type"]+" "+ope["name"];    
    if ope["visibility"]==1 :
      op=ope["type"]+" "+name+"_"+ope["name"];
    
    op+="( ";
    bp="";
    comment = ope["comment"]
   
    for prm in ope["parameters"] :
      v=splitType(prm["type"])
      op+=bp+v[0]+" "+prm["name"]+v[1]
      bp=" , "
    
    op=op+" )"
  
    if ope["visibility"]==0 :
      # Private
      gc.declare("CODE_"+name)
      gc.use("imp_declarations")
      gc.line(op+";");
    else :
      # Public
      gc.declare("HEAD_"+name)
      gc.use("head_code")
      gc.line(op+";");
    
    gc.declare("CODE_"+name)
    gc.use("imp_code");
    insertComment("",comment);      
    gc.line(op);
    gc.line("{");
    gc.line("TRACE_FUNCTION("+name+","+ope["name"]+")");
    gc_code(ope["name"]+"_code");
    gc.line("}");
    gc.line("");

  # Tokens
  for tok in arg['tokens'] :
    if C_TOKENS.has_key(tok['name']) :
      error("Duplicate token name "+tok['name']+" in project")
    else :  
      C_TOKENS[tok['name']]=tok;
    # Put in token list
    if tok["type"]==0 :
      # Counters
      gc.declare("TOKENS")
      gc.use("tokens_list")
      insertComment("",tok['comment']);
      gc.line("TOKEN_REFERENCE(Token_"+tok['name']+")")
      gc.declare("CODE_"+name)
      gc.use("imp_tokens")
      gc.line("TOKEN_DEFINITION(Token_"+tok['name']+")")
    else :
      # Signals
      gc.declare("CODE_"+name)
      gc.use("imp_tokens")
      gc.line("TOKEN_SIGNAL_DEFINITION(Token_"+tok["name"]+")")
      gc.declare("HEAD_"+name)
      gc.use("head_code")
      insertComment("",tok['comment']);
      gc.line("void "+name+"_"+tok["name"]+"( );");
      gc.declare("CODE_"+name)
      gc.use("imp_code");
      gc.line("void "+name+"_"+tok["name"]+"( )");
      gc.line("{");
      gc.line("TRACE_FUNCTION("+name+","+tok["name"]+")");
      gc.line("  TOKEN_RAISE(Token_"+tok["name"]+")")
      gc_code(tok["name"]+"_code");
      gc.line("}");
      gc.line("");
    

  # Optionally generate FSM code
  if data.has_key('context') :
    gc.declare("MAIN_CODE")
    gc.use("RUNCODE")
    gc.line(name+"_Run();");

    gc.declare("HEAD_"+name)
    gc.use("head_code");
    gc.line("void "+name+"_Run();");

    gc.declare("CODE_"+name)
    gc.use('imp_code')
    gc.line("void "+name+"_Run()");
    gc.line("{");
    gc.line("TRACE_FUNCTION("+name+","+name+"_Run)");  
    gc_code("Run_definitions");
    gc.kexp("  run_keycode");
    gc.line("}");
    gc.line("");
    generateAutoma(data)


# Main program
collectDependencies()

  
def Model() :
  # Model
  gc.declare("MAIN_CODE")
  gc.file("src/model.c")
  gc.kexp("include_imp")
  gc_code("USER_INCLUDES");
  gc.line("");  
  insertComment("","Model stub produced by SunRiZe");
  gc.kexp("imp_attrib")
  gc.kexp("imp_declarations")  
  gc.line("");  
  gc_code("BODY_PREFIX");
  gc.line("void model_init()" )  
  gc.line("{" )  
  gc.kexp("  INITCODE")  
  gc.line("}" )  
  gc.line("" )
  gc.line("void model_run()" )  
  gc.line("{" )  
  gc.kexp("  RUNCODE")  
  gc.line("}" )    
  gc.line("" )
  gc_code("BODY_POSTFIX");
  gc.line("");
  gc.line("#if 0");
  gc.garbage();
  gc.line("#endif");  
  # Tokens
  gc.declare('TOKENS') 
  gc.file("include/tokens.h")
  gc.line("#ifndef __TOKENS_H" )
  gc.line("#define __TOKENS_H" )
  gc.kexp("tokens_list" )
  gc.line("#endif /*__TOKENS_H*/" )
  
      
# Main Program
Model()
for data in model :
  if data['model']=='module' :
    generateModule(data)
DFS_create()
  


