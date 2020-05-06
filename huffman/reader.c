#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char *argv[])
{
	unsigned long long int count[256] = {0};
	FILE *fp;
	unsigned long long len = 1;
	int uniq = 0, ch;

	if (argc == 2) {
		if ((fp = fopen(argv[1], "w")) == NULL) {
			err(1, "fopen failed");
			exit(EXIT_FAILURE);
		}
		while ((ch = getchar()) != '.' && ch != EOF) {
			++count[ch];
			++len;
			fputc(ch, fp);
		}
		fclose(fp);
	} else {
		while ((ch = getchar()) != '.' && ch != EOF) {
			++count[ch];
			++len;
		}
	}
	for (int i = 0; i < 256; i++)
		if (count[i] != 0)
			++uniq;
	printf("%d\n", uniq);
	if (len == 0) {
		errx(1, "unsigned long long overflow");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 256; i++) {
		if (count[i])
			printf("%0.17Lf %d\n", (long double) count[i] / len, i);
	}
	return 0;
}
