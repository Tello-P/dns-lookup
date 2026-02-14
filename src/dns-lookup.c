#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
  if (argc != 2){
    printf("Usage: dns <hostname>");
    return 1;}

  printf("Starting DNS Lookup for %s...\n", argv[1]);
  // man getaddrinfo
  struct addrinfo *presult;
  char *node = argv[1];
  char *service = NULL;
  struct addrinfo hints;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = 0; /* Datagram socket */
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;




  int result = getaddrinfo(node, service, &hints, &presult);
  printf("%d\n", result);
  printf("DNS LOOKUP para %s\n", node);
  for (struct addrinfo *rp = presult; rp != NULL; rp = rp->ai_next){
    printf("%s\n", rp->ai_family == AF_INET ? "IPv4" : "IPv6");
    

  char ipstr[INET6_ADDRSTRLEN];

    void *src = rp->ai_family == AF_INET ? (void *) &((struct sockaddr_in *)
      rp->ai_addr)->sin_addr : (void *)  &((struct sockaddr_in6 *) 
      rp->ai_addr)->sin6_addr;
    

    inet_ntop(rp->ai_addr->sa_family, src, ipstr, sizeof(ipstr));
    printf("\tAddress: %s\n", ipstr);

    char *protocol = malloc(sizeof(char)*10);
    switch (rp->ai_protocol) {
      case 0: protocol= "IP";break;
      case 1: protocol = "ICMP";break;
      case 6: protocol = "TCP";break;
      case 17: protocol = "UDP";break;
      default: sprintf(protocol, "%d",rp->ai_protocol);
      break;
    }
    printf("\tService: %s\n", protocol);
    
  }
  freeaddrinfo(presult);

  return 0;
}
