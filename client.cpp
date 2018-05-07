#include <iostream>
#include <cstdlib>
#include <vector>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "data.h"

using namespace std;

int
main (int argc, char* argv[])
{
  int number;
  int server_number;
  vector <string> server;
  vector <int> port;
  
  cout << "Numero a calcular: ";
  cin >> number;
  
  cout << "Numero de servidores: ";
  cin >> server_number;
  
  for(int i = 0;i < server_number; i++)
  {
    cout << "Servidor "<< i << ": ";
    string temp_server;
    cin >> temp_server;
    server.push_back(temp_server);
    cout << "puerto del servidor " << i << ": ";
    int temp_port;
    cin >> temp_port;
    port.push_back(temp_port);
    cout << endl;
  }
  
  for (int i = 2, j = 0; i < number -1; i += (number-2)/server_number, j++)
  {
    SocketDatagrama server_socket (port.at(j));
    cout << "Sending... " << endl;
    data msj;
    char ip_server[16];
    msj.number = number;
    msj.lower_limit = i;
    msj.upper_limit = ((number-1)/server_number) * (j+1);
    if (j == server_number - 1){
      msj.upper_limit = number-1;
    }
    msj.print();
    SocketDatagrama cliente (port.at(j));
    strcpy(ip_server,server.at(j).c_str() );
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip_server, port.at(j));
    server_socket.envia(pk_send);
  }
  bool valid = true;
  SocketDatagrama result (3939);
  for (int i = 0; i < server_number; i++)
  {
    cout << "Waiting response..."<< endl;
    data msj;
    PaqueteDatagrama pk_recv (sizeof (msj));
    result.recibe(pk_recv);
    msj = *pk_recv.obtieneDatos();
    msj.print();
    valid &= msj.valid;
  }
  
  if (valid)
  {
    cout << "El numero es primo" << endl;
  }
  else
  {
    cout << "El numero NO es primo" << endl;
  }
}
