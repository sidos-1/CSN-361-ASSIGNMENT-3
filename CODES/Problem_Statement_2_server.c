#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define PORT 15050
#define PROTOCOL 0
#define encrypt_char 'A'
#define SIZE 32

char encrypt(char c)
{
    return c^encrypt_char ;
}

int send_UDP_encrypt(FILE* file_pointer, char* buffer, int s)
{
    int i,len;
    if(file_pointer == NULL)
    {
        strcpy(buffer, "File Not Found !!") ;
        len = strlen("File Not Found !!") ;
        buffer[len] = EOF ;
        for(i = 0;i<=len ;i++)
        {
            buffer[i]=encrypt(buffer[i]);
        }
        return 1;
    }

    char c,c1;
    for(i=0; i<s; i++)
    {
        c = fgetc(file_pointer);
        c1 = encrypt(c);
        buffer[i]=c1;
        if(c1==EOF)
            return 1;
    }
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
    address.sin_addr.s_addr = INADDR_ANY ;

    socket1 = socket(AF_INET, SOCK_DGRAM, PROTOCOL) ;

    if(socket1 < 0)
    {
        printf("Error Creating Socket\n");
    }

    if(bind(socket1, (struct sockaddr*)&address, sizeof(address))!=0)
    {
        printf("Binding Failed");
    }

    while(1)
    {
        printf("Waiting for file request \n ");

        for(int i=0;i<32;i++)
        {
            buffer[i]='\0';
        }

        rec = recvfrom(socket1, buffer, 32, 0, (struct sockaddr*)&address, &addr_len) ;
        
        printf("File Request for : %s \n ",buffer);

        file_pointer = fopen(buffer, "r");
        if(file_pointer == NULL)
        {
            printf("File Failure\n");
        }

        while(1)
        {
            if(send_UDP_encrypt(file_pointer ,buffer, 32))
            {
                sendto(socket1, buffer, 32, 0, (struct sockaddr*)&address, addr_len) ;
                break;
            }

            sendto(socket1, buffer, 32, 0, (struct sockaddr*)&address, addr_len) ;

            for(int i=0;i<32;i++)
            {
                buffer[i]='\0';
            }

        }

        // printf("File Request Fulfilled\n ");

        if(file_pointer != NULL)
        {
            fclose(file_pointer);
        }

    }

    return 0;
}