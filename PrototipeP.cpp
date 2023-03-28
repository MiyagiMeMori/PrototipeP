#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#pragma comment(lib, "ws2_32.lib")

std::string rtrim(const std::string& s) {
	const std::string trash = "\n\0";
	std::string retStr;
	//auto it = find_first_of(s.begin(), s.end(), trash.begin(), trash.end());
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] != '\n') {
			retStr.push_back(s[i]);
		}
		else {
			return retStr;
		}
	}
	return retStr;
}

int main() {
	//Key constants
	const char SERVER_IP[] = "127.0.0.1";					// Enter IPv4 address of Server
	const short SERVER_PORT_NUM = 1234;				// Enter Listening port on Server side
	const short BUFF_SIZE = 1024;					// Maximum size of buffer for exchange info between server and client

	// Key variables for all program
	int erStat;										// For checking errors in sockets functions

	//IP in string format to numeric format for socket functions. Data is in "ip_to_num"
	in_addr ip_to_num;
	inet_pton(AF_INET, SERVER_IP, &ip_to_num);


	// WinSock initialization
	WSADATA wsData;
	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		std::cout << "Error WinSock version initializaion #";
		std::cout << WSAGetLastError();
		return 1;
	}
	else
		std::cout << "WinSock initialization is OK" << std::endl;

	// Socket initialization
	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		std::cout << "Error initialization socket # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
	}
	else
		std::cout << "Client socket initialization is OK" << std::endl;

	// Establishing a connection to Server
	sockaddr_in servInfo;

	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(SERVER_PORT_NUM);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

	if (erStat != 0) {
		std::cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
		return 1;
	}
	else
		std::cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << std::endl;


	//Exchange text data between Server and Client. Disconnection if a Client send "xxx"

	std::vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);							// Buffers for sending and receiving data
	
	//std::string strServBuff;
	//strServBuff.resize(BUFF_SIZE);
	char strServBuff[BUFF_SIZE];

	short packet_size = 0;												// The size of sending / receiving packet in bytes

	while (true) {
		std::cout << "Your (Client) message to Server: ";
		fgets(clientBuff.data(), clientBuff.capacity(), stdin);

		packet_size = send(ClientSock, clientBuff.data(), clientBuff.size(), 0);
		//clientBuff.clear();

		if (packet_size == SOCKET_ERROR) {
			std::cout << "Can't send message to Server. Error # " << WSAGetLastError() << std::endl;
			closesocket(ClientSock);
			WSACleanup();
			return 1;
		}

		packet_size = recv(ClientSock, strServBuff, BUFF_SIZE, 0);

		if (packet_size == SOCKET_ERROR) {
			std::cout << "Can't receive message from Server. Error # " << WSAGetLastError() << std::endl;
			closesocket(ClientSock);
			WSACleanup();
			return 1;
		}
		else {
			strServBuff[packet_size] = 0;
			std::cout << "Server message: " << strServBuff << std::endl;
		}
	}

	closesocket(ClientSock);
	WSACleanup();

	return 0;
}
/*
Разработать программы сервера и клиента для передачи данных из сервера клиенту
мссп    
Сервер содержит данные по двум типам устройств: «Биометрический сканер» и «Датчик».

Устройство типа «Датчик» поддерживает метод запроса, текущего состояние по тревоге со значениями: «Да» или «Нет». Значение выбирается случайным образом.

Устройство «Биометрический сканер» поддерживает метод проверки биометрии. На входе - два массива байт: биометрические данные (9
байт) и биометрический эталон (9 байт), на выходе - результат проверки: true или false. Значение выбирается случайным образом.

Все типы устройств должны иметь: идентификатор (UUID), имя  (текстовая строка).

В сервере предусмотреть создание нескольких экземпляров указанных типов устройств.

Программа клиента должна по сети подключаться к серверу,  запрашивать данные по всем экземплярам устройств, выводить
информацию на экран о текущем перечне устройств, вызывать удаленные методы в зависимости от типа устройства и выводить результаты их выполнения на экран.
*/


