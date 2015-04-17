#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "hacking.h"
#include "hacking-network.h"

int main(int argc, char *argv[]) {
	int sockfd;
	struct hostent *host_info;
	struct sockaddr_in target_addr;
	unsigned char buffer[4096];
	
	if(argc < 2) {
		printf("Usage: %s <hostname>\n", argv[0]);
		exit(1);
	}

	if((host_info = gethostbyname(argv[1])) == NULL)
		fatal("looking up hostname");

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		fatal("in socket");

	target_addr.sin_family = AF_INET;
	target_addr.sin_port = htons(7800);	
	target_addr.sin_addr = *((struct in_addr *)host_info->h_addr);
	memset(&(target_addr.sin_zero), '\0', 8); // zero the rest of the struct

	if (connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
		fatal("connecting to target server");
	//send_string(sockfd, "HEAD / HTTP/1.0\r\n\r\n");
	send_string(sockfd, "GET /audio.ram HTTP/1.1\r\n");
	
	while(recv(sockfd, buffer,1,0)) {
	printf("%s", buffer);
	//exit(0);		
	}
	printf("Server line not found\n");
	exit(1);
}
