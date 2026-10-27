#include <string.h>
#include "test.h"

size_t	ft_strlen(const char *s);

int	main(void)
{
	static char	big[10001];
	const char	*cases[] = {"", "a", "hello", "hello world", "abc\0def"};

	for (size_t i = 0; i < sizeof cases / sizeof *cases; i++)
		CHECK(ft_strlen(cases[i]) == strlen(cases[i]));
	memset(big, 'x', 10000);
	CHECK(ft_strlen(big) == 10000);
	REPORT();
}
