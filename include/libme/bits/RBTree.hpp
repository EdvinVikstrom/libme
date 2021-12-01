#ifndef LIBME_BITS_RBTREE_HPP
  #define LIBME_BITS_RBTREE_HPP

#include "libme/PointerTraits.hpp"
#include "libme/TypeTraits.hpp"
#include "libme/Allocator.hpp"
#include "libme/Utility.hpp"

namespace me::bits {

  struct RBTreeNodeBase {
    RBTreeNodeBase* m_parent;
    RBTreeNodeBase* m_left;
    RBTreeNodeBase* m_right;
    bool m_black;

    constexpr RBTreeNodeBase* uncle()
    {
      if (m_parent == m_parent->m_parent->m_left)
	return m_parent->m_parent->m_right;
      return m_parent->m_parent->m_left;
    }

    constexpr RBTreeNodeBase* sibling()
    {
      if (this == m_parent->m_left)
	return m_parent->m_right;
      return m_parent->m_left;
    }

    constexpr RBTreeNodeBase* close_nephew()
    {
      if (this == m_parent->m_left)
	return m_parent->m_right->m_left;
      return m_parent->m_left->m_right;
    }

    constexpr RBTreeNodeBase* distant_nephew()
    {
      if (this == m_parent->m_left)
	return m_parent->m_right->m_right;
      return m_parent->m_left->m_left;
    }

    constexpr RBTreeNodeBase* child(bool left)
    {
      return left ? m_left : m_right;
    }

    constexpr bool is_left()
    {
      return this == m_parent->m_left;
    }

    constexpr bool has_child()
    {
      return m_left != nullptr || m_right != nullptr;
    }

    constexpr bool has_red_child()
    {
      return (m_left != nullptr && !m_left->m_black) || (m_right != nullptr && !m_right->m_black);
    }

    // Precondition: this->m_parent must be a valid pointer
    constexpr void set_self(RBTreeNodeBase* node)
    {
      if (this == m_parent->m_left)
	m_parent->m_left = node;
      else
	m_parent->m_right = node;
    }
  };

  template<typename Value>
  struct RBTreeNode : RBTreeNodeBase {
    typedef typename aligned_storage<sizeof(Value), alignof(Value)>::type ValueType;

    ValueType m_value;

    constexpr RBTreeNode(
	RBTreeNodeBase* parent,
	RBTreeNodeBase* left,
	RBTreeNodeBase* right,
	bool black)
      : RBTreeNodeBase{parent, left, right, black}
    {
      AllocatorTraits<Value>::construct(reinterpret_cast<Value*>(m_value.data));
    }

    constexpr RBTreeNode(
	RBTreeNodeBase* parent,
	RBTreeNodeBase* left,
	RBTreeNodeBase* right,
	bool black,
	const Value &val)
      : RBTreeNodeBase{parent, left, right, black}
    {
      AllocatorTraits<Value>::construct(reinterpret_cast<Value*>(m_value.data), val);
    }

    constexpr RBTreeNode(
	RBTreeNodeBase* parent,
	RBTreeNodeBase* left,
	RBTreeNodeBase* right,
	bool black,
	Value &&val)
      : RBTreeNodeBase{parent, left, right, black}
    {
      AllocatorTraits<Value>::construct(reinterpret_cast<Value*>(m_value.data), move(val));
    }

    // Precondition: m_value must be valid
    constexpr ~RBTreeNode()
    {
      AllocatorTraits<Value>::destroy(reinterpret_cast<Value*>(m_value.data));
    }

    constexpr Value& value() { return *reinterpret_cast<Value*>(m_value.data); }
  };

  template<typename Node>
  struct RBTreeNodeIterator {

    typedef Node NodeType;
    typedef Node* NodePointer;

    NodePointer m_pos;

    constexpr NodePointer operator++()
    {
      return m_pos;
    }

    constexpr NodePointer operator--()
    {
      return m_pos;
    }

    constexpr operator bool()
    {
      return m_pos;
    }

    constexpr operator NodePointer()
    {
      return m_pos;
    }

  };

  template<typename Node>
  struct RBTreeConstNodeIterator {
  };

  template<typename Node, typename Alloc>
  class RBTreeImpl {

  public:

    typedef size_t SizeType;
    typedef AllocatorTraits<Node, Alloc> Traits;
    typedef RBTreeNodeBase NodeBaseType;
    typedef RBTreeNodeBase* NodeBasePointer;
    typedef const RBTreeNodeBase* ConstNodeBasePointer;
    typedef Node NodeType;
    typedef Node* NodePointer;
    typedef const Node* ConstNodePointer;
    typedef RBTreeNodeIterator<Node> NodeIterator;
    typedef RBTreeConstNodeIterator<Node> ConstNodeIterator;

  private:

    NodePointer m_root;
    SizeType m_count;

  public:

    constexpr RBTreeImpl();
    constexpr RBTreeImpl(const RBTreeImpl &tree);
    constexpr RBTreeImpl(RBTreeImpl &&tree);
    constexpr ~RBTreeImpl();
    constexpr RBTreeImpl& operator=(const RBTreeImpl &tree);
    constexpr RBTreeImpl& operator=(RBTreeImpl &&tree);
    
    // Precondition: root->m_right must be a valid pointer
    constexpr void rotate_left(NodeBasePointer root);

    // Precondition: root->m_right must be a valid pointer
    constexpr void rotate_right(NodeBasePointer root);

    // Precondition: if left see rotate_left() otherwise see rotate_right()
    constexpr void rotate(NodeBasePointer root, bool left);

    // Returns: A pointer to a node with matching key or nullptr if no match was found.
    template<typename Key> constexpr NodePointer search(NodePointer node, const Key &key);
    
    // Same as search(m_root, key)
    template<typename Key> constexpr NodePointer search(const Key &key);

    // Returns: A pointer to the inserted node
    template<typename Value> constexpr NodePointer insert(Value &&value);
    constexpr void bst_insert(NodePointer node);
    // Precondition: node and node->m_parent must be a valid pointer
    constexpr void insert_rebalance(NodeBasePointer node);

    // Returns: A pointer to the removed node
    template<typename Key> constexpr NodePointer remove(const Key &key);
    // Returns: Node that replaced node
    constexpr void bst_remove(NodePointer node);
    constexpr void remove_rebalance(NodeBasePointer node);

    constexpr void subtree_shift(NodeBasePointer node1, NodeBasePointer node2);

    constexpr void clear() noexcept;

    constexpr NodeIterator make_iterator(SizeType pos) { return {}; }
    constexpr ConstNodeIterator make_iterator(SizeType pos) const { return {}; }
    constexpr NodeIterator make_iterator(NodePointer pos) { return {}; }
    constexpr ConstNodeIterator make_iterator(ConstNodePointer pos) const { return {}; }

    constexpr NodePointer get_root() const { return m_root; }
    constexpr SizeType get_count() const { return m_count; }

  };

  constexpr bool rbtree_node_is_black(RBTreeNodeBase* node) { return node == nullptr || node->m_black; }

  // Precondition: root and node must be a valid pointer
  template<typename Node> constexpr Node* rbtree_node_leaf(Node* root, Node* node);

  constexpr RBTreeNodeBase* rbtree_node_min(RBTreeNodeBase* node);
  constexpr RBTreeNodeBase* rbtree_node_max(RBTreeNodeBase* node);

  constexpr RBTreeNodeBase* rbtree_node_successor(RBTreeNodeBase* node);
  constexpr RBTreeNodeBase* rbtree_node_predecessor(RBTreeNodeBase* node);

  constexpr RBTreeNodeBase* rbtree_node_next(RBTreeNodeBase* node);
  constexpr RBTreeNodeBase* rbtree_node_prev(RBTreeNodeBase* node);

} // namespace me

/* ------------------------ */
/* class me::bits::TreeImpl */
/* ------------------------ */
template<typename Node, typename Alloc>
constexpr me::bits::RBTreeImpl<Node, Alloc>::RBTreeImpl()
  : m_root(nullptr), m_count(0)
{
}

template<typename Node, typename Alloc>
constexpr me::bits::RBTreeImpl<Node, Alloc>::RBTreeImpl(const RBTreeImpl &tree)
{
}

template<typename Node, typename Alloc>
constexpr me::bits::RBTreeImpl<Node, Alloc>::RBTreeImpl(RBTreeImpl &&tree)
  : m_root(tree.m_root), m_count(tree.m_count)
{
  tree.m_root = nullptr;
  tree.m_count = 0;
}

template<typename Node, typename Alloc>
constexpr me::bits::RBTreeImpl<Node, Alloc>::~RBTreeImpl()
{
}

template<typename Node, typename Alloc>
constexpr me::bits::RBTreeImpl<Node, Alloc>&
  me::bits::RBTreeImpl<Node, Alloc>::operator=(const RBTreeImpl &tree)
{
}

template<typename Node, typename Alloc>
constexpr me::bits::RBTreeImpl<Node, Alloc>&
  me::bits::RBTreeImpl<Node, Alloc>::operator=(RBTreeImpl &&tree)
{
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::rotate_left(NodeBasePointer root)
{
  NodeBasePointer pivot = root->m_right;
  root->m_right = pivot->m_left;
  if (root->m_right != nullptr)
    root->m_right->m_parent = root;
  pivot->m_parent = root->m_parent;
  if (root->m_parent == nullptr)
    m_root = static_cast<NodePointer>(pivot);
  else if (root->m_parent->m_left == root)
    root->m_parent->m_left = pivot;
  else
    root->m_parent->m_right = pivot;
  pivot->m_left = root;
  root->m_parent = pivot;
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::rotate_right(NodeBasePointer root)
{
  NodeBasePointer pivot = root->m_left;
  root->m_left = pivot->m_right;
  if (root->m_left != nullptr)
    root->m_left->m_parent = root;
  pivot->m_parent = root->m_parent;
  if (root->m_parent == nullptr)
    m_root = static_cast<NodePointer>(pivot);
  else if (root->m_parent->m_right == root)
    root->m_parent->m_right = pivot;
  else
    root->m_parent->m_left = pivot;
  pivot->m_right = root;
  root->m_parent = pivot;
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::rotate(NodeBasePointer root, bool left)
{
  if (left)
    rotate_left(root);
  else
    rotate_right(root);
}

template<typename Node, typename Alloc>
template<typename Key>
constexpr typename me::bits::RBTreeImpl<Node, Alloc>::NodePointer
  me::bits::RBTreeImpl<Node, Alloc>::search(NodePointer node, const Key &key)
{
  while (node != nullptr && key != node->value())
  {
    if (key < node->value())
      node = static_cast<NodePointer>(node->m_left);
    else
      node = static_cast<NodePointer>(node->m_right);
  }
  return node;
}

template<typename Node, typename Alloc>
template<typename Key>
constexpr typename me::bits::RBTreeImpl<Node, Alloc>::NodePointer
  me::bits::RBTreeImpl<Node, Alloc>::search(const Key &key)
{
  return search(m_root, key);
}

template<typename Node, typename Alloc>
template<typename Value>
constexpr typename me::bits::RBTreeImpl<Node, Alloc>::NodePointer
  me::bits::RBTreeImpl<Node, Alloc>::insert(Value &&value)
{
  NodePointer node = Traits::allocate(1);
  Traits::construct(node, nullptr, nullptr, nullptr, false, move(value));

  bst_insert(node);
  m_count++;

  if (node->m_parent == nullptr)
  {
    m_root = node;
    m_root->m_black = true;
    return node;
  }

  insert_rebalance(node);
  return node;
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::bst_insert(NodePointer node)
{
  NodePointer y = nullptr;
  NodePointer x = m_root;
  while (x != nullptr)
  {
    y = x;
    if (node->value() < x->value())
      x = static_cast<NodePointer>(x->m_left);
    else
      x = static_cast<NodePointer>(x->m_right);
  }
  node->m_parent = y;
  if (y == nullptr)
    m_root = node;
  else if (node->value() < y->value())
    y->m_left = node;
  else
    y->m_right = node;
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::insert_rebalance(NodeBasePointer node)
{
  NodeBasePointer parent = node->m_parent;

  while (true)
  {
    // parent is red
    if (!parent->m_black)
    {
      NodeBasePointer uncle = node->uncle();
      NodeBasePointer grand = parent->m_parent;

      // uncle is black
      if (uncle == nullptr || uncle->m_black)
      {
	// parent is left child
	if (parent == grand->m_left)
	{
	  // (LR) node is right child
	  if (node == parent->m_right)
	  {
	    rotate_left(parent);
	    node = parent;
	    parent = node->m_parent;
	  }
	  // (LL) node is left child
	  rotate_right(grand);
	  swap(grand->m_black, parent->m_black);
	  node = parent;

	// parent is right child
	}else
	{
	  // (RL) node is left child
	  if (node == parent->m_left)
	  {
	    rotate_right(parent);
	    node = parent;
	    parent = node->m_parent;
	  }
	  // (RR) node is right child
	  rotate_left(grand);
	  swap(grand->m_black, parent->m_black);
	  node = parent;
	}

	node = parent;
	continue;

      // uncle is red
      }else
      {
        parent->m_black = uncle->m_black = true;
        grand->m_black = false;
        node = grand;
	continue;
      }
    }
    break;
  }
  m_root->m_black = true;
}

template<typename Node, typename Alloc>
template<typename Key>
constexpr typename me::bits::RBTreeImpl<Node, Alloc>::NodePointer
  me::bits::RBTreeImpl<Node, Alloc>::remove(const Key &key)
{
  NodePointer node = search(m_root, key);
  if (node == nullptr)
    return nullptr;
  m_count--;

  while (true)
  {
    NodeBasePointer parent = node->m_parent;
    NodePointer replace;
    if (node->m_left != nullptr && node->m_right != nullptr)
      replace = static_cast<NodePointer>(rbtree_node_successor(node->m_right));
    else if (node->m_left == nullptr && node->m_right == nullptr)
      replace = nullptr;
    else if (node->m_left != nullptr)
      replace = static_cast<NodePointer>(node->m_left);
    else
      replace = static_cast<NodePointer>(node->m_right);
  
    bool both_black = rbtree_node_is_black(node) && rbtree_node_is_black(replace);
  
    if (replace == nullptr)
    {
      if (node == m_root)
        m_root = nullptr;
      else
      {
        if (both_black)
	  remove_rebalance(node);
        else if (node->sibling() != nullptr)
	  node->sibling()->m_black = false;
  
        if (node->is_left())
	  parent->m_left = nullptr;
        else
	  parent->m_right = nullptr;
      }
      Traits::destroy(node);
      Traits::deallocate(node);
      break;

    }else if (node->m_left == nullptr || node->m_right == nullptr)
    {
      if (node == m_root)
      {
	node->value() = move(replace->value());
        node->m_left = node->m_right = nullptr;
	Traits::destroy(node);
	Traits::deallocate(node);
      }else
      {
        if (node->is_left())
	  parent->m_left = replace;
        else
	  parent->m_right = replace;
	Traits::destroy(node);
	Traits::deallocate(node);
        replace->m_parent = parent;
        if (both_black)
	  remove_rebalance(replace);
        else
	  replace->m_black = true;
      }
      break;
    }

    swap(node->value(), replace->value());
    node = replace;
  }
  return node;
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::bst_remove(NodePointer node)
{
  if (node->m_left == nullptr)
    subtree_shift(node, node->m_right);
  else if (node->m_right == nullptr)
    subtree_shift(node, node->m_left);
  else
  {
    NodeBasePointer successor = rbtree_node_successor(node);
    if (successor->m_parent != node)
    {
      subtree_shift(successor, successor->m_right);
      successor->m_right = node->m_right;
      successor->m_right->m_parent = successor;
    }
    subtree_shift(node, successor);
    successor->m_left = node->m_left;
    successor->m_left->m_parent = successor;
  }
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::remove_rebalance(NodeBasePointer node)
{
  while (true)
  {
    if (node == m_root)
      break;

    NodeBasePointer parent = node->m_parent;
    NodeBasePointer sibling = node->sibling(); // can sibling be nullptr?

    if (sibling == nullptr)
    {
      node = parent;
      continue;
    }

    // sibling is red
    if (!sibling->m_black)
    {
      parent->m_black = false;
      sibling->m_black = true;
      if (sibling->is_left())
        rotate_right(parent);
      else
        rotate_left(parent);
      continue;
      
    // sibling is black and one of sibling's children is red
    }else if (sibling->has_red_child())
    {
      if (sibling->m_left != nullptr && !sibling->m_left->m_black)
      {
	if (sibling->is_left())
	{
          sibling->m_left->m_black = sibling->m_black;
          sibling->m_black = parent->m_black;
          rotate_right(parent);
	}else
	{
          sibling->m_left->m_black = parent->m_black;
          rotate_right(sibling);
          rotate_left(parent);
	}
      }else
      {
	if (sibling->is_left())
	{
          sibling->m_right->m_black = parent->m_black;
          rotate_left(sibling);
          rotate_right(parent);
	}else
	{
          sibling->m_right->m_black = sibling->m_black;
          sibling->m_black = parent->m_black;
          rotate_left(parent);
	}
      }
      parent->m_black = true;
  
    // sibling children are both black
    }else
    {
      sibling->m_black = false;
      if (parent->m_black)
      {
        node = parent;
        continue;
      }
      parent->m_black = true;
    }
    break;
  }
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::subtree_shift(NodeBasePointer node1, NodeBasePointer node2)
{
  if (node1->m_parent == nullptr)
    m_root = static_cast<NodePointer>(node2);
  else if (node1->is_left())
    node1->m_parent->m_left = node2;
  else
    node1->m_parent->m_right = node2;
  if (node2 != nullptr)
    node2->m_parent = node1->m_parent;
}

template<typename Node, typename Alloc>
constexpr void
  me::bits::RBTreeImpl<Node, Alloc>::clear()
  noexcept
{
  NodeIterator begin = make_iterator(0);
  NodeIterator end = make_iterator(m_count);

  for (; begin != end; begin++)
  {
    Traits::destroy(begin);
    Traits::deallocate(begin);
  }
  m_root = nullptr;
  m_count = 0;
}

template<typename Node>
constexpr Node*
  me::bits::rbtree_node_leaf(Node* root, Node* node)
{
  if (node->value() == root->value())
    return root;

  if (node->value() < root->value())
    return rbtree_node_leaf(static_cast<Node*>(root->m_left), node);
  return rbtree_node_leaf(static_cast<Node*>(root->m_right), node);
}

constexpr me::bits::RBTreeNodeBase*
  me::bits::rbtree_node_min(RBTreeNodeBase* node)
{
  while (node->m_left != nullptr)
    node = node->m_left;
  return node;
}

constexpr me::bits::RBTreeNodeBase*
  me::bits::rbtree_node_max(RBTreeNodeBase* node)
{
  while (node->m_right != nullptr)
    node = node->m_right;
  return node;
}

constexpr me::bits::RBTreeNodeBase*
  me::bits::rbtree_node_successor(RBTreeNodeBase* node)
{
  if (node->m_right != nullptr)
    return rbtree_node_min(node->m_right);
  RBTreeNodeBase* y = node->m_parent;
  while (y != nullptr && node == y->m_right)
  {
    node = y;
    y = y->m_parent;
  }
  return y;
}

constexpr me::bits::RBTreeNodeBase*
  me::bits::rbtree_node_predecessor(RBTreeNodeBase* node)
{
  if (node->m_left != nullptr)
    return rbtree_node_max(node->m_left);
  RBTreeNodeBase* y = node->m_parent;
  while (y != nullptr && node == y->m_left)
  {
    node = y;
    y = y->m_parent;
  }
  return y;
}

/*
 *         U
 *        / \
 *       /   \
 *      W     F
 *     / \   / \
 *    L   O V   G
 *     \       / \
 *      B     Y   H
 *
 *
 * x = U
 * x = tree_node_next(xU) == V
 * x = tree_node_next(xV) == F
 * x = tree_node_next(xF) == Y
 * x = tree_node_next(xY) == G
 * x = tree_node_next(xG) == H
 * x = tree_node_next(xH) == U
 * x = tree_node_next(xU) == ERR
 *
 */
constexpr me::bits::RBTreeNodeBase*
  me::bits::rbtree_node_next(RBTreeNodeBase* node)
{
  if (node->m_right != nullptr)
    return rbtree_node_min(node->m_right);
  while (node != node->m_parent->m_left)
    node = node->m_parent;
  return node->m_parent;
}

constexpr me::bits::RBTreeNodeBase*
  me::bits::rbtree_node_prev(RBTreeNodeBase* node)
{
  if (node->m_left != nullptr)
    return rbtree_node_max(node->m_left);
  while (node == node->m_parent->m_left)
    node = node->m_parent;
  return node->m_parent;
}

#endif
