#ifndef COVER_TABLE_H
#define COVER_TABLE_H

#include<iostream>
#include<vector>
#include<stdlib.h>


namespace cover
{

  struct Coordinates
  {
    int _x, _y;
    Coordinates(): _x(-1), _y(-1) {}
    Coordinates(const int x, const int y): _x(x), _y(y) {}
    bool operator==(const Coordinates& c) const { return c._x == _x && c._y == _y; }
    bool operator!=(const Coordinates& c) const { return c._x != _x || c._y != _y; }
    bool operator<(const Coordinates& c) const  { return _x < c._x || _y < c._y;   }
  };

  std::ostream& operator<<(std::ostream& os, const Coordinates& c)
  {
    os << "(" << c._x <<  " " << c._y << ")";
    return os;
  }

  enum GardenStatus { OBSTACLE, LAWN, MOWER, MOWED };

  std::ostream& operator<<(std::ostream& os, const GardenStatus& st)
  {
    switch(st) {
      case OBSTACLE:  std::cout << "##";  break;
      case LAWN:      std::cout << ";;" ; break;
      case MOWER:     std::cout << "o " ; break;
      case MOWED:     std::cout << "  " ; break;
    }
    return os;
  }

  class Garden
  {
    const int _width, _length;
    std::vector<std::vector<GardenStatus> > _table;

  public:

    Garden(const int width, const int length, const double prob):
      _width(width),_length(length),
      _table(_width, std::vector<GardenStatus>(_length,LAWN))
    {
      init();
      randomized(prob);
    }

    void print() const
    {
      for(int i = 0; i < _width; ++i) {
        for(int j = 0; j < _length; ++j)
          std::cout << _table[i][j];
        std::cout << std::endl;
      }
    }

    GardenStatus status(const Coordinates& c) const
    {
      return _table.at(c._x).at(c._y);
    }

    void set(const Coordinates& c, const GardenStatus& st)
    {
      _table.at(c._x).at(c._y) = st;
    }

    int width()  const { return _width;  }
    int length() const { return _length; }

  private:

    void init()
    {
      for(int i = 0; i < _width; ++i)
        _table[i][0] = _table[i][_length-1] = OBSTACLE;
      for(int j = 1; j < _length - 1; ++j)
        _table[0][j] = _table[_width-1][j] = OBSTACLE;
    }

    void randomized(const double prob)
    {
      srand(time(nullptr));
      for(int i = 1; i < _width - 1; ++i)
        for(int j = 1; j < _length - 1; ++j)
          if((static_cast<double>(rand())/(RAND_MAX)) < prob)
            _table[i][j] = OBSTACLE;
    }
  };

}

#endif