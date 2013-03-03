#ifndef BLKHEADER_H
#define BLKHEADER_H

struct blkheader
{
	unsigned int ver;
	unsigned char prevHash[32];
	unsigned char merkRoot[32];
	unsigned int ts;
	unsigned int bits;
	unsigned int nonce;
};

#endif
