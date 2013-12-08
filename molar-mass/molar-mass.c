#include <stdio.h>
#include "molar-masses.h"

#define UPPER 'A'
#define LOWER ('a' - 1)

#define GET_MASS(id) ((id) <= MM_COUNT ? molar_masses[(id) - 1] : 0.0)
#define ADD_MASS(id) \
	{ \
		float mass = GET_MASS(id); \
		\
		if (!mass) { \
			fprintf(stderr, "Invalid element: %c%c", 'A' + id % 26, id < 26 ? '\n' : '`' + id / 26); \
			if (id >= 26) putchar('\n'); \
			return 1; \
		} \
		\
		total += mass * (count ? count : 1); \
	}

int main(const int argc, const char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage:  %s <simple-formula>\n", argv[0]);
		return 1;
	}

	const char* formula = argv[1];

	float total = 0.0;

	int id = 0;
	int seen = 0;
	int count = 0;
	char c;

	while ((c = *formula++)) {
		if (c < '0') {
			fprintf(stderr, "Unexpected %c.\n", c);
			return 1;
		}

		if (c < ':') {
			if (!seen) {
				fprintf(stderr, "Unexpected digit %c.\n", c);
				return 1;
			}

			count = count * 10 + c - '0';
			continue;
		}

		if (c < 'A') {
			fprintf(stderr, "Unexpected %c.\n", c);
			return 1;
		}

		if (c < '[') {
			if (seen) {
				ADD_MASS(id)
				count = 0;
			}

			id = c - 'A';
			seen = 1;
			continue;
		}

		if (c < 'a') {
			fprintf(stderr, "Unexpected %c.\n", c);
			return 1;
		}

		if (c < '{') {
			if (!seen || id >= 26) {
				fprintf(stderr, "Unexpected lowercase %c.\n", c);
				return 1;
			}

			id += (c - '`') * 26;
		}
	}

	ADD_MASS(id)
	printf("%f g/mol\n", total);

	return 0;
}
