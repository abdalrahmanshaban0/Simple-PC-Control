#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(){
    char IP[15];
    int PORT;

    printf("Enter IP and Port number for the server:\n");
    scanf("%s%d", IP, &PORT);

    //Creat TCP/IPv4 Socket
    int FD = socket(AF_INET, SOCK_STREAM, 0);

    //Creat Socket address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &address.sin_addr.s_addr);

    //connection to server
    int ResConnect = connect(FD, (struct sockaddr*)&address, sizeof(address));

    //check error
    if(~ResConnect) 
        printf("Connection established\n");
    else{
        printf("Connection error\n");
        return -1;
    }

    char* Message = NULL;
    size_t Msize = 0;
    printf("Type your messages and we'll send :)\n");

    while(true){
        size_t sz = getline(&Message, &Msize, stdin);
        if(sz > 1){
            send(FD, Message, sz, 0);
        }
    }

    close(FD);

    return 0;
}
