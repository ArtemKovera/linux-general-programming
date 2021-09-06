#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

#define PORT_CLIENT 5000
#define PORT_SERVER 5001
#define BUFF_LEN    512

char buf[BUFF_LEN];

int main()
{   
    int mySocket, i, bytes, status;
    unsigned int size;
    struct sockaddr_in addr_server;
    struct sockaddr_in addr_from;
    struct sockaddr_in addr_client;

    struct hostent *hostinfo;
    
    hostinfo = gethostbyname("127.0.0.1");
    if(hostinfo == NULL)
    {
        fprintf(stderr, "Unknown address\n");
        exit(EXIT_FAILURE);
    }
    
    //server
    addr_server.sin_family        = hostinfo->h_addrtype;
    addr_server.sin_addr          = *(struct in_addr*) hostinfo->h_addr;
    addr_server.sin_port          = htons(PORT_SERVER);
    
    //client
    addr_client.sin_family        = AF_INET;
    addr_client.sin_addr.s_addr   = INADDR_ANY;
    addr_client.sin_port          = htons(PORT_CLIENT); 

    //UDP socket
    mySocket = socket(PF_INET, SOCK_DGRAM, 0);
    if(mySocket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    status = bind(mySocket, (struct sockaddr*)&addr_client, sizeof(addr_client));
    if(status < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    

    //reading a line from stdin
    printf("Please enter your message: \n");
    fgets(buf, BUFF_LEN, stdin);
    size = BUFF_LEN + 1; 
   
    //sending the message to the server
    bytes = sendto(mySocket, buf, size, 0, (struct sockaddr*)&addr_server, sizeof(addr_server));
    if(bytes < 0)
    {
        perror("sendto");
        close(mySocket);
        exit(EXIT_FAILURE);
    }
    
    printf("Sending a message of %d bytes to the server is done\n", bytes);
    
    //getting a new message from the server
    bytes = recvfrom(mySocket, buf, BUFF_LEN, 0, (struct sockaddr*)&addr_from, &size);

    printf("The message from the server: \n%s\n", buf);

    close(mySocket);

    return 0;
}