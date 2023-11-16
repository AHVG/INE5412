#include "fs.h"
#include <cstring>

int INE5412_FS::fs_format()
{
	char *data = new char[Disk::DISK_BLOCK_SIZE];
	memset(data, 0, Disk::DISK_BLOCK_SIZE);

	for(int i = 0; i < disk->size(); i++) {
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

	for(int i = 1; i <= block.super.ninodeblocks; i++) { // detro deste for tem operações de escrita no block (não acho legal)
		disk->read(i, block.data);
		for(int j = 0; j < INODES_PER_BLOCK; j++) {
			if(block.inode[j].isvalid){
				cout << "inode " << (i - 1) * INODES_PER_BLOCK + j + 1 << ":\n";
				cout << "    size: " << block.inode[j].size << " bytes\n";
				cout << "    direct blocks:";
				for(int k = 0; k < POINTERS_PER_INODE; k++) {
					if(block.inode[j].direct[k]) {
						cout << " " << block.inode[j].direct[k];
					}
				}
				cout << "\n";
				if(block.inode[j].indirect) {
					cout << "    indirect block: " << block.inode[j].indirect << "\n";
					disk->read(block.inode[j].indirect, block.data);
					cout << "    indirect data blocks:";
					for(int k = 0; k < POINTERS_PER_BLOCK; k++) {
						if(block.pointers[k]) {
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

	if(block.super.magic != FS_MAGIC) {
		return 0;
	}

	// Usar bit para representar bloco e não um inteiro (criar uma classe para encapsular esse comportamento?)
	for (int i = block.super.ninodes + 1; i < disk->size(); i++)
		free_block_bitmap.push_back(0);

	// Marcar no bitmap ocupado (1) aqueles blocos para os quais os inodes apontam 
	// A operação de mount não é usada apenas uma vez antes de qualquer coisa? se for o caso, não fa sentido esta etapa
	for (int i = 1; i < block.super.ninodeblocks + 1; i++) {
		union fs_block aux;
		disk->read(i, aux.data);
		
		// Para o caso de o inode não estiver sendo usado
		if (!aux.inode->isvalid)
			continue;

		for (int j = 0; j < POINTERS_PER_INODE; j++)
			if (aux.inode->direct[j] && block.super.ninodes < aux.inode->direct[j] && aux.inode->direct[j] < block.super.nblocks)
				free_block_bitmap[aux.inode->direct[j]] = 1;

		// Para o caso de o inode não ter bloco indireto
		if (!aux.inode->indirect)
			continue;

		disk->read(aux.inode->indirect, aux.data);

		for (int j = 0; j < POINTERS_PER_BLOCK; j++)
			if (aux.pointers[j] && block.super.ninodes < aux.pointers[j] && aux.pointers[j] < block.super.nblocks)
				free_block_bitmap[aux.pointers[j]] = 1;

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
			// Se estiver ocupado, passa para o próximo
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
