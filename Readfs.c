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
	printf("\nthis is superblock test\n");
	printf("superblock = address %x\n",sbptr);
	printf("superblock fs_name = %s ;\n ibitmap_blocknum = %d ; dbitmap_blocknum = %d ; inode_blocknum = %d \n", sbptr -> fs_name,sbptr -> ibitmap_blocknum,sbptr -> dbitmap_blocknum,sbptr -> inode_blocknum );
	printf("this is the end of superblock test\n");
	return 0;
}

int readibitmap(int fd){
	i_bitmap ibmptr[16];
	dread(fd,1,ibmptr);
	printf("\nthis is ibitmap test\n");
	for(int i = 0;i<16;i++){
		printf("ibitmap block %d;contain pointer to inode block %d and alloc = %d\n",i,ibmptr[i].little_blocknum,ibmptr[i].alloc);
	}
	printf("this is the end of ibitmap test\n");
	return 0;
}
int readdbitmap(int fd){
	d_bitmap dbmptr[16];
	dread(fd,2,dbmptr);
	printf("\nthis is dbitmap test\n");
	for(int i = 0;i<16;i++){
		printf("dbitmap block %d;contain pointer to data block %d and alloc = %d\n",i,dbmptr[i].little_blocknum,dbmptr[i].alloc);
	}
	printf("this is the end of dbitmap test\n");
	return 0;
}
int readinode(int fd){
	inode inptr[16];
	dread(fd,3,inptr);
	printf("\nthis is inode test\n");
	for(int i = 0;i<16;i++){
		printf("inode block %d;contain pointer to data block %d and size = %d\n",i,inptr[i].big_blocknum,inptr[i].size);
	}
	printf("this is the end of inode test\n");
	return 0;
}

int readdatablock(int fd,int blocknum){
	char data[512];
	dread(fd,blocknum,data);
	for(int i = 0;i<512;i++){
		printf("data = %s",data[i]);
	}
	return 0;
}

int main(int argc, char** argv) {
	int fd = open(DISKFILE, O_RDWR | O_CREAT);
	printf("Starting read");
	readsuperblock(fd);
	readibitmap(fd);
	readdbitmap(fd);
	//readinode(fd);
	//readdatablock(fd,int blocknum);
	close(fd);
	return 0;
}
