#pragma pack(1)
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <boost/format.hpp>
#include <iomanip>

using namespace std;
using boost::format;

#define MAGIC_BLOCK 0xd9b4bef9

struct blkstart
{
	unsigned int magic;
	unsigned int blksize;
	char blkhead[80];
};

struct blkheader
{
	unsigned int ver;
	unsigned char prevHash[32];
	unsigned char merkRoot[32];
	unsigned int ts;
	unsigned int bits;
	unsigned int nonce;
};

void printHash(unsigned char h[32])
{
	for (int k = 0; k < 32; ++k)
	{
		cout<<hex<<setfill('0')<<setw(2)<<(int)h[k];
	}
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
		char blockStart[88];
		blkFile.read(blockStart, 88);
		blkstart* curBlock;
		curBlock = (blkstart*) blockStart;
		if (curBlock-> magic != MAGIC_BLOCK)
			break;
		blkheader* curHead;
		curHead = (blkheader*) curBlock->blkhead;
		cout<<"Block #: "<<blockNum++<<endl;
		cout<<"Block Size: "<<curBlock->blksize<<endl;
		cout<<"Block ver: "<<curHead->ver<<endl;
		cout<<"Prev hash: ";
		printHash(curHead->prevHash);
		cout<<endl;//curHead->prevHash<<endl;

		char time_p[80];
		time_t t = (time_t)curHead->ts;
		struct tm* ptm;
		
		ptm = gmtime(&t);

		strftime(time_p,80,"%F %R", ptm);

		cout<<"Timestamp: "<<time_p<<endl;
		cout<<endl;

		//Initial 8 blocks + size
		blockPos+=curBlock->blksize+8;
	}
}
