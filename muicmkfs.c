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


int
myformat(const char *filename, int size)
{
	/*write file system with three block each byte with one
	   * dwrite(int fd, int blocknum, char *buf)*/
  /*number of files we can support : 16
   * max supported data = 512 byte
   * total space : 16 * 512 byte = */
  /**/

	/* start superblock */
	int fd = open(DISKFILE, O_RDWR | O_CREAT);
	superblock *sptr = (superblock *)malloc(sizeof(superblock));
	strcpy(sptr->fs_name,"Test File System");
	sptr -> ibitmap_blocknum = 1;
	sptr -> dbitmap_blocknum = 2;
	sptr -> inode_blocknum = 3;

	dwrite(fd,0,(char *)sptr);
	/* finish superblock */

	/*start ibitmap*/
	i_bitmap ibmptr[16];
	for(int i = 0;i<16;i++){
		ibmptr[i].little_blocknum = i; // #of inode#
		ibmptr[i].alloc = 0;
	}
	dwrite(fd,1,(char *)ibmptr);
	/*finish ibitmap*/

	/*start dbitmap*/
	d_bitmap dbmptr[16];
	for(int i = 0;i<16;i++){
		dbmptr[i].little_blocknum = i; // #of inode#
		dbmptr[i].alloc = 0;
	}
	dwrite(fd,2,(char *)dbmptr);
	/*finish dbitmap*/

	/*start inode */
	inode inptr[16];
	for(int i = 0;i<16;i++){
		inptr[i].big_blocknum = 4+i; // #of inode#
		inptr[i].size = 512;
	}
	dwrite(fd,3,(char *)inptr);
	/*finish inode*/

	/*start datablock*/
	for(int i=0;i<16;i++){
		printf("Datablock number = %d",i);
		char data[512];
		for(int j =0;i<512;i++){
			data[j] = i%2;
		}
		dwrite(fd,4+i,data);
	}
	/*finish datablock*/
	close(fd);
  return 0;
}

void usage(char *prgname) {
    printf("usage: %s diskSizeInBlockSize\n",prgname);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Invalid number of arguments \n");
        usage(argv[0]);
        return 1;
    }

    unsigned long size = atoi(argv[1]);
    printf("Formatting the %s with size %lu \n",DISKFILE, size);
    myformat(DISKFILE, size);

   return 0;
}
