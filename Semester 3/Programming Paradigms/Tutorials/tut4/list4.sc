sealed trait Tree[+A]
case object Empty extends Tree[Nothing]
case class Node[A](value: A, left: Tree[A], right: Tree[A]) extends Tree[A]

def countInternalNodes[A](tree: Tree[A]): Int = {
  def countInternalNodesAux(t: Tree[A], acc: Int): Int = t match {
    case Empty => 0
    case Node(_, Empty, Empty) => acc
    case Node(_, left, Empty) | Node(_, Empty, right) =>
      acc + countInternalNodesAux(left, acc + 1)
    case Node(_, right, left) =>
      acc + countInternalNodesAux(right, acc + 1) + countInternalNodesAux(left, acc + 1)
  }

  countInternalNodesAux(tree, 0)
}

def countExternalNodes[A](tree: Tree[A]): Int = {
  def countExternalNodesAux(t: Tree[A], acc: Int): Int = t match {
    case Empty => acc
    case Node(_, Empty, Empty) => 2 * (acc + 1)
    case Node(_, left, Empty) | Node(_, Empty, right) =>
      countExternalNodesAux(left, acc + 1) + acc + 1 + countExternalNodesAux(right, acc + 1)
    case Node(_, left, right) =>
      countExternalNodesAux(left, acc + 1) + countExternalNodesAux(right, acc + 1)
  }

  countExternalNodesAux(tree, 0)
}

case class Graph[A](graph: A => List[A])

def depthFirstSearch[A](graph: Graph[A], startNode: A): List[A] = {
  def dfsAux(visited: Set[A], stack: List[A]): List[A] = stack match {
    case Nil => List.empty[A]
    case head :: tail =>
      if (visited.contains(head)) dfsAux(visited, tail)
      else head :: dfsAux(visited + head, graph.graph(head) ++ tail)
  }

  dfsAux(Set.empty[A], List(startNode))
}
