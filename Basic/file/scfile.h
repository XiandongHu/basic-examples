#ifndef __SC_FILE_H__
#define __SC_FILE_H__

#include "bool.h"

#define MAX_NAME_SIZE 128
#define MAX_ACTION_LIST_SIZE 1024
#define MAX_LAUNCH_SIZE 128

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned char ident[8];
	unsigned int reserved;
} SC_Header;

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
	char action_list[MAX_ACTION_LIST_SIZE];
	char launch[MAX_LAUNCH_SIZE];
} SC_Block;

typedef void (*Callback)(SC_Block* block);

bool SC_Init(Callback callback);
bool SC_AddBlock(const int id, const char* name, const char* action_list, const char* launch);
bool SC_UpdateBlock(const int id, const char* name, const char* action_list, const char* launch);
bool SC_DeleteBlock(const int id);
bool SC_ResetBlocks();

#ifdef __cplusplus
}
#endif

#endif
