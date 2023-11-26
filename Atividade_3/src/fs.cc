#include "fs.h"
#include <cstring>
#include <cmath>


INE5412_FS::INE5412_FS(Disk *d) {
	disk = d;
	mounted = 0;
}

int INE5412_FS::fs_format()
{
	union fs_block block;
	char data[Disk::DISK_BLOCK_SIZE] = {0};
	
	// Verificando se já não foi montado o disco
	if(mounted) 
		return 0;

	// Limpando todo o disco
	for(int i = 0; i < disk->size(); i++)
		disk->write(i, data);

	// Resetando o bitmap
	free_block_bitmap.clear();
	for (int i = 0; i < disk->size(); i++)
		free_block_bitmap.push_back(0);

	// Definindo o superblock
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

	// Mostrando as informações do superbloco
	disk->read(0, block.data);
	cout << "superblock:\n";
	cout << "    " << (block.super.magic == FS_MAGIC ? "magic number is valid\n" : "magic number is invalid!\n");
 	cout << "    " << block.super.nblocks << " blocks on disk\n";
	cout << "    " << block.super.ninodeblocks << " blocks for inodes\n";
	cout << "    " << block.super.ninodes << " inodes total\n";

	// Mostrandos os inodes válidos
	for (int i = 1; i < block.super.ninodes; i++) {
		union fs_block aux;
		fs_inode inode;

		// Caso o inode seja inválido, então passa para o próximo
		if(!fs_inode_load(i, &inode) || !inode.isvalid)
			continue;

		// Mostra o tamanho e os blocos diretos do inode válido
		cout << "inode " << i << ":\n";
		cout << "    size: " << inode.size << " bytes\n";
		cout << "    direct blocks:";

		for(int k = 0; k < POINTERS_PER_INODE; k++)
			if(inode.direct[k])
				cout << " " << inode.direct[k];

		cout << "\n";

		// Mostra o bloco indireto caso o inode válido tenha
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
	union fs_block block, aux;
	fs_inode inode;
	disk->read(0, block.data);

	// Verificando se já não foi montado e se o número mágico é válido
	if(mounted || block.super.magic != FS_MAGIC) 
		return 0;

	// Limpando o bitmap
	free_block_bitmap.clear();
	for (int i = 0; i < disk->size(); i++)
		free_block_bitmap.push_back(0);

	// Vendo quais blocos estão sendo usados pelos inodes
	for (int i = 1; i < block.super.ninodes; i++) {

		// Verificando se o inode foi carregado com sucesso e se é válido
		if(!fs_inode_load(i, &inode) || !inode.isvalid)
			continue;

		// Analisando os ponteiros diretos
		for (int j = 0; j < POINTERS_PER_INODE; j++)
			if (fs_check_numblock(inode.direct[j]))
				free_block_bitmap[inode.direct[j]] = 1;

		// Para o caso de o inode não ter bloco indireto
		if (!inode.indirect)
			continue;

		// Definindo como ocupado o bloco usado pelo ponteiro indireto
		free_block_bitmap[inode.indirect] = 1;
		disk->read(inode.indirect, aux.data);

		// Definindo como ocupado os blocos apontados pelo bloco indireto	
		for (int j = 0; j < POINTERS_PER_BLOCK; j++)
			if (fs_check_numblock(aux.pointers[j]))
				free_block_bitmap[aux.pointers[j]] = 1;

	}

	// Definindo mounted como 1 para saber se já foi montado o disco
	mounted = 1;

	return 1;
}

int INE5412_FS::fs_create()
{
	union fs_block block;
	fs_inode inode;
	disk->read(0, block.data);

	// Verificando se já não foi montado e se o número mágico é válido
	if(!mounted || block.super.magic != FS_MAGIC) 
		return 0;

	// Vendo quais blocos estão sendo usados pelos inodes
	for (int i = 1; i < block.super.ninodes; i++) {

		// Verificando se o inode foi carregado com sucesso e se é válido
		if(!fs_inode_load(i, &inode) || inode.isvalid)
			continue;

		// Se encontrou um inode livre, então reseta as informações dele e define-o como ocupado
		inode.isvalid = 1;
		inode.size = 0;
		inode.indirect = 0;

		for (int j = 0; j < POINTERS_PER_INODE; j++)
			inode.direct[j] = 0;

		// Salvando o inode
		if(!fs_inode_save(i, &inode)) 
			return 0;

		return i;
	}

	return 0;
}

int INE5412_FS::fs_delete(int inumber)
{
	union fs_block block, super;
	fs_inode inode;
	disk->read(0, super.data);

	// Verificando se já não foi montado e se o número mágico é válido
	if (!fs_inode_load(inumber, &inode) || !mounted || super.super.magic != FS_MAGIC)
		return 0;

	// Desocupando inode
	inode.isvalid = 0;
	inode.size = 0;

	// Desalocando blocos usados pelo inode por meio dos ponteiros diretos
	for(int i = 0; i < POINTERS_PER_INODE; i++)
		if (fs_check_numblock(inode.direct[i]))
			free_block_bitmap[inode.direct[i]] = 0;

	// Desalocando blocos usados pelo inode por meio do ponteiro indireto
	if(inode.indirect) {
		for(int i = 0; i < POINTERS_PER_BLOCK; i++)
			if (fs_check_numblock(block.pointers[i]))
				free_block_bitmap[block.pointers[i]] = 0;

		free_block_bitmap[inode.indirect] = 0;
	}

	// Salvando o inode agora desocupado no disco
	if(!fs_inode_save(inumber, &inode)) 
		return 0;

	return 1;
}

int INE5412_FS::fs_getsize(int inumber)
{
	union fs_block super;
	fs_inode inode;
	disk->read(0, super.data);

	// Verificando se o inode foi carregado corretamente, se o disco está montado e se o número mágico é válido
	if(!fs_inode_load(inumber, &inode) || !mounted || super.super.magic != FS_MAGIC) 
		return -1;

	return inode.size;
}

int INE5412_FS::fs_read(int inumber, char *data, int length, int offset)
{
	fs_inode inode;
	
	if(!fs_inode_load(inumber, &inode) || !mounted) return 0;
	
	int size = inode.size;
	// Verificando se o offset é maior que o tamanho do arquivo, se sim as chamadas da função terminam
	if(offset >= size) return 0;

	// Pegando nosso bloco inicial
	int block_offset = offset / Disk::DISK_BLOCK_SIZE;

	// Contador para jogar os dados no data
	int destination_offset = 0;
	// Variavel para controlar quantos bytes ja foram copiados
	int aux_offset = offset; 
	// Variavel para controlar para controlar o numero de bytes para copiar naquela chamada de funcao
	int aux_length = length + offset;
	// Variavel para controlar quantos bytes devem ser copiados
	int bytes_to_copy = Disk::DISK_BLOCK_SIZE;

	for(int i = block_offset; i < POINTERS_PER_INODE; ++i){
		// Variavel para controlar o bloco atual
		int current_block = inode.direct[i];
		// Se acaso nao tiver mais blocos para ler, termina a funcao
		if(current_block <= 0) break;

		union fs_block aux;
		// Lendo o bloco atual
		disk->read(current_block, aux.data);
		// Incrementando o aux_offset com o valor de bytes de um bloco
		aux_offset += Disk::DISK_BLOCK_SIZE;
		// Caso o aux_offset extrapolou a quantidade de bytes para serem lidos nessa chamada de funcao, faz um early return
		if(aux_offset > aux_length) return length;
		// Caso o aux_offset extrapolou a quantidade de bytes do arquivo, entao copia apenas o que falta
		if(aux_offset > size) bytes_to_copy = size % Disk::DISK_BLOCK_SIZE;
		// Copiando os bytes para o data
		for(int j = 0; j < bytes_to_copy; ++j) data[destination_offset++] = aux.data[j];
		
	}
	// Atualizando bytes to copy para o valor de um bloco
	// pois agora vamos ler os blocos indiretos
	bytes_to_copy = Disk::DISK_BLOCK_SIZE;
	// Atualizando o bloco offset para o bloco respectivo dos indiretos
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
	// Caso o offset + length seja maior que o tamanho do arquivo, retorna o tamanho do arquivo - offset(o length para aquela chamada de funcão)
	if(length + offset > size) return size - offset;

	return length;
}

int INE5412_FS::fs_write(int inumber, const char *data, int length, int offset)
{
	union fs_block super, block;
	fs_inode inode;
	string blocks_content = "";
	string aux(data);
	disk->read(0, super.data);

	if(!fs_inode_load(inumber, &inode) || !mounted || BYTES_PER_INODE <= offset || super.super.magic != FS_MAGIC)
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
	
	// Faz a leitura dos blocos e, se ele não existir, aloca memória para isso. Se não for possível alocar, retorna erro
	for (int i = start_block_pointer; i < end_block_pointer + 1; i++) {
		int pointer = 0;

		if (i < POINTERS_PER_INODE) {
			pointer = inode.direct[i];
			
			// Se não está alocado o ponteiro direto, aloca
			if (pointer == 0)
				pointer = fs_allocate_block();
			
			// Se não conseguiu alocar, então retorna zero
			if (pointer == 0)
				return 0;
			
			// Define o ponteiro direto alocado
			inode.direct[i] = pointer;

		} else {

			// Se não está alocado o ponteiro indireto, aloca
			if (inode.indirect == 0)
				inode.indirect = fs_allocate_block();

			// Se não conseguiu alocar, então retorna zero
			if (inode.indirect == 0)
				return 0;
			
			// Carrega bloco do indireto
			disk->read(inode.indirect, block.data);
			pointer = block.pointers[i - 5];

			// Se não está alocado o ponteiro do bloco indireto, então aloca
			if (pointer == 0)
				pointer = fs_allocate_block();
			
			// Se não conseguiu alocar, então retorna zero
			if (pointer == 0)
				return 0;

			// Escreve em disco a modificação do bloco indireto
			block.pointers[i - 5] = pointer;
			disk->write(inode.indirect, block.data);			
		}

		// Escreve em disco as mudanças feitas no inode
		if (!fs_inode_save(inumber, &inode))
			return 0;

		// Lê o conteudo do bloco que será modificado
		disk->read(pointer, block.data);
		blocks_content += block.data;
	}

	// Escrevendo em cima do conteudo dos blocos
	blocks_content.replace(offset % Disk::DISK_BLOCK_SIZE, aux.size(), aux);

	// Escreve em disco as modificações nos blocos 
	// (muito similar ao for de cima, só que assumindo que tudo está alocado)
	for (int i = start_block_pointer; i < end_block_pointer + 1; i++) {
		int pointer;

		// If para ver se o bloco está sendo apontado por um ponteiro direto ou indireto
		if (i < POINTERS_PER_INODE) {
			pointer = inode.direct[i];
		} else {
			disk->read(inode.indirect, block.data);
			pointer = block.pointers[i - 5];
		}

		// Escreve o conteudo do bloco modificaod em disco
		disk->write(pointer, blocks_content.substr((i - start_block_pointer) * Disk::DISK_BLOCK_SIZE,
		 (i + 1 - start_block_pointer) * Disk::DISK_BLOCK_SIZE).c_str());
	}

	// Escrevendo em disco as modificações do inode
	if (inode.size < offset + length)
		inode.size = offset + length;
	
	inode.isvalid = 1;
	if (!fs_inode_save(inumber, &inode))
		return 0;
	
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

	return 0;
}

int INE5412_FS::fs_get_inode_block(int inumber) {
	inumber--;
	return (inumber / INODES_PER_BLOCK) + 1;
}

int INE5412_FS::fs_get_inode_line(int inumber) {
	inumber--;
	return inumber % INODES_PER_BLOCK;
}

int INE5412_FS::fs_inode_load(int inumber, fs_inode *inode) {

	if(!fs_check_inumber(inumber)) 
		return 0;

	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	fs_block block;
	disk->read(inode_block, block.data);
	*inode = block.inode[inode_line];

	return 1;

}

int INE5412_FS::fs_inode_save( int inumber, fs_inode *inode ) {
	
	if(!fs_check_inumber(inumber)) 
		return 0;

	int inode_block = fs_get_inode_block(inumber);
	int inode_line = fs_get_inode_line(inumber);

	fs_block block;
	disk->read(inode_block, block.data);
	block.inode[inode_line] = *inode;
	disk->write(inode_block, block.data);

	return 1;
}