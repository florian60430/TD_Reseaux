#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <string>


#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

using namespace std;

int main() 
{

int sock = socket(AF_INET, SOCK_STREAM, 0); 
if (sock == -1)
{
	return 1;
}

int port = 2528;
string ipAddress = "192.168.64.189";

sockaddr_in hint;
hint.sin_family = AF_INET;
hint.sin_port = htons(port);
inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
if (connectRes == -1)
{
	return 1;
}

char buf[4096];
string userInput;

do {

	cout << "> ";
	getline(cin, userInput);

	int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	if (sendRes == -1)
	{
		cout << "Could not send to server! Whoops!\r\n";
		continue;
	}

	memset(buf, 0, 4096);
	int bytesReceived = recv(sock, buf, 4096, 0);
	if (bytesReceived == -1)
		{

			cout << "error getting response from server\r\n";
		}

		else 

		{

			cout << "SERVER : " << string(buf, bytesReceived) << "\r\n";
		}

} while(true);

close(sock);

return 0;

}

