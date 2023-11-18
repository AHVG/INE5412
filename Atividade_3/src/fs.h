#ifndef FS_H
#define FS_H

#include "disk.h"
#include <vector>


class INE5412_FS
{
public:
    static const unsigned int FS_MAGIC = 0xf0f03410;
    static const unsigned short int INODES_PER_BLOCK = 128;
    static const unsigned short int POINTERS_PER_INODE = 5;
    static const unsigned short int POINTERS_PER_BLOCK = 1024;
    static const unsigned short int POINTERS_TO_BLOCKS_PER_INODE = POINTERS_PER_INODE + POINTERS_PER_BLOCK;
    static const unsigned short int BYTES_PER_INODE = POINTERS_TO_BLOCKS_PER_INODE * Disk::DISK_BLOCK_SIZE;

    class fs_superblock {
        public:
            unsigned int magic;
            int nblocks;
            int ninodeblocks;
            int ninodes;
    }; 

    class fs_inode {
        public:
            int isvalid;
            int size;
            int direct[POINTERS_PER_INODE];
            int indirect;
    };

    union fs_block {
        public:
            fs_superblock super;
            fs_inode inode[INODES_PER_BLOCK];
            int pointers[POINTERS_PER_BLOCK];
            char data[Disk::DISK_BLOCK_SIZE];
    };

public:

    INE5412_FS(Disk *d) {
        disk = d;
    } 

    void fs_debug();
    int  fs_format();
    int  fs_mount();

    int  fs_create();
    int  fs_delete(int inumber);
    int  fs_getsize(int inumber);

    int  fs_read(int inumber, char *data, int length, int offset);
    int  fs_write(int inumber, const char *data, int length, int offset);

private:

    Disk *disk;
    vector<int> free_block_bitmap;

private:

    int fs_check_inumber(int inumber);
    int fs_check_numblock(int blocknum);

    int fs_get_inode_block(int inumber);
    int fs_get_inode_line(int inumber);

    union fs_block fs_get_content_block(int n_pointer_to_block);
    void fs_set_content_block(int n_pointer_to_block, char *data);

};

#endif