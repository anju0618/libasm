#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

ssize_t	ft_write(int fd, const void *buf, size_t count);

int	main(void)
{
	int		fds[2];
	char	buf[16] = {0};
	ssize_t	ret;

	CHECK(pipe(fds) == 0);
	ret = ft_write(fds[1], "hello", 5);
	CHECK(ret == 5);
	CHECK(read(fds[0], buf, sizeof buf) == 5);
	CHECK(strcmp(buf, "hello") == 0);
	CHECK(ft_write(fds[1], "", 0) == 0);

	errno = 0;
	ret = ft_write(-1, "x", 1);
	CHECK(ret == -1);
	CHECK(errno == EBADF);

	close(fds[1]);
	errno = 0;
	ret = ft_write(fds[1], "x", 1);
	CHECK(ret == -1);
	CHECK(errno == EBADF);
	close(fds[0]);
	REPORT();
}
