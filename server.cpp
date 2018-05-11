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
  gfx_open (600, 600, "Tiro al blanco");
  gfx_clear_color( 33, 33, 33 );
  while (1)
  {
    gfx_clear ();
    gfx_color (255, 255, 0);
    for(int i = 1;i < 21;i++)
    {
        circulo(300,300,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(300,300,21);
    gfx_color (255, 255, 0);
    for(int i = 22;i < 42;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(300,300,42);
    gfx_color (200, 0, 0);
    for(int i = 43;i < 63;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(300,300,63);
    gfx_color (200, 0, 0);
    for(int i = 64;i < 84;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(300,300,84);
    gfx_color (0, 180, 255);
    for(int i = 85;i < 105;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(300,300,105);
    gfx_color (0, 180, 255);
    for(int i = 106;i < 126;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (255, 255, 255);
    circulo(300,300,126);
    gfx_color (0, 0, 0);
    for(int i = 127;i < 147;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (255, 255, 255);
    circulo(300,300,147);
    gfx_color (0, 0, 0);
    for(int i = 148;i < 168;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (30, 30, 30);
    circulo(300,300,168);
    gfx_color (255, 255, 255);
    for(int i = 169;i < 189;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (30, 30, 30);
    circulo(300,300,189);
    gfx_color (255, 255, 255);
    for(int i = 190;i < 210;i++)
    {
      circulo(300,300,i);
    }
    
    gfx_color (0, 0, 0);
    for ( auto &p : points )
    {
      gfx_line(p.x + 300 -5, p.y +300 -5, p.x +300 +5, p.y +300 +5);
      gfx_line(p.x + 300 +5, p.y +300 -5, p.x +300 -5, p.y +300 +5);
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

