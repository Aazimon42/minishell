#include <stdio.h>

int	main(int argc, char **argv)
{
	int i = 1;

	while (i < argc) {
		printf("ARG %d = [%s]\n", i, argv[i]);
		i++;
	}
}
