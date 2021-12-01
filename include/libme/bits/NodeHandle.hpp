#ifndef LIBME_NODE_HANDLE_HPP
  #define LIBME_NODE_HANDLE_HPP

#include "libme/bits/RBTree.hpp"
#include "libme/Pair.hpp"

namespace me::bits {

  template<typename Value>
  using NodeHandle = RBTreeNode<Value>;

  template<typename Value>
  struct SetNode {

    Value m_value;

    constexpr SetNode(const Value &value)
      : m_value(value) { }
    constexpr SetNode(Value &&value)
      : m_value(move(value)) { }

    constexpr bool operator==(const Value &val) const { return val == m_value; }
    constexpr bool operator<(const Value &val) const { return val < m_value; }
    constexpr bool operator>(const Value &val) const { return val > m_value; }

  };

  template<typename Key, typename Value>
  struct MapNode {

    Pair<Key, Value> m_value;

    constexpr MapNode(const Pair<Key, Value> &value)
      : m_value(value) { }
    constexpr MapNode(Pair<Key, Value> &&value)
      : m_value(move(value)) { }

    constexpr bool operator==(const Pair<Key, Value> &val) const { return val.first == m_value.first; }
    constexpr bool operator<(const Pair<Key, Value> &val) const { return val.first < m_value.first; }
    constexpr bool operator>(const Pair<Key, Value> &val) const { return val.first > m_value.first; }
    constexpr bool operator==(const Key &key) const { return key == m_value.first; }
    constexpr bool operator<(const Key &key) const { return key < m_value.first; }
    constexpr bool operator>(const Key &key) const { return key > m_value.first; }

  };

  template<typename Value>
  using SetNodeHandle = NodeHandle<SetNode<Value>>;

  template<typename Key, typename Value>
  using MapNodeHandle = NodeHandle<MapNode<Key, Value>>;

} // namespace me::bits

#endif
