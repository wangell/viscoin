#ifndef OUTPOINT_H
#define OUTPOINT_H

struct outpoint
{
	char hash[32];
	unsigned int index;
};

#endif
