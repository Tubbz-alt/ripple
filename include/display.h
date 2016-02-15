#include <string.h>

#define RED "\x1b[0;31m"
#define RST "\x1b[0m"

#define DUMPREG64(x, y, z) \
	do {\
		if (y->x == z->x)\
		printf(REGFMT64, y->x); \
		else \
		printf(RED REGFMT64 RST, y->x); \
	} while (0)

#define PRINTREG64(x, y, z, t) \
	do {\
		if (strlen(#x) == 2) \
		printf(#x" :"); \
		else \
		printf(#x":"); \
		DUMPREG64(x, y, z); \
		printf("%s", t);\
	} while (0)

#define DUMPREG32(x, y, z) \
	do {\
		if (y->x == z->x)\
		printf(REGFMT32, y->x); \
		else \
		printf(RED REGFMT32 RST, y->x); \
	} while (0)

#define PRINTREG32(x, y, z, t) \
	do {\
		if (strlen(#x) == 2) \
		printf(#x" :"); \
		else \
		printf(#x":"); \
		DUMPREG32(x, y, z); \
		printf("%s", t);\
	} while (0)

#define DUMPREG16(x, y, z) \
	do {\
		if (y->x == z->x)\
		printf(REGFMT16, y->x); \
		else \
		printf(RED REGFMT16 RST, y->x); \
	} while (0)

#define PRINTREG16(x, y, z, t) \
	do {\
		if (strlen(#x) == 2) \
		printf(#x" :"); \
		else \
		printf(#x":"); \
		DUMPREG16(x, y, z); \
		printf("%s", t);\
	} while (0)

#define DUMPREG8(x, y, z) \
	do {\
		if (y->x == z->x)\
		printf(REGFMT8, y->x); \
		else \
		printf(RED REGFMT8 RST, y->x); \
	} while (0)

#define PRINTREG8(x, y, z,t) \
	do {\
		if (strlen(#x) == 2) \
		printf(#x" :"); \
		else \
		printf(#x":"); \
		DUMPREG8(x, y ,z); \
		printf("%s", t);\
	} while (0)

#define PRINTBIT(name, y, z, t) \
	do {\
		if (y == z) \
		printf("%s%d", name, y); \
		else \
		printf(RED "%s%d" RST, name, y); \
		printf("%s", t); \
	} while (0)

void display_amd64(
		const struct proc_info_t *const);
void display_x86(
		const struct proc_info_t *const);
void display_arm(
		const struct proc_info_t *const);