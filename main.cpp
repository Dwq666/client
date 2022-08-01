#include <iostream>
#include <stdio.h>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../nanomsg/src/pair.h"
#include "../nanomsg/src/bus.h"
#include "../nanomsg/src/nn.h"
using namespace std;

#define cLen 100 

int main()
{
     char* lUrl = "tcp://172.18.30.239:8888";
     int client_sock=0;
     char buf[cLen] = {0};


     if (client_sock = nn_socket (AF_SP, NN_PAIR) < 0)
     {  
        cout<<"create server socket failed!"<<endl;
        return -1;

     }
    
    if(nn_connect(client_sock,lUrl)<0)
    {   
        cout<<"connect server sock failed!"<<endl;
        nn_close(client_sock);
		return -1;
    }

    cout<<"client init success!"<<endl;

    while (1)
    {
        cin>>("%s",buf);
        if(nn_send(client_sock, buf, sizeof(buf), 0) < 0)
		{
			cout<<"send failed!"<<endl;
			nn_close(client_sock);
		}
        memset(buf, 0, cLen);     

        if (nn_recv(client_sock, buf, sizeof(buf), 0) > 0) 
		{
			//cout<<("recieve server msg: %s", buf)<<endl;
            cout<<"recieve server msg:"<< buf <<endl;
		}
        memset(buf, 0, cLen);

    }
    nn_close(client_sock);
    return 0;

}