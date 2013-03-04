#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <list>
#include <cstring>
#include "blkstart.h"
#include "blkheader.h"
#include "transaction.h"

using namespace std;

#define MAGIC_BLOCK 0xd9b4bef9

static void get_varint(char* b, int &len, long long* val)
{
	if (*b < 0xfd)
	{
		*val = (long long)*b;
		len = 1;
	}
	else if (*b == 0xfd)
	{
		memcpy(val, b+1, 2);
		len = 3;
	}
	else if (*b == 0xfe)
	{
		memcpy(val, b+1, 4);
		len = 5;
	}
	else if (*b == 0xff)
	{
		memcpy(val, b+1, 8);
		len = 9;
	}
}

void printHash(unsigned char h[32])
{
	for (int k = 0; k < 32; ++k)
	{
		cout<<hex<<setfill('0')<<setw(2)<<(int)h[k]<<dec;
	}
}

void getFormatTime(char* time_p, unsigned int ts)
{
	time_t t = (time_t)ts;
	struct tm* ptm;
	ptm = gmtime(&t);
	strftime(time_p,80,"%F %R", ptm);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout<<"Must specify a block file to read."<<endl;
		exit(0);
	}

	ifstream blkFile;

	blkFile.open(argv[1], ios::in | ios::binary);

	int blockPos = 0;
	int blockNum = 0;

	while(blkFile.peek() != EOF)
	{
		blkFile.seekg(blockPos);
		char* blockStart = new char[88];
		blkFile.read(blockStart, 88);
		blkstart* curBlock = (blkstart*) blockStart;

		//If the block doesn't start with the magic number the file is done/bogus
		if (curBlock-> magic != MAGIC_BLOCK)
			break;

		blkheader* curHead = (blkheader*) curBlock->blkhead;
		cout<<"Block #: "<<blockNum++<<endl;
		cout<<"Block Size: "<<curBlock->blksize<<endl;
		cout<<"Block ver: "<<curHead->ver<<endl;
		cout<<"Prev hash: ";
		printHash(curHead->prevHash);
		cout<<endl;

		char time_p[80];
		getFormatTime(time_p, curHead->ts);
		cout<<"Timestamp: "<<time_p<<endl;

		char* transSec = new char[curBlock->blksize];
		
		blkFile.read(transSec, curBlock->blksize);
		long long* va = new long long;
		int len_t = 0;
		get_varint(transSec,len_t, va);
		cout<<"# of Trans: "<<*va<<endl;
		cout<<"# of Trans (var length): "<<len_t<<endl;

		int transPos = len_t;

		for (int k = 0; k < (*va); ++k)
		{
			Transaction f;
			memcpy(&f.trans_ver, transSec+transPos, 4);
			long long* txin_count;
			int txin_count_b;
			cout<<"\tTrans ver: "<<f.trans_ver<<endl;
		}

		cout<<endl<<endl;

		//Initial 8 blocks + size
		blockPos+=curBlock->blksize+8;
	}

	cout<<"File contains "<<blockNum<<" blocks."<<endl;
}
