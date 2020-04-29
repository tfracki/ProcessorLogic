#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProcessorLogic.h"


/* This class delivers interface for operation on main linked-list */
class FunctionLogicList {
public:
	//	This function returns singleton object of FunctionLogicList
	static FunctionLogicList & getInstance();

private:

	/* default constructor */
	FunctionLogicList() {};

	/* copy constructor */
	FunctionLogicList(const FunctionLogicList&);

	/* assignment operator */
	FunctionLogicList& operator=(FunctionLogicList&);

	/* This structure contain pointer to LogicFuntion and pointer to next element on the list */
	struct FunctionLogicElm {
		FunctionLogic *m_function;
		struct FunctionLogicElm *m_next;
	} *head;

};


/**************************************************************************************/

FunctionLogicList & FunctionLogicList::getInstance()
{
	static FunctionLogicList s_list;
	return s_list;
}

/**************************************************************************************/


FunctionLogic::FunctionLogic(const char *name, int numinputs, const char **table) :
	m_numinputs(numinputs), m_table(table)
{
  // todo
}

FunctionLogic::~FunctionLogic()
{
  // todo
}

FunctionLogic *FunctionLogic::findFunction(const char *name)
{
  // todo
}

char FunctionLogic::calculate(const char *inputs) const
{
	// todo
}

int FunctionLogic::getNuminputs() const
{ 
	return m_numinputs; 
};

char* FunctionLogic::getName() const 
{ 
	return m_name; 
};


/**************************************************************************************/

ProcessorLogic::ProcessorLogic( FunctionLogic *function )
	: m_FunctionLogic ( function )
{
	m_numinputs = function->getNuminputs();
	m_inputsources = new char * [m_numinputs];
	m_inputfunctions = new ProcessorLogic * [m_numinputs];

	for (int i=0; i<m_numinputs; i++)
	{
		m_inputsources[i] = 0;
		m_inputfunctions[i] = 0;
	}
}


ProcessorLogic::~ProcessorLogic()
{
	delete [] m_inputsources;
	delete [] m_inputfunctions;
}

void ProcessorLogic::setInput(int input, ProcessorLogic *lf)
{
	if (input >= m_numinputs)
	{
		fprintf(stderr, "Warning: Trying to access to unavailable memory, max input value: %d", m_numinputs);
		return;
	}

	m_inputfunctions[input] = lf;
}

void ProcessorLogic::setInput(int input, char * source)
{
	if (input >= m_numinputs)
	{
		fprintf(stderr, "Warning: Trying to access to unavailable memory, max input value: %d", m_numinputs);
		return;
	}

	m_inputsources[input] = source;
}

char ProcessorLogic::process()
{
	char *inputs = new char [m_numinputs];

	for (int i=0; i<m_numinputs; i++)
	{
		inputs[i] =  m_inputsources[i] ? *m_inputsources[i] :
					m_inputfunctions[i] ? m_inputfunctions[i]->process() : 0;
	}

	char output=m_FunctionLogic->calculate(inputs);
	delete [] inputs;
	return output;
}