
/* Sample UDP server */


#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>

// fork and wait
#include <unistd.h>
#include <sys/wait.h>

// exit
#include <stdlib.h>

// kqueue / kevent 

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

// bzero
#include <strings.h>

// printf
#include <stdio.h>

#define CHILDREN 32
#define PORTNUMBER 32000

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr;	
	int kq;
	struct kevent evSet;
	struct kevent evList[32];
	int nev, i,x, status;
	int lowwater = 1000;
	pid_t pid;
	pid_t childpid[CHILDREN];
	
	socklen_t len;
	char mesg[1400];	
	
	// Open UDP datagram socket
	// Pretty Standard Socket binding code

	sockfd=socket(AF_INET,SOCK_DGRAM,0);	
	bzero(&servaddr,sizeof(servaddr));	
	
	setsockopt(sockfd, SOL_SOCKET, SO_RCVLOWAT, &lowwater, sizeof(lowwater));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORTNUMBER);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	
	// Prefork the children 
	
	for (x=0; x<CHILDREN; x++) {
		childpid[x] = fork();
	
	
		if (childpid[x] == 0) { 
			// In Child
			kq = kqueue();
			pid = getpid();			
			printf ("[%d] Child %d Forked\n", pid, x );
			
			// Setup the Kevent Event.
			EV_SET(&evSet, sockfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
			if (kevent(kq, &evSet, 1, NULL, 0, NULL) == -1)  {
				printf("erorr kevent\n");
				exit(1);
			}

			for (;;){
				len = sizeof(cliaddr);
				// Wait for the 
				nev = kevent(kq, NULL, 0, evList, 32, NULL);
				if (nev < 1) { 
					printf("error kevent\n");
				} else {
								
					for (i=0; i<nev; i++) { 
						if (evList[i].ident == sockfd) {      
							n = recvfrom(sockfd,mesg,1400,0,(struct sockaddr *)&cliaddr,&len);						
						} else {
							printf ("[%d] Not the socket id.\n", pid);    	
						}
					}
				
			}
			
		} 
		
		exit(0);
	}
} 


	printf("PARENT PID: %d\n", getpid());
	for (x=0; x<32; x++) { 	
		printf("[%d] Waiting for Child PID: %d\n", getpid(), childpid[x]);
		waitpid(childpid[x], &status, 0 ); 
	}
		
}