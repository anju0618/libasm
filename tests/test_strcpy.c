#include <string.h>
#include "test.h"

char	*ft_strcpy(char *dest, const char *src);

int	main(void)
{
	char		buf[32];
	char		*ret;
	const char	*cases[] = {"", "a", "hello", "hello world"};

	for (size_t i = 0; i < sizeof cases / sizeof *cases; i++)
	{
		memset(buf, 'x', sizeof buf);
		ret = ft_strcpy(buf, cases[i]);
		CHECK(ret == buf);
		CHECK(strcmp(buf, cases[i]) == 0);
		CHECK(buf[strlen(cases[i]) + 1] == 'x');
	}
	REPORT();
}
