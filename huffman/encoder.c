#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

#define MAXCODELEN 256

int main(int argc, char *argv[])
{
	char code[256][MAXCODELEN + 2] = {0};
	FILE *fp;
	int ch;

	if (argc != 2) {
		errx(1, "Usage: encoder [FILE]");
		exit(EXIT_FAILURE);
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
		err(1, "fopen failed");
		exit(EXIT_FAILURE);
	}
	while ((ch = fgetc(fp)) != EOF) {
		fgets(code[ch], MAXCODELEN + 2, fp);
		if (code[ch][strlen(code[ch]) - 1] == '\n')
			code[ch][strlen(code[ch]) - 1] = '\0';
	}
	fclose(fp);
	while ((ch = getchar()) != '.' && ch != EOF) {
		fputs(code[ch], stdout);
	}
	return 0;
}
