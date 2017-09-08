#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <getopt.h>
#include <libgen.h>
#include "EdpKit.h"
#include "Common.h"
#define   DEVICEID   "9792779"
#define   APIKEY     "IlDVXSJ9p80H=8Fflp7R=joc89A="
#define   IP   "jjfaedp.hedevice.com"
#define   PORT     "876"
#define ERR_CREATE_SOCKET   -1 
#define ERR_HOSTBYNAME      -2 
#define ERR_CONNECT         -3 
#define ERR_SEND            -4
#define ERR_TIMEOUT         -5
#define ERR_RECV            -6
static int g_is_encrypt = 0;
EdpPacket* send_pkg;
char send_buf[300];
 int sockfd,ret;
void hexdump(const unsigned char *buf, uint32 num)
{
    uint32 i = 0;
    for (; i < num; i++) 
    {
        printf("%02X ", buf[i]);
        if ((i+1)%8 == 0) 
            printf("\n");
    }
    printf("\n");
}

int32 Open(const uint8 *addr, int16 portno)
{
    int32 sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* ´´½¨socketÌ×½Ó×Ö */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "ERROR opening socket\n");
        return ERR_CREATE_SOCKET; 
    }
    server = gethostbyname(addr);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        return ERR_HOSTBYNAME;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        fprintf(stderr, "ERROR connecting\n");
        return ERR_CONNECT;
    }
    return sockfd;
}

int32 DoSend(int32 sockfd, const char* buffer, uint32 len)
{
    int32 total  = 0;
    int32 n = 0;
    while (len != total)
    {
        n = send(sockfd,buffer + total,len - total,MSG_NOSIGNAL);
        if (n <= 0)
        {
            fprintf(stderr, "ERROR writing to socket\n");
            return n;
        }
        total += n;
    }
    hexdump((const unsigned char *)buffer, len);
    return total;
}

void send_data()
{  
    char text[25] = {"2"};
    memset(send_buf,0,300);	
    strcat(send_buf, ",;");
    strcat(send_buf, "dianya,");
    strcat(send_buf, text);
    strcat(send_buf, ";");
    send_pkg = PacketSavedataSimpleString(DEVICEID, send_buf, 0);
    DoSend(sockfd, (const char*)send_pkg->_data, send_pkg->_write_pos);
    DeleteBuffer(&send_pkg);
}
void rec()
{

    int n=0;
    char* cmdid;
    uint16 cmdid_len;
    char*  cmd_req;
    uint32 cmd_req_len;
     EdpPacket* send_pkg;
     RecvBuffer* recv_buf = NewBuffer();
     EdpPacket* pkg;
     uint8 mtype;
     char buffer[1024]={"2"};
     n = recv(sockfd, buffer, 1024, MSG_NOSIGNAL);
     hexdump((const unsigned char *)buffer, n);
     WriteBytes(recv_buf, buffer, n);
     pkg = GetEdpPacket(recv_buf);
     mtype = EdpPacketType(pkg);
     if(mtype==CMDREQ)
      {              
            UnpackCmdReq(pkg, &cmdid, &cmdid_len,&cmd_req, &cmd_req_len);
            printf("rec is %s\n",cmd_req);
            free(cmdid); 
            free(cmd_req);
            DeleteBuffer(&pkg);
            DeleteBuffer(&recv_buf);
      }
}
void main()
{
     sockfd = Open((const uint8*)IP, atoi(PORT));
     send_pkg = PacketConnect1(DEVICEID, APIKEY);
     printf("send connect to server, bytes: %d\n", send_pkg->_write_pos);
     ret=DoSend(sockfd, (const char*)send_pkg->_data, send_pkg->_write_pos);
     DeleteBuffer(&send_pkg);
     send_data();	
     while(1)
     {
          rec();
          sleep(1);   
     }
     Close(sockfd); 	   
}


