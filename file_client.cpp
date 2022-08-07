#include "file_client.h"

f_client::f_client(char * aip,int aport)
{   
    ip_addr = aip;
    port_addr = aport;
}
f_client::~f_client()
{

}

void f_client::start()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
	addr.sin_port = htons(port_addr);
	addr.sin_addr.S_un.S_addr = inet_addr(ip_addr);
 
	connect(sock, (sockaddr*)&addr, sizeof(addr));

    char * buf = new char[1024];
    while(1)
    {
        cin>>("%s",buf);
        SendData(buf,sizeof(buf));
        memset(buf, 0, 1024);   
    }
	
}


void f_client::SendFile(const char * aFileName)
{
    FILE * fp = fopen(aFileName, "rb");
    fseek(fp, 0, SEEK_END);
    int lsize=ftell(fp); 
    fseek(fp, 0, SEEK_SET);
    char * buffer = new char[lsize];  
    fread(buffer,lsize,1, fp);
    SendData(buffer,lsize);
    delete[] buffer;
}

void f_client::SendData(const char * aData ,int aSize)
{
    send(sock,(char *)&aSize,sizeof(aSize),0);

    int lIndex=0;
    while(lIndex <aSize)
    {
        int  lret= send(sock,aData+ lIndex,1024,0);
        lIndex += lret;
    }
  
}