#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

using namespace std;

int main() 
{

SOCKET sock;
sock = socket(AF_INET, SOCK_DGRAM, 0);
SOCKADDR_IN InfoServer;

InfoServer.sin_addr.s_addr = htonl(INADDR_ANY);
InfoServer.sin_family = AF_INET;
InfoServer.sin_port = htons(2728);

printf("Listage du port %d... \n", 2728);

int error_message;

error_message = ::bind(sock, (SOCKADDR*)&InfoServer, sizeof(InfoServer));

char buffer[1500];
memset (buffer, '\0', 1500);
sockaddr_in _from;
socklen_t fromlen = sizeof(_from);

uint8_t _SizepacketBuff = 0;
ioctl (sock, FIONREAD, &_SizepacketBuff);

cout << "taille du buffer : " << _SizepacketBuff << endl;
do
    {
	error_message = recvfrom(sock, buffer, 1500, 0, reinterpret_cast<sockaddr*>(&_from), &fromlen);
	if (error_message<1)
	 {
		fprintf(stderr, "socket() message: %s\n", strerror(errno));

	 }

	 else

	 {
		printf(" IP : %s ", inet_ntoa(_from.sin_addr));
		printf(" PORT : %d", ntohs(_from.sin_port));
		printf("Reçu : %s ", buffer);
	 }
    }while(_SizepacketBuff <=  0);


}
