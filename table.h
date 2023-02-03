#ifndef COVER_TABLE_H
#define COVER_TABLE_H

#include<iostream>
#include<vector>
#include<stdlib.h>

namespace cover
{

  class Table
  {
    const int _width, _length;
    std::vector<std::vector<bool> > _table;

  public:
    Table(const int width, const int length):
      _width(width),_length(length),
      _table(_width, std::vector<bool>(_length,false))
    {
      init();
      randomized(0.9);
    }

    bool isGrass(const int x, const int y) const { return _table.at(x).at(y); }

    void print() const
    {
      for(int i = 0; i < _width; ++i) {
        for(int j = 0; j < _length; ++j) {
          if(_table[i][j])
            std::cout << "  ";
          else
            std::cout << "# ";
        }
        std::cout << std::endl;
      }
    }

  private:

    void init()
    {
      for(int i = 0; i < _width; ++i)
        _table[i][0] = _table[i][_length-1] = false;
      for(int j = 1; j < _length - 1; ++j)
        _table[0][j] = _table[_width-1][j] = false;
    }

    void randomized(const double prob)
    {
      //srand(time(nullptr));
      for(int i = 1; i < _width - 1; ++i)
        for(int j = 1; j < _length - 1; ++j)
          if((static_cast<double>(rand())/(RAND_MAX)) < prob)
            _table[i][j] = true;
    }
  };

}

#endif