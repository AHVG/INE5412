#include "fs.h"
#include <cstring>
#include <cmath>


INE5412_FS::INE5412_FS(Disk *d) {
	disk = d;
	mounted = 0;
}

// anotacoes
// precisamos montar o disco toda execucao nova?
// o create acho q n da pra fazer com load_inode
// o delete ta com problema, tem q revisar
// tem q fazer a ideia do load e save no write

int INE5412_FS::fs_format()
{
	if(mounted) return 0;

	union fs_block block;
	char data[Disk::DISK_BLOCK_SIZE] = {0};

	for(int i = 0; i < disk->size(); i++)
		disk->write(i, data);

	free_block_bitmap.clear();

	for (int i = 0; i < disk->size(); i++)
		free_block_bitmap.push_back(0);

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

		fs_inode inode;

		if(!fs_inode_load(i, &inode) || !inode.isvalid)
			continue;

		cout << "inode " << i << ":\n";
		cout << "    size: " << inode.size << " bytes\n";
		cout << "    direct blocks:";

		for(int k = 0; k < POINTERS_PER_INODE; k++)
			if(inode.direct[k])
				cout << " " << inode.direct[k];

		cout << "\n";

		if(inode.indirect) {	
			cout << "    indirect block: " << inode.indirect << "\n";
			disk->read(inode.indirect, aux.data);
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
	if(mounted) return 0;
	mounted = 1;

	union fs_block block;
	disk->read(0, block.data);

	if(block.super.magic != FS_MAGIC)
		return 0;

	free_block_bitmap.clear();

	for (int i = 0; i < disk->size(); i++)
		free_block_bitmap.push_back(0);

	for (int i = 1; i < block.super.ninodes; i++) {
		union fs_block aux;
		fs_inode inode;
		if(!fs_inode_load(i, &inode) || !inode.isvalid)
			continue;

		for (int j = 0; j < POINTERS_PER_INODE; j++) {
			if (fs_check_numblock(inode.direct[j])) {
				free_block_bitmap[inode.direct[j]] = 1;
			}
		}

		// Para o caso de o inode não ter bloco indireto
		if (!inode.indirect)
			continue;

		free_block_bitmap[inode.indirect] = 1;
		disk->read(inode.indirect, aux.data);

		for (int j = 0; j < POINTERS_PER_BLOCK; j++) {
			if (fs_check_numblock(aux.pointers[j])) {
				free_block_bitmap[aux.pointers[j]] = 1;
			}
		}

	}

	cout << endl;

	return 1;
}

int INE5412_FS::fs_create()
{
	if(!mounted) return 0;
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
	fs_inode inode;

	if (!fs_inode_load(inumber, &inode) || !mounted)
		return 0;

	union fs_block block, super;

	disk->read(0, super.data);

	inode.isvalid = 0;
	
	for(int i = 0; i < POINTERS_PER_INODE; i++) {
		if (fs_check_numblock(inode.direct[i])) {
			free_block_bitmap[inode.direct[i]] = 0;
		} else {
			return 0;
		}
	}

	if(inode.indirect) {
		for(int i = 0; i < POINTERS_PER_BLOCK; i++) {
			if (fs_check_numblock(block.pointers[i])) {
				free_block_bitmap[block.pointers[i]] = 0;
			} else {
				return 0;
			}
		}

		free_block_bitmap[inode.indirect] = 0;
	}

	if(!fs_inode_save(inumber, &inode)) return 0;
	return 1;
}

int INE5412_FS::fs_getsize(int inumber)
{
	fs_inode inode;
	if(!fs_inode_load(inumber, &inode) || !mounted) return -1;
	return inode.size;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	fs_inode inode;
	
	if(!fs_inode_load(inumber, &inode) || !mounted) return 0;

	int size = inode.size;

	if(offset >= size) return 0;

	int block_offset = offset / Disk::DISK_BLOCK_SIZE;

	int destination_offset = 0;
	int aux_offset = offset; int aux_length = length + offset;
	int bytes_to_copy = Disk::DISK_BLOCK_SIZE;

	for(int i = block_offset; i < POINTERS_PER_INODE; ++i){
		int current_block = inode.direct[i];
		if(current_block <= 0) break;

		union fs_block aux;
		disk->read(current_block, aux.data);
		aux_offset += Disk::DISK_BLOCK_SIZE;

		if(aux_offset > aux_length) return length;
		if(aux_offset > size) bytes_to_copy = size % Disk::DISK_BLOCK_SIZE;
		
		for(int j = 0; j < bytes_to_copy; ++j) data[destination_offset++] = aux.data[j];
		
	}

	bytes_to_copy = Disk::DISK_BLOCK_SIZE;
	block_offset = (aux_offset / Disk::DISK_BLOCK_SIZE) - POINTERS_PER_INODE;

	if(inode.indirect){
		union fs_block indirect_block;
		disk->read(inode.indirect, indirect_block.data);
		for(int i = block_offset; i < POINTERS_PER_BLOCK; ++i){
			int current_block = indirect_block.pointers[i];
			if(current_block <= 0) break;

			union fs_block aux;
			disk->read(current_block, aux.data);
			aux_offset += Disk::DISK_BLOCK_SIZE;

			if(aux_offset > aux_length) return length;
			if(aux_offset > size) bytes_to_copy = size % Disk::DISK_BLOCK_SIZE;
			for(int j = 0; j < bytes_to_copy; ++j) data[destination_offset++] = aux.data[j];
			
			}
	}
	
	if(length + offset > size) return size - offset;

	return length;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{

	if(!fs_check_inumber(inumber) || !mounted || BYTES_PER_INODE <= offset)
		return 0;

	if (BYTES_PER_INODE <= offset + length)
		length = BYTES_PER_INODE - offset;

	// Temos 5 ponteiros diretos e um indireto, o qual equivale a 1024 diretos
	// Assim start_pointer_block pode assumir um valor entre 0 a 1028 (1024 + 5 - 1), inclusos
	// O end_pointer_block também pode assumir um valor entre 0 a 1028, inclusos
	// Se start_block_pointer tiver valor de 0 a 4, então ele vai ter que pegar blocos
	// apontados pelos ponteiros diretos
	int start_block_pointer = offset / Disk::DISK_BLOCK_SIZE;
	int end_block_pointer = (length + offset - 1) / Disk::DISK_BLOCK_SIZE;

	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	// Ler todos os blocos que serão modificados
	string blocks_content = "";
	
	// Faz a leitura dos blocos e, se ele não existir, aloca memória para isso. Se não for possível alocar, retorna erro
	for (int i = start_block_pointer; i < end_block_pointer + 1; i++) {
		fs_block block, aux;
		int pointer = 0;
		
		disk->read(inode_block, block.data);

		if (i < 5) {
			pointer = block.inode[inode_line].direct[i];
			
			if (pointer == 0)
				pointer = fs_allocate_block();
			
			if (pointer == 0)
				return 0;
			
			block.inode[inode_line].direct[i] = pointer;

		} else {

			if (block.inode[inode_line].indirect == 0)
				block.inode[inode_line].indirect = fs_allocate_block();

			if (block.inode[inode_line].indirect == 0)
				return 0;
			
			disk->read(block.inode[inode_line].indirect, aux.data);
			pointer = aux.pointers[i - 5];

			if (pointer == 0)
				pointer = fs_allocate_block();
			
			if (pointer == 0)
				return 0;

			aux.pointers[i - 5] = pointer;
			disk->write(block.inode[inode_line].indirect, aux.data);			
		}

		disk->write(inode_block, block.data);
		disk->read(pointer, aux.data);
		blocks_content += aux.data;
	}

	// Escrever em todos os blocos que serão modificados
	string aux(data);
	blocks_content.replace(offset % Disk::DISK_BLOCK_SIZE, aux.size(), aux);

	// Assume-se que os blocos estão alocados já, então apenas escreve neles
	for (int i = start_block_pointer; i < end_block_pointer + 1; i++) {
		fs_block block, aux;
		int pointer;
		disk->read(inode_block, block.data);

		if (i < 5) {
			pointer = block.inode[inode_line].direct[i];
		} else {
			disk->read(block.inode[inode_line].indirect, aux.data);
			pointer = aux.pointers[i - 5];
		}

		disk->write(pointer, blocks_content.substr(i * Disk::DISK_BLOCK_SIZE, (i + 1) * Disk::DISK_BLOCK_SIZE).c_str());

	}

	fs_block block;
	disk->read(inode_block, block.data);
	block.inode[inode_line].size += length;
	block.inode[inode_line].isvalid = 1;
	disk->write(inode_block, block.data);
	
	return length;
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

int INE5412_FS::fs_allocate_block() {
	fs_block block;
	disk->read(0, block.data);

	for (long unsigned int i = block.super.ninodeblocks + 1; i < free_block_bitmap.size(); i++) {
		if (free_block_bitmap[i] == 0) {
			char data[Disk::DISK_BLOCK_SIZE] = {0};
			disk->write(i, data);
			free_block_bitmap[i] = 1;
			return i;
		}
	}

	cout << free_block_bitmap.size() << endl;

	return 0;
}

int INE5412_FS::fs_get_inode_block(int inumber) {
	return (inumber / INODES_PER_BLOCK) + 1;
}

int INE5412_FS::fs_get_inode_line(int inumber) {
	return inumber % INODES_PER_BLOCK;
}

int INE5412_FS::fs_inode_load(int inumber, fs_inode *inode) {

	if(!fs_check_inumber(inumber)) return 0;

	inumber--;

	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	fs_block block;
	disk->read(inode_block, block.data);

	*inode = block.inode[inode_line];

	return 1;

}
int INE5412_FS::fs_inode_save( int inumber, fs_inode *inode ) {
	if(!fs_check_inumber(inumber)) return 0;

	inumber--;

	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	fs_block block;
	disk->read(inode_block, block.data);

	block.inode[inode_line] = *inode;

	disk->write(inode_block, block.data);

	return 1;
}