#include <iostream>
#include <winsock2.h>

// Ye line WinMain ka error khatam karne ke liye hai
#define WinMain main 

// Library link karne ka tareeqa
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    // 1. Initialize Winsock
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in client;
    int start_port, end_port;
    string target_ip;

    cout << "=====================================" << endl;
    cout << "   WASIF-SCAN: Security Tool v1.0    " << endl;
    cout << "=====================================" << endl;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cout << "Failed. Error Code : " << WSAGetLastError();
        return 1;
    }

    // 2. User Input
    cout << "Enter Target IP: ";
    cin >> target_ip;
    cout << "Enter Start Port (e.g. 70): ";
    cin >> start_port;
    cout << "Enter End Port (e.g. 90): ";
    cin >> end_port;

    cout << "\nScanning " << target_ip << "...\n" << endl;

    // 3. Scanning Loop
    for(int port = start_port; port <= end_port; port++) {
        // Create Socket
        s = socket(AF_INET , SOCK_STREAM , 0);
        
        client.sin_addr.s_addr = inet_addr(target_ip.c_str());
        client.sin_family = AF_INET;
        client.sin_port = htons(port);

        // Connect karke check karna (TCP Handshake)
        if (connect(s , (struct sockaddr *)&client , sizeof(client)) == 0) {
            cout << "[+] Port " << port << " : OPEN" << endl;
        } else {
            // Port closed hai, kuch print karne ki zaroorat nahi
        }

        closesocket(s); // Socket band karna zaroori hai
    }

    WSACleanup();
    cout << "\nScan Complete. Press any key to exit.";
    cin.ignore();
    cin.get();
    
    return 0;
}