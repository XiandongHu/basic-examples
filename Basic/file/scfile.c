#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "scfile.h"

#define HEADER_SIZE sizeof(SC_Header)
#define BLOCK_SIZE sizeof(SC_Block)

static const char* DATA_FILE = "SmartTask.sc";

static bool check_file()
{
	FILE* fp = fopen(DATA_FILE, "rb");
	if (!fp) {
		return false;
	}

	long size = HEADER_SIZE;
	SC_Header header;
	memset(&header, 0, size);
	if (fread(&header, size, 1, fp) == 1) {
		if (header.ident[0] == 0x8F && header.ident[1] == 0x53 && header.ident[2] == 0x43) {
			fseek(fp, 0, SEEK_END);
			int end = ftell(fp);
			if ((end - size) % BLOCK_SIZE == 0) {
				fclose(fp);
				return true;
			}
		}
	}

	fclose(fp);
	return false;
}

static bool write_header()
{
	FILE* fp = fopen(DATA_FILE, "wb");
	if (!fp) {
		return false;
	}

	long size = HEADER_SIZE;
	SC_Header header;
	memset(&header, 0, size);
	header.ident[0] = 0x8F;
	header.ident[1] = 0x53;
	header.ident[2] = 0x43;

	int number = fwrite(&header, size, 1, fp);
	fclose(fp);
	return number == 1;
}

static bool check_size(const char* name, const char* action_list, const char* launch)
{
	int name_length = strlen(name);
	int action_list_length = strlen(action_list);
	int launch_length = strlen(launch);
	return name_length < MAX_NAME_SIZE && action_list_length < MAX_ACTION_LIST_SIZE && launch_length < MAX_LAUNCH_SIZE;
}

static bool wind_to_block(FILE* fp, const int id, SC_Block** block)
{
	bool result = false;
	fseek(fp, 0, SEEK_END);
	long end = ftell(fp);
	long offset = HEADER_SIZE;
	if (end > offset) {
		fseek(fp, offset, SEEK_SET);
		long size = BLOCK_SIZE;
		*block = (SC_Block*) malloc(size);
		memset(*block, 0, size);
		int number = fread(*block, size, 1, fp);
		while (number == 1 && !feof(fp)) {
			if ((*block)->id == id) {
				result = true;
				break;
			}
			number = fread(*block, size, 1, fp);
		}
	}

	return result;
}

bool SC_Init(Callback callback)
{
	if (!check_file() && !write_header()) {
		return false;
	}

	FILE* fp = fopen(DATA_FILE, "rb");
	if (!fp) {
		return false;
	}

	fseek(fp, 0, SEEK_END);
	long end = ftell(fp);
	long offset = HEADER_SIZE;
	if (end > offset) {
		fseek(fp, offset, SEEK_SET);
		long size = BLOCK_SIZE;
		SC_Block* block = (SC_Block*) malloc(size);
		memset(block, 0, size);
		int number = fread(block, size, 1, fp);
		while (number == 1 &&!feof(fp)) {
			callback(block);
			number = fread(block, size, 1, fp);
		}
		free(block);
	}

	fclose(fp);
	return true;
}

bool SC_AddBlock(const int id, const char* name, const char* action_list, const char* launch)
{
	FILE* fp = fopen(DATA_FILE, "r+b");
	if (!fp) {
		return false;
	}

	if (!check_size(name, action_list, launch)) {
		return false;
	}

	SC_Block* block = NULL;
	if (wind_to_block(fp, id, &block)) {
		free(block);
		return false;
	}

	long size = BLOCK_SIZE;
	if (!block) {
		block = (SC_Block*) malloc(size);
	}
	memset(block, 0, size);
	block->id = id;
	strcpy(block->name, name);
	strcpy(block->action_list, action_list);
	strcpy(block->launch, launch);

	fseek(fp, 0, SEEK_END);
	int number = fwrite(block, size, 1, fp);
	free(block);

	fclose(fp);
	return number == 1;
}

bool SC_UpdateBlock(const int id, const char* name, const char* action_list, const char* launch)
{
	FILE* fp = fopen(DATA_FILE, "r+b");
	if (!fp) {
		return false;
	}

	if (!check_size(name, action_list, launch)) {
		return false;
	}

	SC_Block* block = NULL;
	bool result = wind_to_block(fp, id, &block);
	if (result) {
		long size = BLOCK_SIZE;
		memset(block, 0, size);
		block->id = id;
		strcpy(block->name, name);
		strcpy(block->action_list, action_list);
		strcpy(block->launch, launch);

		fseek(fp, -size, SEEK_CUR);
		result = fwrite(block, size, 1, fp) == 1;
	}
	if (block) {
		free(block);
	}

	fclose(fp);
	return result;
}

bool SC_DeleteBlock(const int id)
{
	FILE* fp = fopen(DATA_FILE, "r+b");
	if (!fp) {
		return false;
	}

	SC_Block* block = NULL;
	bool result = wind_to_block(fp, id, &block);
	if (result) {
		long size = BLOCK_SIZE;
		memset(block, 0, size);
		int number = fread(block, size, 1, fp);
		if (number == 1 && !feof(fp)) {
			while (number == 1 && !feof(fp)) {
				fseek(fp, -(size << 1), SEEK_CUR);
				if (fwrite(block, size, 1, fp) != 1) {
					result = false;
					break;
				}
				fseek(fp, size, SEEK_CUR);
				number = fread(block, size, 1, fp);
			}
		}
		if (result) {
			result = ftruncate(fileno(fp), ftell(fp) - size) == 0;
		}
	}
	if (block) {
		free(block);
	}

	fclose(fp);
	return result;
}

bool SC_ResetBlocks()
{
	FILE* fp = fopen(DATA_FILE, "r+b");
	if (!fp) {
		return false;
	}

	bool result = ftruncate(fileno(fp), HEADER_SIZE) == 0;
	fclose(fp);
	return result;
}
