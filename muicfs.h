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

struct superblock{
	char fs_name[28];
	int* inode_pointer;
	int* ibitmap_pointer;
	int* dbitmap_pointer;
	int* datablock;
};

struct inode{
	int size;
	int* p
};

struct d_bitmap{
	int* p;
	char alloc;

};

struct i_bitmap{
	int* p;
	char alloc;

};

struct file{
	char file_name[28];
	int* inode_pointer;
	int filesize;
};

struct dir{
	char dir_name[28];
	int* inode_pointer;
	int dir_size;

};
