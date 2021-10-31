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
#include<sys/select.h>
#include<fcntl.h>



#define PORT "5050"
#define MAX_CLIENTS 256
#define NAME_SIZE 64

void makeNonblocking(int fd)
{
    int oldFlags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, oldFlags | O_NONBLOCK);
}

typedef struct 
{
    int fd;
    char name[NAME_SIZE];
}Client;

void add_client(Client * clients, int socket) // const char * clientName)
{
    if(socket > MAX_CLIENTS)
        return;

    clients[socket].fd = socket;
    
    /*
    int i = 0;

    while(clientName[i] != '\0' && i < 63)
    {
       clients[socket].name[i] = clientName[i];
       i++;
    }

    clientName[i] == '\0'; 
    */
    
}

void remove_client(Client * clients, int socket)
{
    if(socket > MAX_CLIENTS)
        return;
    
    clients[socket].fd = 0;
}

void send_to_all_clients(Client * clients, const char * message, size_t messageSize)
{
    int status; 
    for(int i = 4; i < MAX_CLIENTS; ++i)
    {
        if(clients[i].fd != 0)
        {   
            status = send(i, message, messageSize, MSG_NOSIGNAL);
            if(status == -1)
            {
                perror("send()");
                exit(-1);
            }
        }
    }
}

int main()
{
    Client clients[MAX_CLIENTS];

    int clientCount = 0;

    const char * message = "MESSAGE TO CLIENTS";

    memset(&clients, 0, sizeof(clients));

    int masterSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(masterSocket == -1)
    {
        perror("socket()");
        exit(-1);
    }

    struct addrinfo hints;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bindAddress;

    getaddrinfo(0, PORT, &hints, &bindAddress);

    int status = bind(masterSocket, bindAddress->ai_addr, bindAddress->ai_addrlen);
    if(status == -1)
    {
        perror("bind()");
        exit(-1);
    }

    makeNonblocking(masterSocket);

    listen(masterSocket, SOMAXCONN);
    
    int selectStatus;
    int maxElement = MAX_CLIENTS + 1;
    char buffer[NAME_SIZE];
    char choise;
    
    while(1)
    {
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(masterSocket, &reads);

        for(int i = 3; i < MAX_CLIENTS; ++i)
        {
            FD_SET(i, &reads);
        }

        selectStatus = select(maxElement, &reads, NULL, NULL, NULL);
        
        for(int i = 3; i < MAX_CLIENTS; ++i)
        {
            if(FD_ISSET(i, &reads))
            {
                int recvSize = recv(i, buffer, BUFSIZ, MSG_NOSIGNAL);

                if((recvSize == 0) && (errno != EAGAIN)) 
                {
                    shutdown(i, SHUT_RDWR);
                    close(i);
                    remove_client(clients, i);
                    clientCount--;
                }

                if(recvSize != 0)
                {
                    send(i, buffer, BUFSIZ, MSG_NOSIGNAL);
                }
            }
        }

        if(FD_ISSET(masterSocket, &reads))
        {
            struct sockaddr_storage client_address;
            socklen_t client_len = sizeof(client_address);
            int clientSock = accept(masterSocket, (struct sockaddr*) &client_address, &client_len);
            if(clientSock == -1)
            {
                perror("accept()");
                exit(-1);
            }
            makeNonblocking(clientSock);   
            add_client(clients, clientSock);
            clientCount++;
        }
        
        /*
        puts("To send message to all clients press 's' (Any other symbol if not)");
        
        choise = getchar();

        if(choise == 's')
            send_to_all_clients(clients, message, sizeof(message));
        */
    }

    return 0;
}