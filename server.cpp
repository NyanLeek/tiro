#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <thread>

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
}

int
dibuja ( void )
{  
  gfx_open (300, 300, "Tiro al blanco");
  gfx_clear_color( 33, 33, 33 );
  int frame = 1;
  while (1)
  {
    cout << "Frase: " << frame++ << '\r' << flush;
    gfx_clear ();
    gfx_color (255, 255, 0);
    for(int i = 1;i < 6;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,6);
    gfx_color (255, 255, 0);
    for(int i = 7;i < 12;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,12);
    gfx_color (255, 255, 0);
    for(int i = 13;i < 18;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,18);
    gfx_color (255, 255, 0);
    for(int i = 19;i < 24;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,24);
    gfx_color (255, 255, 0);
    for(int i = 25;i < 30;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,30);
    gfx_color (255, 255, 0);
    for(int i = 31;i < 36;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,36);
    gfx_color (255, 255, 0);
    for(int i = 37;i < 42;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_color (0, 0, 0);
    circulo(150,150,42);
    gfx_color (255, 255, 0);
    for(int i = 43;i < 48;i++)
    {
      circulo(150,150,i);
    }
    
    gfx_flush ();
    usleep (16666);
  }
}

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

int
main (int argc, char* argv[])
{
  if(argc < 2)
  {
    cout << "Argument missing. Usage: server side_size" << endl;
    return 1;
  }
  
  int port = 9000;
    
  thread draw ( dibuja );
  //thread receiving ( network_thread, port );
  
  draw.join();
  //receiving.join();
  
  return 0;
}

