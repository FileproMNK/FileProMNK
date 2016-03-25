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
	int fd = open(DISKFILE, O_RDWR | O_CREAT);

	char superb[sizeof(superblock)];
	char inode1[sizeof(inode)*16];
	char db[sizeof(d_bitmap)];
	char ib[sizeof(i_bitmap)];
	char datab[BLOCKSIZE * 16];

	char buf_for_seperb[BLOCKSIZE];
	char buf_for_inode1[BLOCKSIZE];
	char buf_for_db[BLOCKSIZE];
	char buf_for_ib[BLOCKSIZE];
	char buf_for_datab[BLOCKSIZE];

	int* superb_pointer = &(buf_for_seperb);
	int* inode1_pointer = &(buf_for_inode1);
	int* db_pointer = &(buf_for_db);
	int* ib_pointer = &(buf_for_ib);
	int* datab_pointer = &(buf_for_datab);

	superblock->inode_pointer = inode1_pointer;
	superblock->ibitmap_pointer = db_pointer;
	superblock->dbitmap_pointer = ib_pointer;
	superblock->datablock_pointer = datab_pointer;

	inode->p = inode1_pointer;
	d_bitmap->p = db_pointer;
	i_bitmap->p = ib_pointer;


/*put pointer into struct first and then put all to block*/

	strcpy(buf_for_seperb,superblock);
	strcpy(buf_for_inode1,inode);
	strcpy(buf_for_db,d_bitmap);
	strcpy(buf_for_ib,i_bitmap);
//	strcpy(buf_for_datab,someinfo);



	dwrite(fd, 0, buf_for_seperb); /*super block*/

	dwrite(fd, 1, buf_for_inode1); /* inode bitmap block */



	dwrite(fd, 2, buf1); /* data bitmap block */


	for (int i = 3; i <= 19; i++){
		dwrite(fd, i, buf1); /* data inode : size of file , pointer inode */
	}

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
