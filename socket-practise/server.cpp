#include <iostream>
#include <time.h>
#include <array>
#include "WS2tcpip.h"
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

SOCKET createSocket()
{
	WSADATA wsData;
	WORD ver = (2, 2);
	int winSock;
	SOCKET server;

	winSock = WSAStartup(ver, &wsData);
	if (winSock)
		throw exception("Can't initialaze winsock!");
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
		throw exception("Can't create a socket!");
	sockaddr_in hint; 
	hint.sin_family = AF_INET; 
	string ipAddress = "10.1.4.185"; //can be different
	hint.sin_port = htons(1031);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(server, (sockaddr*)&hint, sizeof(hint));
	return (server);
}

char * wtoc(const wchar_t* w)
{
	size_t length;
	size_t size = wcslen(w);
    char * mass = new char[size];
	wcstombs_s(&length,mass,size+2,w,size+1);
	return (mass);
}

vector<string> rewrite(string & data)
{
	string in;
	vector<string> sort;
	int j = 0;

	for (size_t i = 0; i < data.length(); i++)
	{
		in[i] = data[i];
		if (data[i] = '\n')
		{
			sort.at(j) = in;
			in.clear();
			j++;
		}
	}
	return (sort);
}

string checkIt(string & data)
{
	const string who = "who";
	const string get = "get";
	string returnRes;
	string check;

	for (size_t i = 0; i < 3; i++)
		check.push_back(data[i]);
	if (data.size() > 4)
	{
		string refresh = data;
		data.clear();
		for (size_t i = 3; i < refresh.size(); i++)
			data.push_back(refresh[i]);
	}
	if (who == check)
		return ("Created by Yuliia Hetman\n");
	if (check == get)
	{
		bool empty = false;
		WIN32_FIND_DATAW wfd;
		char * buf;
		HANDLE const hFind = FindFirstFileW(L"C:\\*", &wfd);
		if (INVALID_HANDLE_VALUE != hFind)
		{
			do {
				buf = wtoc(&wfd.cFileName[0]);
				returnRes += buf;
				returnRes += '\n';
			} while (NULL != FindNextFileW(hFind, &wfd));
			FindClose(hFind);
		}
		if (!data.empty())
		{
			data.clear();
			data = returnRes;
			return (data);
		}
		else
		{
			string sort;
			vector<string> in;
			for (size_t i = 0; i < data.length(); i++)
			{
				if (data[i] != ' ')
				{
					for (; data[i] != '\n'; i++)
						sort.push_back(data[i]);
				}
			}
			in = rewrite(returnRes);
			data.clear();
			string line;
			for (size_t i = 0; i < in.size(); i++)
			{
				line = in.at(i);
				if (line.find_first_of(sort))
					data += line;
				line.clear();
			}
		}
	}
	return (data);
}

int main()
{
	ofstream history("history.txt");
	SOCKET server;
	try
		server = createSocket();
	catch (exception & e)
	{
		cout << e.what() << endl;
		return (0);
	}
	listen(server, SOMAXCONN);
	cout << "Listening...\n";
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSock = accept(server, (sockaddr*)&client, &clientSize);
	cout << "Client created\n";
	const size_t length = 1000;
	char host[length];
	inet_ntop(AF_INET, &client.sin_addr, host, length);
	cout << host << " connect on port " << ntohs(client.sin_port) << endl;
	char buf[500];
	string data;
	int bytesReceived;
	while (true)
	{
		ZeroMemory(buf, 500);
		bytesReceived = recv(clientSock, buf, 500, 0);
		data = buf;
		history << host  << data << '\n';
		data = checkIt(data);
		send(clientSock, data.c_str(), data.length(), 0);
	}
	system("pause");
	closesocket(server);
	closesocket(clientSock);
	history.close();
	WSACleanup();
}