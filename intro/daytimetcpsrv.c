#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	// 1.Create a TCP socket
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	// 2.Bind server’s well-known port to socket
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	// Specify the IP address as INADDR_ANY, which allows the server to accept a client connection on any interface
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);	/* daytime server */

	// 3.Convert socket to listening socket
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	// LISTENQ specifies the maximum number of client connections
	Listen(listenfd, LISTENQ);

	// 4.Accept client connection, send reply
	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

		// 5.Terminate connection
		Close(connfd);
	}
}
