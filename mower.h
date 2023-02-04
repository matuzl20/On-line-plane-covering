#ifndef COVER_MOWER
#define COVER_MOWER

#include "garden.h"

#include<set>
#include<stack>

namespace cover
{

  enum Direction { UP, LEFT, DOWN, RIGHT };

  std::ostream& operator<<(std::ostream& os, const Direction& d)
  {
    switch(d) {
      case UP:    os << "UP";     break;
      case LEFT:  os << "LEFT";   break;
      case DOWN:  os << "DOWN";   break;
      case RIGHT: os << "RIGHT";  break;
    }
    return os;
  }

  class Mower
  {
    Garden _garden;
    Coordinates _pos, _prevPos;
    Direction _orient;
    std::set<Coordinates> _mowed;
    std::stack<Coordinates> _stack;

  public:

    Mower(const Garden& garden):
      _garden(garden)
    {}

    void init()
    {
      //srand(time(nullptr));
      _orient = UP;
      do {
        _pos = Coordinates(rand() % _garden.width(), rand() % _garden.length());
      } while(_garden.status(_pos) != LAWN || !findLawn(_orient));
      _garden.set(_prevPos = _pos, MOWER);
    }

    /* procedure DFS_iterative(G, v) is
    let S be a stack
    S.push(v)
    while S is not empty do
        v = S.pop()
        if v is not labeled as discovered then
            label v as discovered
            for all edges from v to w in G.adjacentEdges(v) do 
                S.push(w) */

    void dfs()
    {
      _stack.push(_pos);
      while(!_stack.empty()) {
        //std::cout << "Stack: " << _stack.size() << std::endl;;
        const auto c = _stack.top();
        //std::cout << "Current position of stack: " << c << std::endl;
        _stack.pop();
        if(!isDiscovered(c)) {
          discover(c);
          forAllEdges();
        }
        else {
          //std::cout << c << " is already discovered!\n";

        }
        print();
      }
    }

    /*
      procedure DFS(G, v) is
      label v as discovered
      for all directed edges from v to w that are in G.adjacentEdges(v) do
        if vertex w is not labeled as discovered then
          recursively call DFS(G, w)
    */

    void rec_dfs()
    {
      rec_dfs(_pos,1);
    }

    void rec_dfs(const Coordinates& c, int x)
    {
      discover(c);
      print();
      const auto ori = static_cast<int>(_orient);
      //std::cout << "Ori: " << ori << std::endl;
      for(int i = 0 ; i < 4 ; ++i) {
        std::cout << x << std::endl;
        Direction dir = static_cast<Direction>((ori + i) % 4);
        const auto& coors = coorsOfMoveTo(dir);
        //std::cout << "Dir: " << dir << std::endl;
        if(/* coors != _prevPos && */ isLawn(dir) && !isDiscovered(coors) /* && !isMowed(dir) */) {
          //std::cout << "\tPUSHED!\n";
          rec_dfs(coors,x+1);
        }
      }
      
    }

    /* void move()
    {
      // if current orientation is ok, go on.
      if(isLawn(_orient)) {
        std::cout << "LAWNING...\n";
        _prevPos = _pos;
        _pos = coorsOfMoveTo(_orient);
        _mowed.insert(_pos);
        _garden.set(_prevPos,MOWED);
        _garden.set(_pos,MOWER);
        move();
      }
      // if turning is needed.
      else {
        std::cout << "TURNING...\n";
        Direction dir;
        if(findLawn(dir)) {
          turn(dir);
          move();
        }
      }
    } */

    void print() const
    {
     /* system("sleep 0.5" );
      system("clear"); */
      _garden.print();
    }

  private:

    // dfs
    bool isDiscovered(const Coordinates& c) const
    {
      if(_mowed.empty())
        return false;
      return _mowed.find(c) != _mowed.end();
    }

    void discover(const Coordinates& c)
    {
      _prevPos = _pos;
      _pos = c;
      _mowed.insert(_pos);
      _garden.set(_prevPos,MOWED);
      _garden.set(_pos,MOWER);
    }

    void forAllEdges()
    {
      const auto ori = static_cast<int>(_orient);
      //std::cout << "Ori: " << ori << std::endl;
      for(int i = 0 ; i < 4 ; ++i) {
        Direction dir = static_cast<Direction>((ori + i) % 4);
        const auto& coors = coorsOfMoveTo(dir);
        //std::cout << "Dir: " << dir << std::endl;
        if(coors != _prevPos && isLawn(dir) /* && !isMowed(dir) */) {
          //std::cout << "\tPUSHED!\n";
          _stack.push(coors);
        }
      }
    }

    // spiral

    // fölös?

    bool isLawn(const Direction& dir) const
    {
      try {
        return _garden.status(coorsOfMoveTo(dir)) == LAWN;
      } catch(std::out_of_range&) {
        return false;
      }
    }

    Coordinates coorsOfMoveTo(const Direction& dir) const
    {
      switch (dir){
        case UP:    return Coordinates(_pos._x - 1,_pos._y);
        case LEFT:  return Coordinates(_pos._x,_pos._y - 1);
        case DOWN:  return Coordinates(_pos._x + 1,_pos._y);
        case RIGHT: return Coordinates(_pos._x,_pos._y + 1);
      }
    }

    void turn(const Direction& dir)
    {
      _orient = dir;
    }

    bool findLawn(Direction& dir) const
    {
      const auto ori = static_cast<int>(_orient);
      //std::cout << "Ori: " << ori << std::endl;
      for(int i = 0 ; i < 4 ; ++i) {
        dir = static_cast<Direction>((ori + i) % 4);
        const auto& coors = coorsOfMoveTo(dir);
        //std::cout << "Dir: " << dir << std::endl;
        if(coors != _prevPos && isLawn(dir) /* && !isMowed(dir) */)
          return true;
      }
      return false;
    }

  };

  //spiral?
  class Mower2
  {
    Garden _garden;
    Coordinates _pos, _prevPos;
    Direction _orient;
    std::set<Coordinates> _mowed;

  public:

    Mower2(const Garden& garden):
      _garden(garden)
    {}

    void init()
    {
      //srand(time(nullptr));
      _orient = UP;
      do {
        _pos = Coordinates(rand() % _garden.width(), rand() % _garden.length());
      } while(_garden.status(_pos) != LAWN || !findLawn(_orient));
      _garden.set(_prevPos = _pos, MOWER);
    }
    /*
    STC(w,x)
      Mark the current cell x as an old cell.
      2. While x has a new obstacle-free neighboring cell:
      2.1 Scan for the first new neighbor of x in counterclockwise order, starting with the parent cell w.
      Call this neighbor y.
      2.2 Construct a spanning-tree edge from x to y.
      2.3 Move to a subcell of y by following the right-side
      2.4 Execute STCl(x, y)
    */

    void spiral(/* Coordinates w, Coordinates x, Direction dir */) // w : _prevPos; x : _pos
    {
      /* Direction oppDir = opposite(dir);
      while(findLawn(dir)) {

      } */
    }

    Direction opposite(const Direction& dir) const
    {
      switch(dir) {
        case UP:    return DOWN;
        case LEFT:  return RIGHT;
        case DOWN:  return UP;
        case RIGHT: return LEFT;
      }
    }

    bool findLawn(Direction& dir) const
    {
      const auto ori = static_cast<int>(dir);
      //std::cout << "Ori: " << ori << std::endl;
      for(int i = 0 ; i < 4 ; ++i) {
        dir = static_cast<Direction>((ori + i) % 4);
        const auto& coors = coorsOfMoveTo(dir);
        //std::cout << "Dir: " << dir << std::endl;
        if(coors != _prevPos && isLawn(dir) /* && !isMowed(dir) */)
          return true;
      }
      return false;
    }

    bool isLawn(const Direction& dir) const
    {
      try {
        return _garden.status(coorsOfMoveTo(dir)) == LAWN;
      } catch(std::out_of_range&) {
        return false;
      }
    }

    Coordinates coorsOfMoveTo(const Direction& dir) const
    {
      switch (dir){
        case UP:    return Coordinates(_pos._x - 1,_pos._y);
        case LEFT:  return Coordinates(_pos._x,_pos._y - 1);
        case DOWN:  return Coordinates(_pos._x + 1,_pos._y);
        case RIGHT: return Coordinates(_pos._x,_pos._y + 1);
      }
    }



  };

} // end of namespace cover


#endif