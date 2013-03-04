#ifndef TXIN_H
#define TXIN_H

#include "outpoint.h"

class Txin
{
	outpoint previous_output;
	unsigned long long script_length;
	unsigned char* script;
	unsigned int seq;
};

#endif
