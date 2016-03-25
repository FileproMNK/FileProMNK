/*
 * Copyright(c) 2005-2010 Alex C. Snoeren <snoeren@cs.ucsd.edu>
 * 2005 Calvin Hubble
 * 2006 Kiran Tati <ktati@cs.ucsd.edu>
 *
 * This program is intended to format your disk file, and should be executed
 * BEFORE any attempt is made to mount your file system.  It will not, however
 * be called before every mount.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "muicfs.h"


int readsuperblock(int fd){
	superblock *sbptr = (superblock *)malloc(sizeof(superblock));

	dread(fd,0,sbptr);

	//sbptr = sbptr+499;
	printf("superblock = address %x\n",sbptr);
	printf("superblock info = %s\n",*sbptr);
//	printf("superblock fs_name = %s ; ibitmap_blocknum = %d ; dbitmap_blocknum = %d ; inode_blocknum = %d", sbptr -> fs_name,sbptr -> ibitmap_blocknum,sbptr -> dbitmap_blocknum,sbptr -> inode_blocknum );
	return 0;
}

int readibitmap(int fd){
	//dread(fd,)
	//printf("inode number : %d , file size pointed to inode : %d" inode -> big_blocknum, inode ->);
	return 0;
}
int readdbitmap(int fd){
	//dread(fd);
	return 0;
}
int readinode(int fd){
	//dread(fd,)
//printf("inode number : %d , file size pointed to inode : %d" inode -> big_blocknum, inode ->);
	return 0;
}


int main(int argc, char** argv) {
	int fd = open(DISKFILE, O_RDWR | O_CREAT);
	readsuperblock(fd);
	close(fd);
	return 0;
}
