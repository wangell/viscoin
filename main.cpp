#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <list>
#include "blkstart.h"
#include "blkheader.h"

using namespace std;

#define MAGIC_BLOCK 0xd9b4bef9

void printHash(unsigned char h[32])
{
	for (int k = 0; k < 32; ++k)
	{
		cout<<hex<<setfill('0')<<setw(2)<<(int)h[k]<<dec;
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
		time_t t = (time_t)curHead->ts;
		struct tm* ptm;
		
		ptm = gmtime(&t);

		strftime(time_p,80,"%F %R", ptm);

		cout<<"Timestamp: "<<time_p<<endl;
		cout<<endl;

		//Initial 8 blocks + size
		blockPos+=curBlock->blksize+8;
	}

	cout<<"File contains "<<blockNum<<" blocks."<<endl;
}
