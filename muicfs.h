/*
 * Copyright(c) 2005-2007  Alex C. Snoeren <snoeren@cs.ucsd.edu>
 *
 */

#define BLOCKSIZE 512

/* This is the name of the file you will use for your disk.
   Currently, it looks in the current directory.  You may want
   to replace this with an absolute path. */
#define DISKFILE "disk.txt"

/* You must use the following two calls to read from your "disk" */

/* Read a block from disk */
int dread(int fd, int blocknum, char *buf);

/* Write a block to disk */
int dwrite(int fd, int blocknum, char *buf);

/* start coding */
typedef struct inode{
	char filetype;
	int datablknum;
	int size;
} inode;

typedef struct ibitmap{
	int freeinodenum[16];
}ibitmap;

typedef struct dbitmap{
	int freedatanum[16];
}dbitmap;


typedef struct file{
	char filename[28];
	int inodenum;
}file;

typedef struct directory{
	int myinode;
	int mymotherinode;
	file children[15];
}
