#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

ssize_t	ft_read(int fd, void *buf, size_t count);

int	main(void)
{
	int		fds[2];
	char	buf[16] = {0};
	ssize_t	ret;

	CHECK(pipe(fds) == 0);
	CHECK(write(fds[1], "hello", 5) == 5);
	ret = ft_read(fds[0], buf, sizeof buf);
	CHECK(ret == 5);
	CHECK(strcmp(buf, "hello") == 0);

	CHECK(write(fds[1], "abcdef", 6) == 6);
	memset(buf, 0, sizeof buf);
	CHECK(ft_read(fds[0], buf, 3) == 3);
	CHECK(strncmp(buf, "abc", 3) == 0);

	close(fds[1]);
	CHECK(ft_read(fds[0], buf, 3) == 3);
	CHECK(ft_read(fds[0], buf, sizeof buf) == 0);

	errno = 0;
	ret = ft_read(-1, buf, 1);
	CHECK(ret == -1);
	CHECK(errno == EBADF);
	close(fds[0]);
	REPORT();
}
