#ifndef COVER_GRAPH_H
#define COVER_GRAPH_H

#include<iostream>
#include<vector>

namespace cover
{

  struct Invalid
  {
    Invalid() {}
    bool operator==(Invalid) { return true;  }
    bool operator!=(Invalid) { return false; }
    bool operator< (Invalid) { return false; }
  };

  class Coordinates
  {
    const int _x, _y;

  public:
    Coordinates(Invalid&) : _x(-1), _y(-1) {}
    Coordinates(const int x, const int y): _x(x), _y(y) {}
    bool operator==(const Coordinates& c) const { return c._x == _x && c._y == _y; }
    bool operator!=(const Coordinates& c) const { return c._x != _x || c._y != _y; }
    bool operator<(const Coordinates& c) const { return norm() < c.norm(); }

  private:
    int norm() const { return _x * _x + _y * _y; }
  };

  class Node
  {
    const int _id;
    static int _maxNodeId;
    const Coordinates _c;

  public:
    Node(Invalid i) : _id(-1), _c(i) {}
    Node(const Coordinates& c) : _id(_maxNodeId++), _c(c) {}
    Node(const int x, const int y) : _id(_maxNodeId++), _c(x,y) {}
    bool operator==(const Node& n) const { return _id == n._id; }
    bool operator!=(const Node& n) const { return _id != n._id; }
    bool operator< (const Node& n) const { return _id < n._id; }
    static int maxNodeId() { return _maxNodeId; }
    friend std::ostream& operator<<(std::ostream&, const Node&);
  };

  std::ostream& operator<<(std::ostream& os, const Node& n)
  {
    os << n._id ;
    return os;
  }

  class Edge
  {
    const int _id;
    static int _maxEdgeId;
    const Node _u, _v;

  public:
    Edge(Invalid i) : _id(-1), _u(i), _v(i) {}
    Edge(const Node& u, const Node& v) : _id(_maxEdgeId++), _u(u), _v(v) {}
    bool operator==(const Edge& e) const { return _id == e._id; }
    bool operator!=(const Edge& e) const { return _id != e._id; }
    bool operator< (const Edge& e) const { return _id < e._id; }
    static int maxEdgeId() { return _maxEdgeId; }
    friend std::ostream& operator<<(std::ostream&, const Edge&);
  };

  std::ostream& operator<<(std::ostream& os, const Edge& e)
  {
    os << e._id;
    return os;
  }

  class Graph
  {
    std::vector<Node> _nodes;
    std::vector<Edge> _edges;

  public:

    Graph() {}

    void addNode(const Coordinates& c) { _nodes.push_back(Node(c)); }
    void addNode(const int x, const int y) { _nodes.push_back(Node(x,y)); }
  };

} // end of namespace cover

#endif