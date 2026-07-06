#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iomanip>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

const char* XG_IP = "192.168.0.10";
const int XG_PORT = 8500;

std::string formatParam(double val) {
	std::stringstream ss;
	ss << val << std::setprecision(3);
	if (val > 0) ss << "+";
	ss << std::setfill('0') << std::setw(11) << val;
	return ss.str();
}

void sendXGCommand(int commandId, double p1 = 0.0, double p2 = 0.0, double p3 = 0.0) {
	WSADATA wsaData;
	SOCKET sock = INVALID_SOCKET;
	char recvbuf[1024];
	int recvlen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "WSAStartup failed." << std::endl;
		return;
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cout << "Socket creation failed." << std::endl;
		WSACleanup();
		return;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(XG_PORT);
	inet_pton(AF_INET, XG_IP, &serverAddr.sin_addr);

	std::cout << "Connecting to " << XG_IP << "..." << std::endl;
	if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		std::cout << "Connection failed. Error: " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	std::string cmd = "CC, " + std::to_string(commandId) +  + "\r";
	std::cout << "Sending: " << cmd;

	send(sock, cmd.c_str(), (int)cmd.length(), 0);

	recvlen = recv(sock, recvbuf, 1024, 0);
	if (recvlen > 0) {
		recvbuf[recvlen] = '\0';
		std::cout << "XG Response (Ack): " << recvbuf << std::endl;
	}

	recvlen = recv(sock, recvbuf, 1024, 0);
	if (recvlen > 0) {
		recvbuf[recvlen] = '\0';
		std::cout << "XG Response (Data): " << recvbuf << std::endl;
	}

	closesocket(sock);
	WSACleanup();
}

int main() {
	std::cout << "=== XG_Comm_Tester Start ==="<<std::endl;
	std::cout << "\n--- Testing Pipeline Trigger (CC, 15) ---" << std::endl;
	sendXGCommand(15);
	std::cout << "\n--- Testing Alignment (CC, 2) ---" << std::endl;
	sendXGCommand(2, 100.5, 200.1, 0.0);
	std::cout << "\nTest Finished. Press Enter to exit...";
	std::cin.get();
	return 0;
}