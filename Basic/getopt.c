#include <stdio.h>
#include <unistd.h>

void print_args(int argc, char** argv)
{
	int i = 0;
	for (; i < argc; i++) {
		printf("argv[%d]=%s ", i, argv[i]);
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	print_args(argc, argv);

	printf("optind=%d, opterr=%d\n", optind, opterr);

	printf("------------------------------\n");
	int ch;
	while ((ch = getopt(argc, argv, "go:")) != -1) {
		printf("ch=%c, optind=%d, argc=%d, argv[%d]=%s\n", ch, optind, argc, optind, argv[optind]);
		switch (ch) {
			case 'g':
				printf("option: -g\n");
				break;
			case 'o':
				printf("option: -o, arg=%s\n", optarg);
				break;
			case '?':
				printf("unknown option: %c\n", (char) optopt);
				break;
		}
	}
	printf("------------------------------\n");

	printf("optind=%d, argv[%d]=%s\n", optind, optind, argv[optind]);

	print_args(argc, argv);

	if (optind < argc) {
		printf("input=%s\n", argv[optind]);
	}

	return 0;
}
