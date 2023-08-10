#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("[Info] Arguments(%i):\n", argc);
	for (int i = 0; i < argc; i++) printf(" - %i: %s\n", i, argv[i]);
}
