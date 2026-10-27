#ifndef TEST_H
# define TEST_H

# include <stdio.h>

static int	g_total;
static int	g_fails;

# define CHECK(cond) \
	do { \
		g_total++; \
		if (!(cond)) { \
			g_fails++; \
			printf("  FAIL line %d: %s\n", __LINE__, #cond); \
		} \
	} while (0)

# define REPORT() \
	do { \
		printf("  %d/%d passed\n", g_total - g_fails, g_total); \
		return (g_fails != 0); \
	} while (0)

#endif
