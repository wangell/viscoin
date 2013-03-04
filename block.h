#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "blkheader.h"
#include "transaction.h"

class Block
{
	unsigned int magic;
	unsigned int size;
	blkheader header;
	unsigned long long trans_count;
	vector<Transaction*> trans;
};

#endif
