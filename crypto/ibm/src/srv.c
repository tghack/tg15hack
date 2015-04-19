#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

const char *const ebcdic = "\xe2\x85\x83\xa4\x99\x89\xa3\xa8\x40\xa3\x88\x99"
			    "\x96\xa4\x87\x88\x40\x96\x82\xa2\xa4\x99\x89\xa3"
			    "\xa8\x40\x86\xa3\xa6\x5a\x40\xe3\x96\x92\x85\x95"
			    "\x7a\x40\xc5\xc2\xc3\xc4\xc9\xc3\x7e\x85\x95\x83"
			    "\x99\xa8\x97\xa3\x89\x96\x95\x25";

static inline int socket_create(const char *port)
{
	struct addrinfo hints, *result, *rp;
	static int yes = 1;
	int sfd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port, &hints, &result)) {
		perror("getaddrinfo()");
		return -1;
	}

	for (rp = result; rp; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if (sfd == -1)
			continue;
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR,
					&yes, sizeof(int)) == -1)
			continue;
		if (!bind(sfd, rp->ai_addr, rp->ai_addrlen))
			break;

		close(sfd);
	}

	freeaddrinfo(result);

	if (!rp) {
		fprintf(stderr, "Could not connect socket to any address!\n");
		return -1;
	}

	return sfd;
}

int main(int argc, char *argv[])
{
	ssize_t ret;
	int sock, cfd;
	socklen_t len;
	struct sockaddr addr;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	sock = socket_create(argv[1]);
	if (sock == -1) {
		exit(EXIT_FAILURE);
	}

	if (listen(sock, SOMAXCONN)) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		len = sizeof(struct sockaddr);
		cfd = accept(sock, (struct sockaddr *)&addr, &len);
		if (cfd == -1) {
			perror("accept");
			continue;
		}

		ret = write(cfd, ebcdic, strlen(ebcdic));
		if (ret == -1)
			perror("write");
		else
			printf("Sent %zd bytes\n", ret);
		close(cfd);
	}

	return 0;
}
