#include "Machine.h"



Machine::Machine() 
{

  DPRINTF("Machine::Machine()");  

}



Machine::~Machine()
{
  DPRINTF("Machine::~Machine()");
}


void Machine::setI(int what,int val)
{
  
}

void Machine::setF(int what,float val)
{
  
}


int Machine::getI(int what)
{
  
}


void Machine::init()
{
  DPRINTF("Machine::init()");
}



void Machine::reset()
{
  DPRINTF("Machine::reset()");
}


int Machine::tick()
{
  DPRINTF("Machine::tick()");
}


int Machine::checkI(int what,int val)
{
  DPRINTF("WARNING : Machine::checkI()");
  return val;
}

int Machine::checkITwoVal(int what,int val,int val2)
{
  DPRINTF("WARNING : Machine::checkITwoVal()");
  return val;
}


const char * Machine::getMachineParamCharStar(int machineParam,int paramValue)
{
  const char * str_null="NOLL";
  DPRINTF("Machine::getMachineParamCharStar");
  return str_null;
}

const char * Machine::getMachineTwoParamCharStar(int machineParam,int paramValue1, int paramValue2)
{
  const char * str_null="NULL";
  DPRINTF("Machine::getMachineTwoParamCharStar");
  return str_null;
}

