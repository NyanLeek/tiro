#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>

class data
{
  public:
    int id;
    float x;
    float y;
    float speed;
    float x_dest;
    float y_dest;
    bool valid;
    void print (void);
};

#endif