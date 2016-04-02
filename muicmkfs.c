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
	superblock *sptr = (superblock *)malloc(sizeof(BLOCKSIZE));
	strcpy(sptr->filesystemname,"Test File System");
	sptr -> ibitmapblknum = 1;
	sptr -> dbitmapblknum = 2;
	sptr -> inodeblknum = 3;
	sptr -> rootinodeblknum = 1;
	dwrite(fd,0,(char *)sptr);
	free(sptr);
	/* finish superblock */

	/*start ibitmap*/
	char *ibitmap = (char *)malloc(sizeof(char)*BLOCKSIZE);
	for(int i = 0;i<BLOCKSIZE;i++){
		ibitmap[i]=0;
	}
	dwrite(fd,1,ibitmap);
	free(ibitmap);
	/*finish ibitmap*/

	/*start dbitmap*/
	char *dbitmap = (char *)malloc(sizeof(char)*BLOCKSIZE);
	for(int i = 0;i<BLOCKSIZE;i++){
		dbitmap[i]=0;
	}
	dwrite(fd,2,dbitmap);
	free(dbitmap);
	/*finish dbitmap*/

	/*start inode */
	inode *inodeptr = (inode *)malloc(sizeof(inode)*16);
	for(int i = 0;i<16;i++){
		strcpy(inodeptr[i].filet,"file");
		inodeptr[i].datablknum = i+4;
		inodeptr[i].size = 0;
	}
	dwrite(fd,3,(char *)inodeptr);
	free(inodeptr);
	/*finish inode*/

	/*start datablock (root)*/
	/*no need to initialize*/
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
