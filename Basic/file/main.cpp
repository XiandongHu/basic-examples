#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <list>

#include "scfile.h"

using namespace std;

class Scene
{
	public:
		Scene(int id, const char* name, const char* action_list, const char* launch) {
			this->id = id;
			this->name = name;
			this->action_list = action_list;
			this->launch = launch;
		}

		inline void print() {
			cout << id << name << action_list << launch << endl;
		}

	private:
		int id;
		string name;
		string action_list;
		string launch;
};

list<Scene*> scenes;

void callback(SC_Block* block)
{
	scenes.push_back(new Scene(block->id, block->name, block->action_list, block->launch));
}

int main(int argc, char** argv)
{
	const char* name = "健康模式";
	const char* action_list = "[{\"thirdParty\": \"xmrouter\", \"type\": \"normal_wifi_down\", \"delay\": 0, \"name\": \"小米路由器\", \"keyName\": \"关闭WiFi 8小时\", \"extra\": {\"duration\": 28800000}}]";
	const char* launch = "{\"timer\": {\"time\": \"23:00:00\", \"repeat\": \"1, 2, 3, 4, 5, 6, 7\", \"enabled\": false}}";

	if (!SC_Init(callback)) {
		printf("### SC_Init Failed\n");
	}

	for (list<Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++) {
		(*it)->print();
		delete *it;
		*it = NULL;
	}
	scenes.clear();

	printf("\n");

	// add
	/*int i = 1;
	for (; i <= 10; i++) {
		if (!SC_AddBlock(i, name, action_list, launch)) {
			printf("### SC_AddBlock Failed\n");
			break;
		}
	}*/

	// update
	/*const char* new_name = "定时关机";
	const char* new_action_list = "[{\"thirdParty\": \"xmrouter\", \"type\": \"normal_shutdown\", \"delay\": 0, \"name\": \"小米路由器\", \"keyName\": \"关机2小时\", \"extra\": {\"duration\": 2880}}]";
	const char* new_launch = "{\"timer\": {\"time\": \"23:00:00\", \"repeat\": \"1, 2, 3, 4, 5\", \"enabled\": false}}";
	if (!SC_UpdateBlock(3, new_name, new_action_list, new_launch)) {
		printf("### SC_UpdateBlock Failed\n");
	}*/

	// delete
	/*if (!SC_DeleteBlock(10)) {
		printf("### SC_DeleteBlock Failed\n");
	}*/
	
	// reset
	/*if (!SC_ResetBlocks()) {
		printf("### SC_ResetBlocks Failed\n");
	}*/

	return 0;
}
