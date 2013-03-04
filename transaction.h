#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include "txin.h"
#include "txout.h"

class Transaction
{
	public:
	unsigned int trans_ver;
	unsigned long long txin_count;
	std::vector<Txin> txins;
	unsigned long long txout_count;
	std::vector<Txout> txouts;
	unsigned int lock_time;
};

#endif
