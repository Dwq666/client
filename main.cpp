#include "nanomsg_client.h"
#include "file_client.h"


int main()
{   
    WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
    f_client * lclient = new f_client("172.27.65.154",8888);
    lclient->start();
    

    return 0;
}