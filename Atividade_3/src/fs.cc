#include "fs.h"
#include <cstring>
#include <cmath>


int INE5412_FS::fs_format()
{
	union fs_block block;
	char data[Disk::DISK_BLOCK_SIZE] = {0};

	for(int i = 0; i < disk->size(); i++)
		disk->write(i, data);

	block.super.magic = FS_MAGIC;
	block.super.nblocks = disk->size();
	block.super.ninodeblocks = ceil(disk->size() / 10);
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
 	cout << "    " << block.super.nblocks << " blocks on disk\n";
	cout << "    " << block.super.ninodeblocks << " blocks for inodes\n";
	cout << "    " << block.super.ninodes << " inodes total\n";

	for (int i = 1; i < block.super.ninodes; i++) {
		union fs_block aux;
		int inode_block = fs_get_inode_block(i);
		int inode_line = fs_get_inode_line(i);

		disk->read(inode_block, aux.data);

		if(!aux.inode[inode_line].isvalid)
			continue;

		cout << "inode " << i-1 << ":\n";
		cout << "    size: " << aux.inode[inode_line].size << " bytes\n";
		cout << "    direct blocks:";

		for(int k = 0; k < POINTERS_PER_INODE; k++)
			if(aux.inode[inode_line].direct[k])
				cout << " " << aux.inode[inode_line].direct[k];

		cout << "\n";

		if(aux.inode[inode_line].indirect) {	
			cout << "    indirect block: " << aux.inode[inode_line].indirect << "\n";
			disk->read(aux.inode[inode_line].indirect, aux.data);
			cout << "    indirect data blocks:";

			for(int k = 0; k < POINTERS_PER_BLOCK; k++)
				if(aux.pointers[k])
					cout << " " << aux.pointers[k];
			
			cout << "\n";
		}
	}
}

int INE5412_FS::fs_mount()
{
	union fs_block block;
	disk->read(0, block.data);

	if(block.super.magic != FS_MAGIC)
		return 0;

	for (int i = 0; i < disk->size(); i++)
		free_block_bitmap.push_back(0);

	for (int i = 1; i < block.super.ninodeblocks + 1; i++) {
		union fs_block aux;
		disk->read(i, aux.data);
		
		// Para o caso de o inode não estiver sendo usado
		if (!aux.inode->isvalid)
			continue;

		for (int j = 0; j < POINTERS_PER_INODE; j++) {
			if (fs_check_numblock(aux.inode->direct[j])) {
				free_block_bitmap[aux.inode->direct[j]] = 1;
			} else {
				return 0;
			}
		}

		// Para o caso de o inode não ter bloco indireto
		if (!aux.inode->indirect)
			continue;

		disk->read(aux.inode->indirect, aux.data);

		for (int j = 0; j < POINTERS_PER_BLOCK; j++) {
			if (fs_check_numblock(aux.pointers[j])) {
				free_block_bitmap[aux.pointers[j]] = 1;
			} else {
				return 0;
			}
		}

	}


	return 1;
}

int INE5412_FS::fs_create()
{
	union fs_block block;
	disk->read(0, block.data);

	if(block.super.magic != FS_MAGIC)
		return 0;

	for (int i = 1; i < block.super.ninodeblocks + 1; i++) {
		union fs_block aux;
		disk->read(i, aux.data);
		
		for (int k = 0; k < block.super.ninodes; k++) {

			if (aux.inode[k].isvalid)
				continue;
			
			aux.inode[k].isvalid = 1;
			aux.inode[k].size = 0;
			aux.inode[k].indirect = 0;

			for (int j = 0; j < POINTERS_PER_INODE; j++)
				aux.inode[k].direct[j] = 0;
			
			disk->write(i, aux.data);

			return (i - 1) * INODES_PER_BLOCK + k + 1;
		}

	}

	return 0;
}

int INE5412_FS::fs_delete(int inumber)
{
	if (!fs_check_inumber(inumber))
		return 0;

	union fs_block block, super;
	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	disk->read(0, super.data);
	disk->read(inode_block, block.data);

	block.inode[inode_line].isvalid = 0;
	
	for(int i = 0; i < POINTERS_PER_INODE; i++) {
		if (fs_check_numblock(block.inode[inode_line].direct[i])) {
			free_block_bitmap[block.inode[inode_line].direct[i]] = 0;
		} else {
			return 0;
		}
	}

	if(block.inode[inode_line].indirect) {
		for(int i = 0; i < POINTERS_PER_BLOCK; i++) {
			if (fs_check_numblock(block.pointers[i])) {
				free_block_bitmap[block.pointers[i]] = 0;
			} else {
				return 0;
			}
		}
	}

	disk->write(inode_block, block.data);
	return 1;
}

int INE5412_FS::fs_getsize(int inumber)
{
	if (!fs_check_inumber(inumber))
		return -1;

	union fs_block block;
	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	disk->read(inode_block, block.data);

	return block.inode[inode_line].size;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	if(!fs_check_inumber(inumber))
		return 0;

	union fs_block block;

	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	disk->read(inode_block, block.data);

	int size = block.inode[inode_line].size;

	if(offset >= size)
		return 0;


	int block_offset = offset / Disk::DISK_BLOCK_SIZE;

	int total_bytes = 0, cont = 0, destination_offset = 0;
	int aux_offset = offset; int aux_length = length + offset;
	int bytes_to_copy = Disk::DISK_BLOCK_SIZE;

	for(int i = block_offset; i < POINTERS_PER_INODE; ++i){
		int current_block = block.inode[inode_line].direct[i];
		if(current_block <= 0) break;
		union fs_block aux;
		disk->read(current_block, aux.data);
		aux_offset += Disk::DISK_BLOCK_SIZE;
		if(aux_offset > aux_length){
			cont = aux_offset - aux_length;
			total_bytes = aux_offset - cont;
			bytes_to_copy = total_bytes % Disk::DISK_BLOCK_SIZE;
		}
		for(int j = 0; j < bytes_to_copy; ++j){
			data[destination_offset++] = aux.data[j];
		}
		if(aux_offset > aux_length) break;
	}

	bytes_to_copy = Disk::DISK_BLOCK_SIZE;
	block_offset = (aux_offset / Disk::DISK_BLOCK_SIZE) - POINTERS_PER_INODE;
	if(block.inode[inode_line].indirect){
		union fs_block indirect_block;
		disk->read(block.inode[inode_line].indirect, indirect_block.data);
		for(int i = block_offset; i < POINTERS_PER_BLOCK; ++i){
			int current_block = indirect_block.pointers[i];
			if(current_block <= 0) break;
			union fs_block aux;
			disk->read(current_block, aux.data);
			aux_offset += Disk::DISK_BLOCK_SIZE;
			if(aux_offset > aux_length){
				cont = aux_offset - aux_length;
				total_bytes = aux_offset - cont;
				bytes_to_copy = total_bytes % Disk::DISK_BLOCK_SIZE;
			}

			for(int j = 0; j < bytes_to_copy; ++j){
				data[destination_offset++] = aux.data[j];
			}
			if(aux_offset > aux_length) break;
			}
	}
	
	if(length + offset > size)
		return size - offset;

	return length;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	return 0;
}

int INE5412_FS::fs_check_inumber(int inumber) {
	union fs_block block;
	disk->read(0, block.data);
	int inode_block = fs_get_inode_block(inumber);

	return 0 < inode_block && inode_block < block.super.ninodeblocks + 1;
}

int INE5412_FS::fs_check_numblock(int blocknum) {
	union fs_block block;
	disk->read(0, block.data);

	return block.super.ninodeblocks < blocknum && blocknum < block.super.nblocks;
}

int INE5412_FS::fs_get_inode_block(int inumber) {
	inumber--;
	return (inumber / INODES_PER_BLOCK) + 1;
}

int INE5412_FS::fs_get_inode_line(int inumber) {
	inumber--;
	return inumber % INODES_PER_BLOCK;
}