#ifndef PROCESSORLOGIC_H
#define PROCESSORLOGIC_H


/* This class delivers interface for logic function operation */
class FunctionLogic {
public:
	FunctionLogic(const char *name, int numinputs, const char **table);

	virtual ~FunctionLogic();


	//	This function returns pointer to FunctionLogic object identified by a passed "name" string.
	static FunctionLogic *findFunction(const char *name);

	// This function compares "inputs" string with truth table "m_table" and returns result.
	virtual char calculate(const char *inputs) const;


	/* Accessor functions */

		/* @return: numbers of inputs for logic function  */
	int getNuminputs() const;
		
		/* @return: string identifier of the current instance  */
	char *getName() const;

private:
	/* copy constructor - blocked */
	FunctionLogic(const FunctionLogic&);

	/* assignment operator - blocked */
	FunctionLogic& operator=(FunctionLogic&);

protected:
	// string identifier for class instance
	int m_numinputs;

	// number of inputs for logic function
	char *m_name;

	// truth table which is string of "numinputs" inputs + resulting output, inputs / output are char: 't', 'f', 'x'
	const char **m_table;
};

/* This class delivers interface for processing the logic */
class ProcessorLogic {
public:
	ProcessorLogic( FunctionLogic *function );
	
	/* destructor	*/
	~ProcessorLogic();

	//	This functions sets input parameters.
	void setInput(int input, ProcessorLogic *lf);
	void setInput(int input, char * source);

	//	This functions returns result of the calculation using input sources.
	char process();

private:
	/* copy constructor - blocked */
	ProcessorLogic(const ProcessorLogic&);

	/* assignment operator - blocked */
	ProcessorLogic& operator=(ProcessorLogic&);

	int m_numinputs;

	// index of the input parameter which will be changed
	char **m_inputsources;
	ProcessorLogic **m_inputfunctions;
	FunctionLogic *m_FunctionLogic;

};

#endif // PROCESSORLOGIC_H