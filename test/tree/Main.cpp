#include "../../include/libme/bits/RBTree.hpp"
#include "libme/Allocator.hpp"

#include <stdio.h>

struct Node {
  int key;
  constexpr Node(int k)
    : key(k)
  {
  }
  bool operator==(const Node &node) const { return key == node.key; }
  bool operator<(const Node &node) const { return key < node.key; }
  bool operator>(const Node &node) const { return key > node.key; }
};

typedef me::bits::RBTreeNode<Node> NodeType;
static void print_tree(NodeType* node, int height)
{
  if (node != nullptr)
  {
    print_tree(static_cast<NodeType*>(node->m_left), height + 1);
    ::printf("%s[%i] = %i %s\n\e[0m", node->m_black ? "\e[0m" : "\e[31m", height, node->value().key, node->m_parent == nullptr ? "[ROOT]" : "");
    print_tree(static_cast<NodeType*>(node->m_right), height + 1);
  }
}

int main(int argc, char** argv)
{
  me::bits::RBTreeImpl<NodeType, me::DefaultAllocator<NodeType>> tree;
  tree.insert(Node(83));
  tree.insert(Node(17));
  tree.insert(Node(3));
  tree.insert(Node(45));
  tree.insert(Node(77));
  tree.insert(Node(103));
  ::printf("after inserted\n");
  print_tree(tree.get_root(), 0);

  tree.remove(Node(45));
  ::printf("\nafter removed\n");
  print_tree(tree.get_root(), 0);
}
