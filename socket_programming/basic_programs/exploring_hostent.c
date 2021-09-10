#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct hostent *ht = gethostbyname(argv[1]);

    if(ht == NULL)
    {
        if(h_errno == HOST_NOT_FOUND)
            fprintf(stderr, "The specified host is unknown.\n");
        else if(h_errno == NO_DATA)
        {
            fprintf(stderr, "The  requested  name  is  valid but does not have an IP address.\n"
              "Another type of request to the name server for this  domain  may"
              "\nreturn  an  answer. The  constant  NO_ADDRESS is a synonym for NO_DATA.\n");
        }
        else if(h_errno == NO_RECOVERY)
        {
            fprintf(stderr, "A nonrecoverable name server error occurred.\n");
        }
        else if(h_errno == TRY_AGAIN)
        {
            fprintf(stderr, "A temporary error occurred on an authoritative name server. Try again later.\n");
        }

        exit(EXIT_FAILURE);
    }
    
    printf("\nThe official name of the host: %s\n\n", ht->h_name);

    
    char **alternativeName = ht->h_aliases;
    size_t i = 0;
    puts("The alternative names: ");
    while(alternativeName[i])
    {
        printf("%s", alternativeName[i]);
        i++;
    }
    if(!i)
        printf("NO alternative names\n\n");
    
    printf("Type: %s\n\n", (ht->h_addrtype == AF_INET) ? "IP4" : "IP6");
    
    printf("Length: %d bytes\n\n", ht->h_length);


    return 0;
}