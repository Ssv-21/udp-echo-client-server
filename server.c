#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXLINE 1024
#define PORT 8200
int main(int argc, char **argv)
{
   int sockfd;
   int n, i;
   socklen_t len;
   char msg[1024];
   struct sockaddr_in servaddr, cliaddr;
   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = INADDR_ANY;
   servaddr.sin_port = htons(PORT);
   printf("\n Server Binded..");
   bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
   printf("\n\n Listening for clients..");
   for (i = 0; i < 1; i++)
   {
      printf("\n ");
      len = sizeof(cliaddr);
      n = recvfrom(sockfd, msg, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
      printf("\n Client's Message : %s\n\n", msg);
      if (n < 6)
      {
         perror("send error");
      }
      sendto(sockfd, msg, n, 0, (struct sockaddr *)&cliaddr, len);
   }
   return 0;
}
