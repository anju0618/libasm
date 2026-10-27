#include <stdlib.h>
#include <string.h>
#include "test.h"

char	*ft_strdup(const char *s);

int	main(void)
{
	char		*dup;
	const char	*cases[] = {"", "a", "hello", "hello world"};

	for (size_t i = 0; i < sizeof cases / sizeof *cases; i++)
	{
		dup = ft_strdup(cases[i]);
		CHECK(dup != NULL);
		CHECK(dup != cases[i]);
		CHECK(dup && strcmp(dup, cases[i]) == 0);
		free(dup);
	}
	REPORT();
}
