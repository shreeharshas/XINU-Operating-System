#ifndef FS_H
#define FS_H
 
#define O_CREAT 11
#define O_RDONLY 0 
#define O_WRONLY 1 
#define O_RDWR 2

#define FILENAMELEN 32
#define INODEBLOCKS 12
#define INODEDIRECTBLOCKS (INODEBLOCKS - 2)
#define DIRECTORY_SIZE 16

#define MDEV_BLOCK_SIZE 512
#define MDEV_NUM_BLOCKS 512
#define DEFAULT_NUM_INODES (MDEV_NUM_BLOCKS / 4)

#define INODE_TYPE_FILE 1
#define INODE_TYPE_DIR 2

#define F_INRW -9999
#define F_NTRW 9999

#define DIRECTORY_SIZE 16
#define FILETABLEN 100

#define TYPE_FILE       0
#define TYPE_DIRECTORY  1

#define FSTATE_CLOSED 0
#define FSTATE_OPEN 1

#define FS 1

#define INODE2BLOCKNO(inode_num) ((inode_num/8) + 2)
#define INODE2OFFSET(inode_num)  ((inode_num%8) * sizeof(struct inode))

struct inode {
  int id;
  short int type;
  short int nlink;
  int device;
  int size;
  int state;
  int blocks[INODEBLOCKS];
};

struct filetable {
  int state;
  int fileptr;
  int mode;
  int curr_inode_num;
  struct dirent *de;
  struct inode in;
};

struct dirent {
  int inode_num;
  char name[FILENAMELEN];
};

struct directory {
  int numentries;
  struct dirent entry[DIRECTORY_SIZE];
};

struct fsystem {
  int nblocks;
  int blocksz;
  int ninodes;
  int inodes_used;
  int freemaskbytes;
  char *freemask;
  struct directory root_dir;
};

extern struct fsystem fsd;
extern struct filetable GlobalFileTab[INODEBLOCKS];
extern struct inode current_inode[INODEBLOCKS];


/* file and directory functions */
int fs_open(char *filename, int flags);
int fs_close(int fd);
int fs_create(char *filename, int mode);
int fs_seek(int fd, int offset);
int fs_read(int fd, void *buf, int nbytes);
int fs_write(int fd, void *buf, int nbytes);

/* filesystem functions */
int fs_mkfs(int dev, int num_inodes);
int fs_mount(int dev);

/* filesystem internal functions */
int fs_get_inode_by_num(int dev, int inode_number, struct inode *in);
int fs_put_inode_by_num(int dev, int inode_number, struct inode *in);

int fs_setmaskbit(int b);
int fs_clearmaskbit(int b);
int fs_getmaskbit(int b);

/*
  Block Store functions
  bread, bwrite,
  bput, bget write entire blocks (macro with offset=0, len=blocksize)
 */
int bs_mkdev(int dev, int blocksize, int numblocks);
int bs_bread(int bsdev, int block, int offset, void *buf, int len);
int bs_bwrite(int bsdev, int block, int offset, void * buf, int len);

/* debugging functions */
void fs_printfreemask(void);
void fs_print_fsd(void);
#endif /* FS_H */
