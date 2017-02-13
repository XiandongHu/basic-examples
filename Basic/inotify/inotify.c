#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <sys/inotify.h>

#define ERROR(text) error(1, errno, "%s", text)

struct EventMask
{
	int flag;
	const char* name;
};

int readFile(void* dest, size_t remain, FILE* file)
{
	char* offset = (char*) dest;
	while (remain) {
		int n = fread(offset, 1, remain, file);
		if (n == 0) {
			return -1;
		}

		remain -= n;
		offset += n;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	const char* target;
	if (argc == 1) {
		target = ".";
	} else {
		target = argv[1];
	}

	EventMask eventMasks[] = {
		{IN_ACCESS, "IN_ACCESS"},
		{IN_ATTRIB, "IN_ATTRIB"},
		{IN_CLOSE_WRITE, "IN_CLOSE_WRITE"},
		{IN_CLOSE_NOWRITE, "IN_CLOSE_NOWRITE"},
		{IN_CREATE, "IN_CREATE"},
		{IN_DELETE, "IN_DELETE"},
		{IN_DELETE_SELF, "IN_DELETE_SELF"},
		{IN_MODIFY, "IN_MODIFY"},
		{IN_MOVE_SELF, "IN_MOVE_SELF"},
		{IN_MOVED_FROM, "IN_MOVED_FROM"},
		{IN_MOVED_TO, "IN_MOVED_TO"},
		{IN_OPEN, "IN_OPEN"},

		{IN_DONT_FOLLOW, "IN_DONT_FOLLOW"},
		{IN_EXCL_UNLINK, "IN_EXCL_UNLINK"},
		{IN_MASK_ADD, "IN_MASK_ADD"},
		{IN_ONESHOT, "IN_ONESHOT"},
		{IN_ONLYDIR, "IN_ONLYDIR"},

		{IN_IGNORED, "IN_IGNORED"},
		{IN_ISDIR, "IN_ISDIR"},
		{IN_Q_OVERFLOW, "IN_Q_OVERFLOW"},
		{IN_UNMOUNT, "IN_UNMOUNT"},
	};

	int monitor = inotify_init();
	if (-1 == monitor) {
		ERROR("inotify_init");
	}

	int watcher = inotify_add_watch(monitor, target, IN_ALL_EVENTS);
	if (-1 == watcher) {
		ERROR("inotify_add_watch");
	}

	FILE* monitorFile = fdopen(monitor, "r");
	char event_buf[512];
	struct inotify_event* event;
	char lastName[1024];
	char name[1024];

	/**
	 * see inotify_event structure
	 * event:inotify_event -> name:char[event.len]
	 */
	while (true) {
		/*inotify_event event;
		if (-1 == readFile(&event, sizeof(event), monitorFile)) {
			ERROR("readFile");
		}
		if (event.len) {
			readFile(name, event.len, monitorFile);
		} else {
			sprintf(name, "FD: %d\n", event.wd);
		}

		if (strcmp(name, lastName) != 0) {
			puts(name);
			strcpy(lastName, name);
		}

		for (int i = 0; i < sizeof(eventMasks) / sizeof(EventMask); ++i) {
			if (event.mask & eventMasks[i].flag) {
				printf("\t%s\n", eventMasks[i].name);
			}
		}*/

		int event_pos = 0;
		int num_bytes = read(monitor, event_buf, sizeof(event_buf));
		if (num_bytes < (int) sizeof(*event)) {
			if (errno == EINTR) {
				continue;
			}
			ERROR("read, got a short event!");
			break;
		}
		while (num_bytes >= (int) sizeof(*event)) {
			int event_size;
			event = (struct inotify_event*) (event_buf + event_pos);
			if (event->len) {
				strcpy(name, event->name);
			} else {
				sprintf(name, "FD: %d\n", event->wd);
			}
			event_size = sizeof(*event) + event->len;
			num_bytes -= event_size;
			event_pos += event_size;
		}

		if (strcmp(name, lastName) != 0) {
			puts(name);
			strcpy(lastName, name);
		}

		for (int i = 0; i < sizeof(eventMasks) / sizeof(EventMask); ++i) {
			if (event->mask & eventMasks[i].flag) {
				printf("\t%s\n", eventMasks[i].name);
			}
		}
	}

	return 0;
}
