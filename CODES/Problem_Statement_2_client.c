#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define PORT 15050
#define IP "127.0.0.1"
#define PROTOCOL 0
#define encrypt_char 'A'
#define SIZE 32

char decrypt(char c)
{
    return c^encrypt_char ;
}

int recv_UDP_decrypt(char* buffer, int s)
{
    char c;
    for(int i=0;i<s;i++)
    {
        c = buffer[i]; 
        c = decrypt(c);
        if(c==EOF)
            return 1;
        else
        {
            printf("%c",c);
        }
        
    }
    printf("\n");
    return 0;
}

int main()
{
    int socket1, rec ;
    char buffer[32] ;
    FILE* file_pointer ;

    struct sockaddr_in address ;
    int addr_len = sizeof(address) ;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr(IP) ;

    socket1 = socket(AF_INET, SOCK_DGRAM, PROTOCOL) ;

    if(socket1 < 0)
    {
        printf("Error Creating Socket\n");
    }

    while(1)
    {
        printf("Enter file name to receive :  ");
        scanf("%s", buffer); 
        printf("\n");

        sendto(socket1, buffer, 32, 0, (struct sockaddr*)&address, addr_len) ;
        
        printf("\n-------DATA-------\n\n\n");
        

        while(1)
        {
             for(int i=0;i<32;i++)
            {
                buffer[i]='\0';
            }

            rec = recvfrom(socket1, buffer, 32, 0, (struct sockaddr*)&address, &addr_len) ;

            if(recv_UDP_decrypt(buffer, 32))
            {
                break;
            }

        }

        printf("\n\n\n--------END-------\n"); 

    }

    return 0;
}