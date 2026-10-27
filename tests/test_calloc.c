#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include "test.h"

void	*ft_calloc(size_t nmemb, size_t size);

static int	is_zero(const unsigned char *p, size_t n)
{
	for (size_t i = 0; i < n; i++)
		if (p[i])
			return (0);
	return (1);
}

int	main(void)
{
	unsigned char	*p;
	volatile size_t	big = SIZE_MAX;
	volatile size_t	half = SIZE_MAX / 2 + 1;

	p = ft_calloc(10, 4);
	CHECK(p != NULL);
	CHECK(p && is_zero(p, 40));
	free(p);

	p = ft_calloc(1, 1);
	CHECK(p != NULL);
	CHECK(p && is_zero(p, 1));
	free(p);

	p = ft_calloc(1000, 1000);
	CHECK(p != NULL);
	CHECK(p && is_zero(p, 1000000));
	free(p);

	free(ft_calloc(0, 4));
	free(ft_calloc(4, 0));

	errno = 0;
	CHECK(ft_calloc(big, 2) == NULL);
	CHECK(errno == ENOMEM);
	errno = 0;
	CHECK(ft_calloc(half, 2) == NULL);
	CHECK(errno == ENOMEM);
	REPORT();
}
