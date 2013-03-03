#ifndef BLKSTART_H
#define BLKSTART_H

struct blkstart
{
	unsigned int magic;
	unsigned int blksize;
	unsigned char blkhead[80];
};

#endif
