#include "fs.h"
#include <cstring>

int INE5412_FS::fs_format()
{
	char *data = new char[Disk::DISK_BLOCK_SIZE];
	memset(data, 0, Disk::DISK_BLOCK_SIZE);
	for(int i = 0; i < disk->size(); i++){
		disk->write(i, data);
	}
	delete[] data;
	union fs_block block;

	block.super.magic = FS_MAGIC;
	block.super.nblocks = disk->size();
	block.super.ninodeblocks = disk->size() / 10;
	block.super.ninodes = block.super.ninodeblocks * INODES_PER_BLOCK;
	disk->write(0, block.data);
	return 1;
}

void INE5412_FS::fs_debug()
{
	union fs_block block;

	disk->read(0, block.data);

	cout << "superblock:\n";
	cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
 	cout << "    " << block.super.nblocks << " blocks\n";
	cout << "    " << block.super.ninodeblocks << " inode blocks\n";
	cout << "    " << block.super.ninodes << " inodes\n";
}

int INE5412_FS::fs_mount()
{
	return 0;
}

int INE5412_FS::fs_create()
{
	return 0;
}

int INE5412_FS::fs_delete(int inumber)
{
	return 0;
}

int INE5412_FS::fs_getsize(int inumber)
{
	return -1;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	return 0;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	return 0;
}
