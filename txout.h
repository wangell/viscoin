#ifndef TXOUT_H
#define TXOUT_H

class Txout
{
	long long val;
	unsigned long long script_length;
	unsigned char* script;
};

#endif
