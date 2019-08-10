#include<stdio.h> 
#include<string.h> 
  

char NetworkClass(char ipv4_addr[])
{

    int i = 0;
    while (ipv4_addr[i] != '.')
    {
        i++;
    }
    i--; 

    int ipv4_octet_1= 0, k= 1; 
    while (i >= 0) 
    { 
        ipv4_octet_1=ipv4_octet_1+(ipv4_addr[i]-'0')*k; 
        k=k*10;
        i--; 
    } 
  

    if (ipv4_octet_1>=1 && ipv4_octet_1<= 126) 
        return 'A'; 
  
    else if (ipv4_octet_1>= 128 && ipv4_octet_1<= 191) 
        return 'B'; 
  
    else if (ipv4_octet_1>= 192 && ipv4_octet_1<= 223) 
        return 'C'; 
  
    else if (ipv4_octet_1>= 224 && ipv4_octet_1<= 239) 
        return 'D'; 
  
    else if(ipv4_octet_1>239)
        return 'E'; 

    return 'R' ;
} 
  
void HostandNetwork_ID_A(char ipv4_addr[])
{
     char network[12], host[12];
    for (int k = 0; k < 12; k++)
        network[k]=host[k]='\0';

    int i = 0, j = 0;
    while (ipv4_addr[j] != '.')
        network[i++] = ipv4_addr[j++];
    i = 0;
    j++;
    while (ipv4_addr[j] != '\0')
        host[i++] = ipv4_addr[j++];
    printf("Network ID is %s\n", network);
    printf("Host ID is %s\n", host);

}

void HostandNetwork_ID_B(char ipv4_addr[])
{
     char network[12], host[12];
    for (int k = 0; k < 12; k++)
        network[k]=host[k]='\0';

    int i = 0, j = 0, octect_no = 0;

    while (octect_no < 2)
    {
        network[i++] = ipv4_addr[j++];
        if(ipv4_addr[j] == '.')
            octect_no++;
    }
    i = 0;
    j++;

    while (ipv4_addr[j] != '\0')
        host[i++] = ipv4_addr[j++];

    printf("Network ID is %s\n", network);
    printf("Host ID is %s\n", host);
    
}

void HostandNetwork_ID_C(char ipv4_addr[])
{
     char network[12], host[12];
    for (int k = 0; k < 12; k++)
        network[k]=host[k]='\0';

    int i = 0, j = 0, octect_no = 0;

    while (octect_no < 3)
    {
        network[i++] = ipv4_addr[j++];
        if (ipv4_addr[j] == '.')
            octect_no++;
    }

    i = 0;
    j++;
  
    while (ipv4_addr[j] != '\0')
        host[i++] = ipv4_addr[j++];
  
    printf("Network ID is %s\n", network);
    printf("Host ID is %s\n", host);

}

void HostandNetwork_ID_D_E(char ipv4_addr[])
{
    printf("In this Class, No division into Network and Host ID\n");

}

int main() 
{
    printf("Enter the IP Address : ");
    char ipv4_addr[15] ; 
    scanf("%s",ipv4_addr);
    char network_class = NetworkClass(ipv4_addr); 

    printf("Given IP address belongs to Class %c\n", network_class);

    if(network_class=='A')
        HostandNetwork_ID_A(ipv4_addr);
    else if(network_class=='B')
        HostandNetwork_ID_B(ipv4_addr);
    else if(network_class=='C')
        HostandNetwork_ID_C(ipv4_addr);
    else if(network_class=='D'||network_class=='E')
        HostandNetwork_ID_D_E(ipv4_addr);
    else
        printf("Reserved IP Address\n");
    
    

    return 0; 
}