#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

struct Modbus 
{
     UINT16 TransID; 
     UINT16 ProtocolID; 
     UINT8 Length; 
     UINT8 UnitID; 
     
     UINT8 FuncCode; 
     char Data[128]; 
};
struct GameSettings
{
	int GameMode;
	int SpeedOFTime;
};

int main(){
     //�������� ���������

     Modbus mod;
     mod.TransID = 0x00;
     mod.ProtocolID = 0x00;
     mod.UnitID = 0x00;
     mod.FuncCode = 0x00;   
     strcpy(mod.Data, "Error");   
     mod.Length = sizeof mod.Data;

     printf("GameSettings\n");
     GameSettings newData;

     mod.TransID = 0x00;
     mod.ProtocolID = 0x00;
     mod.UnitID = 0x03;       
     mod.FuncCode = 0x01;
        
     printf("Enter GameMode (1 - standart, 2 - reverse): ");
     scanf("%d", &newData.GameMode);
     newData.GameMode--; 

     printf("Enter Time Speed (Average = 300 mls): ");
     scanf("%d", &newData.SpeedOFTime);

     mod.Length = sizeof mod.Data;
     memcpy(&mod.Data[0],&newData,sizeof(newData));
               

     char mod_for_send[256]; // ������ ��� ��������
     memcpy(&mod_for_send[0],&mod,sizeof(mod));// �������� ��� ��������

         // �������������� DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData); //0000001000000010
         // ������� �����
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
         // ���������� ������ � �������
    sockaddr_in sockAddr;
         memset (& sockAddr, 0, sizeof (sockAddr)); // ������ ���� ����������� 0
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("192.168.50.58"); //127.0.0.1
    sockAddr.sin_port = htons(502);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    char szBuffer[MAXBYTE] = {0};
    send(sock, mod_for_send,sizeof(mod), NULL); // ��������
         
     

    recv(sock, szBuffer, MAXBYTE, NULL); // ���������
    memcpy(&mod,&szBuffer[0],256*sizeof(char)); // ��������� ������ � ���������


         // ������� ���������� ������
     printf("\n---------Return----------\n");
     printf("Message form server: %s\n", mod.Data);
     printf("------------------------\n");
         // ��������� �����
    closesocket(sock);
         // ���������� ������������� DLL
    WSACleanup();
    system("pause");
    return 0;
}

