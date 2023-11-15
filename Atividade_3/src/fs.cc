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
 	cout << "    " << block.super.nblocks << " blocks on disk\n";
	cout << "    " << block.super.ninodeblocks << " blocks for inodes\n";
	cout << "    " << block.super.ninodes << " inodes total\n";

	for(int i = 1; i <= block.super.ninodeblocks; i++){
		disk->read(i, block.data);
		for(int j = 0; j < INODES_PER_BLOCK; j++){
			if(block.inode[j].isvalid){
				cout << "inode " << (i-1)*INODES_PER_BLOCK + j << ":\n";
				cout << "    size: " << block.inode[j].size << " bytes\n";
				cout << "    direct blocks:";
				for(int k = 0; k < POINTERS_PER_INODE; k++){
					if(block.inode[j].direct[k]){
						cout << " " << block.inode[j].direct[k];
					}
				}
				cout << "\n";
				if(block.inode[j].indirect){
					cout << "    indirect block: " << block.inode[j].indirect << "\n";
					disk->read(block.inode[j].indirect, block.data);
					cout << "    indirect data blocks:";
					for(int k = 0; k < POINTERS_PER_BLOCK; k++){
						if(block.pointers[k]){
							cout << " " << block.pointers[k];
						}
					}
					cout << "\n";
				}
			}
		}
	}
}

// Examina o disco para um sistema de arquivos. Se um est´a presente, lˆe o superbloco, constroi um
// bitmap de blocos livres, e prepara o sistema de arquivos para uso. Retorna um em caso de sucesso, zero
// caso contr´ario. Note que uma montagem bem-sucedida ´e um pr´e-requisito para as outras chamadas.
int INE5412_FS::fs_mount()
{
	union fs_block block;
	disk->read(0, block.data);
	if(block.super.magic != FS_MAGIC){
		return 0;
	}
	// TODO: bitmap
	// percorrer todos os blocos e marcar os que estao ocupados, acredito que so verificar se o data[i] = tudo 0
	// ai criar um bitmap com os blocos livres, cada bloco do bitmap tem 32bits
	return 1;
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
