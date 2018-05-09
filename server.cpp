#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include "gfx.h"
#include "data.h"
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

using namespace std;

vector < data > points;

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
    
    gfx_color (0, 255, 0);
    for ( auto &p : points )
    {
      gfx_line(p.x + 150 -2, p.y +150 -2, p.x +150 +2, p.y +150 +2);
      gfx_line(p.x + 150 +2, p.y +150 +2, p.x +150 -2, p.y +150 -2);
    }
    
    gfx_flush ();
    usleep (33333);
  }
}

int
red ( int port )
{
  data msj;
  char *ip_cliente;
  SocketDatagrama server (port);
  PaqueteDatagrama pk_recv (sizeof (msj));
  while (1) {
    cout << "Waiting for packet" << endl;
    server.recibe (pk_recv);
    ip_cliente = pk_recv.obtieneDireccion ();
    int pto_cliente = pk_recv.obtienePuerto ();
    cout << "Packet received from " << ip_cliente << ":" << pto_cliente << endl;
    msj = *pk_recv.obtieneDatos ();
    cout << "Received:"<< endl;
    msj.print();
    points.push_back(msj);
  }
}

int
main (int argc, char* argv[])
{
  if(argc < 1)
  {
    cout << "Argument missing. Usage: server" << endl;
    return 1;
  }
  
  int port = 7300;
    
  thread draw ( dibuja );
  thread receive ( red, port );
  
  draw.join();
  receive.join();
  
  return 0;
}

