#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "gfx.h"

using namespace std;

int
circulo ( int x0, int y0, int radius )
{
  int x = radius-1;
  int y = 0;
  int dx = 1;
  int dy = 1;
  int err = dx - (radius << 1);

  while (x >= y)
  {
      gfx_point(x0 + x, y0 + y);
      gfx_point(x0 + y, y0 + x);
      gfx_point(x0 - y, y0 + x);
      gfx_point(x0 - x, y0 + y);
      gfx_point(x0 - x, y0 - y);
      gfx_point(x0 - y, y0 - x);
      gfx_point(x0 + y, y0 - x);
      gfx_point(x0 + x, y0 - y);
      if (err <= 0)
      {
          y++;
          err += dy;
          dy += 2;
      }
      
      if (err > 0)
      {
          x--;
          dx += 2;
          err += dx - (radius << 1);
      }
  }
  return 0;
}

int
dibuja ( void )
{  
  gfx_open (300, 300, "Tiro al blanco");
  gfx_clear_color( 33, 33, 33 );
  while (1)
  {
    gfx_clear ();
    gfx_color (255, 255, 0);
    for(int i = 1;i < 11;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,11);
    gfx_color (255, 255, 0);
    for(int i = 12;i < 22;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,22);
    gfx_color (200, 0, 0);
    for(int i = 23;i < 33;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,33);
    gfx_color (200, 0, 0);
    for(int i = 34;i < 44;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,44);
    gfx_color (0, 180, 255);
    for(int i = 45;i < 55;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,55);
    gfx_color (0, 180, 255);
    for(int i = 56;i < 66;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (255, 255, 255);
    circulo(150,150,66);
    gfx_color (0, 0, 0);
    for(int i = 67;i < 77;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (255, 255, 255);
    circulo(150,150,77);
    gfx_color (0, 0, 0);
    for(int i = 78;i < 88;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (30, 30, 30);
    circulo(150,150,88);
    gfx_color (255, 255, 255);
    for(int i = 89;i < 99;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (30, 30, 30);
    circulo(150,150,99);
    gfx_color (255, 255, 255);
    for(int i = 100;i < 110;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_flush ();
    usleep (33333);
  }
}
/*
int
network_thread ( int port )
{
  data msj, msj_client;
  char *ip_cliente;
  SocketDatagrama server (port);
  PaqueteDatagrama pk_recv (sizeof (msj));
  while (1) {
    cout << "Waiting for packet" << endl;
    int n = server.recibe (pk_recv);
    ip_cliente = pk_recv.obtieneDireccion ();
    int pto_cliente = pk_recv.obtienePuerto ();
    cout << "Packet received from " << ip_cliente << ":" << pto_cliente << endl;
    msj_client = *pk_recv.obtieneDatos ();
    cout << "Received:"<< endl;
    msj_client.print();
    
    msj.print();
    PaqueteDatagrama pk_send (&msj, sizeof (msj), ip_cliente, 3939);
    cout << "Enviando mensaje..." << endl;
    SocketDatagrama client (3939);
    int m = client.envia (pk_send);
    cout << "Mensaje enviado." << endl; 
  }
}
*/
int
main (int argc, char* argv[])
{
  if(argc < 1)
  {
    cout << "Argument missing. Usage: server" << endl;
    return 1;
  }
  
  int port = 9000;
    
  thread draw ( dibuja );
  //thread receiving ( network_thread, port );
  
  draw.join();
  //receiving.join();
  
  return 0;
}

