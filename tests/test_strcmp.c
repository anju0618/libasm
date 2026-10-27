#include <string.h>
#include "test.h"

int	ft_strcmp(const char *s1, const char *s2);

static int	sign(int x)
{
	return ((x > 0) - (x < 0));
}

int	main(void)
{
	const char	*cases[] = {"", "a", "ab", "abc", "abd", "b", "hello",
		"hellp", "abc\x7f", "abc\x80", "abc\xff"};
	size_t		n = sizeof cases / sizeof *cases;

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			CHECK(sign(ft_strcmp(cases[i], cases[j]))
				== sign(strcmp(cases[i], cases[j])));
	REPORT();
}
