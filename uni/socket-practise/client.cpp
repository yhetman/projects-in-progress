#include <iostream>
#include <string>
#include <array>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

SOCKET createSocket(string ipAddress)
{  // IP ADRESS of the server
	int port = 1031;// listening port # on the server
	WSAData data; // initialize winsock
	WORD ver = MAKEWORD(2, 2); 
	int wsResult = WSAStartup(ver, &data);
	if (wsResult)
		cerr << "can't start Winsock, err # " << wsResult << endl;
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // create socket
	if (sock == INVALID_SOCKET)
		cerr << "can't create a socket, err # " << WSAGetLastError() << endl;
	sockaddr_in hint;
	hint.sin_family = AF_INET; // TCP/IP
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "can't connect to a server, Err # " << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
	}
	return (sock);
}


int main()
{
	string user;
	const size_t length = 25;
	cout << "Enter IP server:\n";
	cin >> user;
	SOCKET client;
	try
		client = createSocket(user);
	catch (const std::exception & e)
	{
		cout << e.what() << endl;
		system("pause");
		return false;
	}
	int sendResult, bytesReceived;
	char buf[500000];
	while (true)
	{
		ZeroMemory(buf, 500000);
		user.clear();
		cout << '>';
		cin >> user;
		if (user.c_str() != "who" || user[0] == 'g') {}
		else
		{
			cout << "Uncorrect command\n";
			continue;
		}
		sendResult = send(client, user.c_str(), user.length(), 0);
		if (sendResult != SOCKET_ERROR)
		{
			bytesReceived = recv(client, buf, 500000, 0);
			user.clear();
			user = buf;
		}
		cout << "Server: " << user << '\n';
	}
	system("pause");
}