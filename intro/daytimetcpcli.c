#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	// 1.Create TCP socket
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	// 2.Specify server’s IP address and port
	// Set sockaddr_in structure to 0
	bzero(&servaddr, sizeof(servaddr));
	// Set the address family to AF_INET
	servaddr.sin_family = AF_INET;
	// Set the port number to 13, the function htons convert the binary port number. (host to network short)
	servaddr.sin_port   = htons(13);	/* daytime server */
	// The function inet_pton convert the ASCII command-line argument into the proper format. (presentation to numeric)
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	// 3.Establish connection with server
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	// 4.Read and display server’s reply
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");

	// 5.Terminate program
	exit(0);
}
