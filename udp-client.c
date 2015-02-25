
/* Sample UDP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

// exit
#include <stdlib.h>

// bzero
#include <strings.h>

// printf
#include <stdio.h>

// getpid

#include <sys/types.h>
#include <unistd.h>


#define PORTNUMBER 32000


int main(int argc, char**argv)
{
   int sockfd,c=0,pid;
   struct sockaddr_in servaddr;
   char sendline[1400];

   if (argc != 2)
   {
      printf("usage:  udp-client <IP address>\n");
      exit(1);
   }


   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(argv[1]);
   servaddr.sin_port=htons(PORTNUMBER);
   
   pid = getpid();

   while (1)
   {
   
   	c++;
   	
   	snprintf ( (char*)&sendline, sizeof(sendline), "+wys9i9fPAzx0MvRzwe0ZqoNv1fYoqjWbGFTNE97KfewSJXsrDnWb4GX/5NbCsSS7e/O6NptAR9e oKnX0cQvji4BoGNIkm1hQ3Ux3eb0jcy7zQkdVgSGwP691a9QWzSJpE96V4Klid1se32SPHfDmAZN leapTKjCeusG2ryGtJJtUh78gl12RAWKMYu7xmL4J41zR96HHsSEEE0o2xqS4rvK7fZP92nDWRrt LDGj9eRXVulOQxUbnKS/adC2/bwgu5PNPfnfW850UXeiSUyhl1COUpy6jdDKScSUA6mPlcGGNfUq c5FZbqT6Xi9iMQ5NLjf2Umrgjr3YCrshORqSZFz6PYm3LDESwf++dFWvjTTNI/1wrEW4WyHbKQI/ UbCT+yaznys5M+vyDGCnVz5rDLVjraFEgoSyLEt6xNUtyTTPNA9j6AUXAulxpc3C4gPAGCtG4fyg AqgwETJp5BkOURWxzcUTgkc48EhS9w4Nh9jM9bU8cugROeEBl3ttgZa/PWDI8OQndF45wckOjfKA Ws/6P3xqIes41MPABHzxTiCjW6xDT2qrOM1io4RlmNEhzVPPj7c1iwAH6PhqW4ByCOLkidFi9q3D S7MF0mALxzenjrzs764p8PkalLYkYvM8RoRMNSVJh3v2I525kZrRA/hvS5h9r+Cs5q1OiBQ5TXz3 hke6Q1lTiFyVOXBxQT31HqykLBj9xbEezUAP9kvgT/Jmd8L2Aswg3aqu1wInbu2K8mwOqC/djhn5 H7qtjGLZ1cphEIVauDoOTaq17ecHwWK8Rn8CdbMBBDT6OKX517g3oO/VdqimmPl0fu7VSKmqVnF3 UqKbdJ6Ytqsu1b5YHoujjPnRdd25wryDAv36WLUl76UyVFdChHzd12U1OwdNposwDUa+nzaYJTMa a2aqsPu3gXmC1oiu/una66EA4MpV078WU1RM2szXcBXWjoFXrNl/YqRIralWhuJjFI6IF5lvupzJ : %09d", c  );

	sendto(sockfd,sendline,sizeof(sendline),0,
		(struct sockaddr *)&servaddr,sizeof(servaddr));

	if ( (c % 1000000) == 0 ) {
		printf ( "[%d] Packets Sent: %d \n", pid, c );	
	}

   }
}

