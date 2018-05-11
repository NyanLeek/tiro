#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <random>
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
  /*int point_n;
  cout << "Numero de puntos: ";
  cin >> point_n;
  */
  char ip_server [16];
  strcpy( ip_server,argv[1] );
  int port = atoi(argv[2]);
  
  default_random_engine generator;
  normal_distribution<double> distribution(0,1);
  
  SocketDatagrama client(0);
  
  data msj;
  while (1)
  {
    double rx = distribution(generator);
    double ry = distribution(generator);
    rx -= 1;
    ry -= 1;
    rx *= 210;
    ry *= 210;
    msj.x = rx;
    msj.y = ry;
    cout << "Sending Packet... ";
    msj.print();
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip_server, port);
    client.envia(pk_send);  
    usleep(100000);
  }
}
