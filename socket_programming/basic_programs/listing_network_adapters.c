/*
    Listing network adapters

    This program is analogous to one example from the book
    "Hands-On Network Programming with C" by Lewis Van Winkle 
*/
#include<sys/socket.h>
#include<netdb.h>
#include<ifaddrs.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    struct ifaddrs *addresses;

    if (getifaddrs(&addresses) == -1)
    {
        fprintf(stderr, "getifaddrs call failed\n");
        exit(EXIT_FAILURE);
    }

    struct ifaddrs *address = addresses;
    
    //walking through all the addresses
    while(address)
    {
        int family = address->ifa_addr->sa_family;

        if(family == AF_INET6 || family == AF_INET)
        {
            printf("%s\t", address->ifa_name);
            printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");

            char ap[100];
            const int family_size = family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            getnameinfo(address->ifa_addr, family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
            printf("\t%s\n", ap);
        }

        address = address->ifa_next;
    }

    freeifaddrs(addresses);
    return 0;
}