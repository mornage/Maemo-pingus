//  $Id: pathfinder.hpp 2986 2007-08-17 16:20:09Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_PATHFINDER_HXX
#define HEADER_PATHFINDER_HXX

#include <queue>
#include "graph.hpp"

namespace WorldMapNS {

struct PathfinderResult
{
  std::vector<NodeId> path;
  float cost;
};

/** */
template<class T, class C>
class Pathfinder
{
public:
  class NodeStat
  {
  public:
    enum { CLOSED, UNKNOWN, OPEN} status;

    NodeId parent;
    float  cost;
    NodeId handle;

    NodeStat ()
      : status (UNKNOWN),
	parent(-1),
	cost(0),
	handle (-1)
    {
    }
  };

private:
  struct CostComp
  {
    Pathfinder<T, C>& pathfinder;

    CostComp(Pathfinder<T, C>& p) : pathfinder(p) {}

    bool operator()(NodeId a, NodeId b)
    {
      //std::cout << "Coast: " << pathfinder.stat_graph[a].cost << " " << pathfinder.stat_graph[b].cost << std::endl;
      return pathfinder.stat_graph[a].cost > pathfinder.stat_graph[b].cost;
    }
  };

  friend struct CostComp;

  Graph<T, C>& graph;
  NodeId start;
  std::priority_queue<NodeId, std::vector<NodeId>, CostComp> open_nodes;
  std::vector<NodeStat>   stat_graph;

public:
  /** Find pathes to all other nodes, by starting from the node \a s */
  Pathfinder (Graph<T, C>& g, NodeId s)
    : graph (g), start (s), open_nodes(CostComp(*this))
  {
    stat_graph.resize (graph.max_node_handler_value());
    push_to_open (start);

    while (!open_nodes.empty())
      {
	NodeId current = open_nodes.top ();
	open_nodes.pop ();

	//std::cout << "Current Node: " << current << " "
        //<< stat_graph[current].cost << std::endl;

	Node<T>& node = graph.resolve_node (current);
	for (std::vector<EdgeId>::iterator e = node.next.begin ();
	     e != node.next.end ();
	     ++e)
	  {
	    NodeId child_node = graph.resolve_edge(*e).destination;
	    NodeStat& stat = stat_graph[child_node];
	    float new_cost = stat_graph[current].cost + graph.resolve_edge(*e).cost;

	    if  (stat.status == NodeStat::OPEN
		 && stat.cost <= new_cost)
	      {
		// do nothing, already now a better path
	      }
	    else
	      {
		stat_graph[child_node].parent = current;
		stat_graph[child_node].cost   = new_cost;

		if (!is_open (child_node))
		  push_to_open (child_node);
	      }
	  }
      }
    //std::cout << "---DONE---" << std::endl;
  }

  /** The nodes to walk to reach end is returned in reverse order! so
      you have to handle the vector like a stack with .back() == .top() */
  std::vector<NodeId> get_path (NodeId end)
  {
    std::vector<NodeId> path;
    NodeId handle = end;

    do
      {
	path.push_back(handle);
	//std::cout << "Handle: " << handle
        //<< " Parent: " << stat_graph[handle].parent << std::endl;

	if (handle == start)
	  {
	    return path;
	  }
	else if (handle == -1)
	  {
	    // no path found
	    return  std::vector<NodeId>();
	  }
	else
	  {
	    handle = stat_graph[handle].parent;
	  }
      }
    while (1);
  }

  /** @return the cost of the path to node */
  float get_cost(NodeId node)
  {
    return stat_graph[node].cost;
  }

  PathfinderResult get_result(NodeId node)
  {
    PathfinderResult res;
    res.path = get_path(node);
    res.cost = get_cost(node);
    return res;
  }

  void push_to_open (NodeId handle)
  {
    open_nodes.push (handle);
    stat_graph[handle].status = NodeStat::OPEN;
  }

  bool is_open (NodeId handle)
  {
    return stat_graph[handle].status == NodeStat::OPEN;
  }

private:
  Pathfinder (const Pathfinder&);
  Pathfinder operator= (const Pathfinder&);
};

} // namespace WorldMapNS

#endif

/* EOF */
