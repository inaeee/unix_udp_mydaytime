udp_mydaytime.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>

#define MAXLINE 127

int main(int argc, char *argv[]){
        struct sockaddr_in servaddr;
        struct hostent *hp;
        int s,nbyte,addrlen=sizeof(servaddr);
        char buf[ MAXLINE+1 ];

        if(argc != 2){
                printf("Usage: %s ip_address\n", argv[0]);
                exit(0);
        }

        //소켓생성
        if((s=socket(PF_INET, SOCK_DGRAM, 0)) <0 ){
                perror("socket fail");
                exit(1);
        }

        //서버의 소켓주소 구조체 작성
        //servaddr의 주소지정
        servaddr.sin_family=AF_INET;
        hp = gethostbyname(argv[1]);
        bzero((char *)&servaddr, sizeof(servaddr));

        memcpy(&servaddr.sin_addr,hp->h_addr_list[0],sizeof(servaddr.sin_addr));
        servaddr.sin_port=htons(13);

        if(sendto(s,buf,strlen(buf),0,(struct sockaddr *)&servaddr, addrlen) <0){
                perror("sendto fail");
                exit(0);
        }

        if((nbyte=recvfrom(s,buf,MAXLINE,0,(struct sockaddr *)&servaddr, &addrlen)) <0){
                perror("recevfrom fail");
                exit(0);
        }

        buf[nbyte]=0;
        printf("%s", buf);
        close(s);
        return 0;
}
