#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "data.h"

using namespace std;

int
main (int argc, char* argv[])
{
  if (argc < 3)
  {
    return 1;
  }
  char ip_server [16];
  strcpy( ip_server,argv[1] );
  int port = atoi(argv[2]);
  
  SocketDatagrama client(0);
  
  data msj;
  msj.x = 0;
  msj.y = 0;
  while (1)
  {
    cout << "Sending Packet... ";
    msj.print();
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip_server, port);
    client.envia(pk_send);  
    msj.x++;
    msj.y++;
    usleep(1000000);
  }
  

}
