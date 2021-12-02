#ifndef LIBME_MAP_HPP
  #define LIBME_MAP_HPP

#include "libme/Type.hpp"
#include "libme/Allocator.hpp"
#include "libme/TypeTraits.hpp"
#include "libme/Memory.hpp"
#include "libme/Exceptions.hpp"
#include "libme/Functional.hpp"
#include "libme/bits/NodeHandle.hpp"

#include <initializer_list>

namespace me {

  template<typename Key, typename Value, typename Compare, typename Alloc>
  class MultiMap;

  template<typename Key, typename Value, typename Compare = less<Key>, typename Alloc = DefaultAllocator<Value>>
  class Map {

  public:

    typedef Key KeyType;
    typedef Value MappedType;
    typedef Pair<const Key, Value> ValueType;
    typedef size_t SizeType;
    typedef ptrdiff_t DifferenceType;
    typedef Compare KeyCompare;
    typedef AllocatorTraits<ValueType, Alloc> Traits;
    typedef ValueType& Reference;
    typedef const ValueType& ConstReference;
    typedef typename Traits::Pointer Pointer;
    typedef typename Traits::ConstPointer ConstPointer;
    typedef bits::MapNodeHandle<Key, Value> NodeType;
    typedef bits::RBTreeNodeIterator<NodeType> Iterator;
    typedef bits::RBTreeConstNodeIterator<NodeType> ConstIterator;

    struct InsertReturnType {
      Iterator position;
      bool inserted;
      NodeType node;
    };

  private:

    bits::RBTreeImpl<NodeType, DefaultAllocator<NodeType>> m_tree;

  public:

    constexpr Map();
    template<typename Iter> constexpr Map(Iter first, Iter last);
    constexpr Map(const Map &map);
    constexpr Map(Map &&map);
    constexpr Map(std::initializer_list<ValueType> list);
    constexpr ~Map();
    constexpr Map& operator=(const Map &map);
    constexpr Map& operator=(Map &&map)
      noexcept(is_nothrow_move_assignable<Compare>::value);
    constexpr Map& operator=(std::initializer_list<ValueType> list);

    constexpr MappedType& at(const Key &key);
    constexpr const MappedType& at(const Key &key) const;
    constexpr MappedType& operator[](const Key &key);
    constexpr MappedType& operator[](Key &&key);

    constexpr Iterator begin();
    constexpr ConstIterator begin() const;
    constexpr Iterator end();
    constexpr ConstIterator end() const;

    constexpr bool is_empty() const;
    constexpr SizeType length() const;
    constexpr SizeType max_length() const;

    constexpr void clear() noexcept;
    constexpr Pair<Iterator, bool> insert(ConstReference val);
    template<typename T> constexpr Pair<Iterator, bool> insert(T &&val)
      requires is_constructible<ValueType, T&&>::value;
    constexpr Pair<Iterator, bool> insert(ValueType &&val);
    constexpr Iterator insert(ConstIterator hint, ConstReference val);
    template<typename T> constexpr Iterator insert(ConstIterator hint, T &&val)
      requires is_constructible<ValueType, T&&>::value;
    constexpr Iterator insert(ConstIterator hint, ValueType &&val);
    template<typename Iter> constexpr void insert(Iter first, Iter last);
    constexpr void insert(std::initializer_list<ValueType> list);
    constexpr InsertReturnType insert(NodeType &&node);
    constexpr Iterator insert(ConstIterator hint, NodeType &&node);
    template<typename T> constexpr Pair<Iterator, bool> insert_or_assign(const KeyType &key, T &&obj);
    template<typename T> constexpr Pair<Iterator, bool> insert_or_assign(KeyType &&key, T &&obj);
    template<typename T> constexpr Iterator insert_or_assign(ConstIterator hint, const KeyType &key, T &&obj);
    template<typename T> constexpr Iterator insert_or_assign(ConstIterator hint, KeyType &&key, T &&obj);
    template<typename... Args> constexpr Pair<Iterator, bool> emplace(Args&&... args);
    template<typename... Args> constexpr Iterator emplace_hint(ConstIterator hint, Args&&... args);
    template<typename... Args> constexpr Pair<Iterator, bool> try_emplace(const KeyType &key, Args&&... args);
    template<typename... Args> constexpr Pair<Iterator, bool> try_emplace(KeyType &&key, Args&&... args);
    template<typename... Args> constexpr Iterator try_emplace(ConstIterator hint, const Key &key, Args&&... args);
    template<typename... Args> constexpr Iterator try_emplace(ConstIterator hint, KeyType &&key, Args&&... args);
    constexpr Iterator erase(ConstIterator pos);
    constexpr Iterator erase(ConstIterator first, ConstIterator last);
    constexpr SizeType erase(const KeyType &key);
    template<typename T> constexpr SizeType erase(T &&key);
    constexpr void swap(Map &map);
    constexpr NodeType extract(ConstIterator pos);
    constexpr NodeType extract(const KeyType &key);
    template<typename T> constexpr NodeType extract(T &&key);
    template<typename T> constexpr void merge(Map<Key, Value, T, Alloc> &map);
    template<typename T> constexpr void merge(Map<Key, Value, T, Alloc> &&map);
    template<typename T> constexpr void merge(MultiMap<Key, Value, T, Alloc> &map);
    template<typename T> constexpr void merge(MultiMap<Key, Value, T, Alloc> &&map);

    constexpr SizeType count(const KeyType &key) const;
    template<typename T> constexpr SizeType count(const T &key) const;
    constexpr Iterator find(const KeyType &key);
    constexpr ConstIterator find(const KeyType &key) const;
    template<typename T> constexpr Iterator find(const T &key);
    template<typename T> constexpr ConstIterator find(const T &key) const;
    constexpr bool contains(const KeyType &key) const;
    template<typename T> constexpr bool contains(const T &key) const;
    constexpr Pair<Iterator, Iterator> equal_range(const KeyType &key);
    constexpr Pair<ConstIterator, ConstIterator> equal_range(const KeyType &key) const;
    template<typename T> constexpr Pair<Iterator, Iterator> equal_range(const T &key);
    template<typename T> constexpr Pair<ConstIterator, ConstIterator> equal_range(const T &key) const;
    constexpr Iterator lower_bound(const KeyType &key);
    constexpr ConstIterator lower_bound(const KeyType &key) const;
    template<typename T> constexpr Iterator lower_bound(const T &key);
    template<typename T> constexpr ConstIterator lower_bound(const T &key) const;
    constexpr Iterator upper_bound(const KeyType &key);
    constexpr ConstIterator upper_bound(const KeyType &key) const;
    template<typename T> constexpr Iterator upper_bound(const T &key);
    template<typename T> constexpr ConstIterator upper_bound(const T &key) const;

  };

} // namespace me

/* ------------- */
/* class me::Map */
/* ------------- */
template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>::Map()
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename Iter>
constexpr me::Map<Key, Value, Compare, Alloc>::Map(Iter first, Iter last)
{
  for (; first != last; first++)
    m_tree.insert(first->first, first->second);
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>::Map(const Map &map)
  : m_tree(map.m_tree)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>::Map(Map &&map)
  : m_tree(move(map.m_tree))
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>::Map(std::initializer_list<ValueType> list)
{
  for (Iterator i = list.begin(); i != list.end(); i++)
    m_tree.insert(i->first, i->second);
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>::~Map()
{
  /* destroy the m_tree */
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>&
  me::Map<Key, Value, Compare, Alloc>::operator=(const Map &map)
{
  m_tree = map.m_tree;
  return *this;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>&
  me::Map<Key, Value, Compare, Alloc>::operator=(Map &&map)
  noexcept(is_nothrow_move_assignable<Compare>::value)
{
  m_tree = move(map.m_tree);
  return *this;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Map<Key, Value, Compare, Alloc>&
  me::Map<Key, Value, Compare, Alloc>::operator=(std::initializer_list<ValueType> list)
{
  for (Iterator i = list.begin(); i != list.end(); i++)
    m_tree.insert(i->first, i->second);
  return *this;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr Value&
  me::Map<Key, Value, Compare, Alloc>::at(const KeyType &key)
{
  NodeType* node = m_tree.search(key);
  if (node == nullptr)
    throw OutOfRangeError();
  return node->m_value.second;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr const Value&
  me::Map<Key, Value, Compare, Alloc>::at(const KeyType &key) const
{
  const NodeType* node = m_tree.search(key);
  if (node == nullptr)
    throw OutOfRangeError();
  return node->m_value.second;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr Value&
  me::Map<Key, Value, Compare, Alloc>::operator[](const KeyType &key)
{
  return try_emplace(key).first->second;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr Value&
  me::Map<Key, Value, Compare, Alloc>::operator[](KeyType &&key)
{
  return try_emplace(move(key)).first->second;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::begin()
{
  return m_tree.make_iterator(0);
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::ConstIterator
  me::Map<Key, Value, Compare, Alloc>::begin() const
{
  return m_tree.make_iterator(0);
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::end()
{
  return m_tree.make_iterator(m_tree.get_count());
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::ConstIterator
  me::Map<Key, Value, Compare, Alloc>::end() const
{
  return m_tree.make_iterator(m_tree.get_count());
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr bool
  me::Map<Key, Value, Compare, Alloc>::is_empty() const
{
  return m_tree.get_count() == 0;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::SizeType
  me::Map<Key, Value, Compare, Alloc>::length() const
{
  return m_tree.get_count();
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::SizeType
  me::Map<Key, Value, Compare, Alloc>::max_length() const
{
  return 1234567; // TODO
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::clear()
  noexcept
{
  m_tree.clear();
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::insert(ConstReference val)
{
  NodeType* node = m_tree.search(val);
  if (node != nullptr)
    return {node, false};
  return {m_tree.insert(val), true};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::insert(T &&val)
  requires is_constructible<ValueType, T&&>::value
{
  return emplace(forward<T>(val));
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::insert(ValueType &&val)
{
  NodeType* node = m_tree.search(forward<ValueType>(val));
  if (node != nullptr)
    return {node, false};
  return {m_tree.insert(forward<ValueType>(val)), true};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::insert(ConstIterator hint, ConstReference val)
{

}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::insert(ConstIterator hint, T &&val)
  requires is_constructible<ValueType, T&&>::value
{
  return emplace_hint(hint, forward<T>(val));
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::insert(ConstIterator hint, ValueType &&val)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename Iter>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::insert(Iter first, Iter last)
{
  for (; first != last; first++)
    m_tree.insert(*first);
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::insert(std::initializer_list<ValueType> list)
{
  ConstIterator iter = list.begin();
  for (; iter != list.end(); iter++)
    m_tree.insert(*iter);
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::InsertReturnType
  me::Map<Key, Value, Compare, Alloc>::insert(NodeType &&node)
{
  NodeType* pos = m_tree.search(forward<NodeType>(node));
  if (pos != nullptr)
    return InsertReturnType{pos, false, forward<NodeType>(node)};
  return InsertReturnType{m_tree.insert(node), true, forward<NodeType>(node)};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::insert(ConstIterator hint, NodeType &&node)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::insert_or_assign(const KeyType &key, T &&obj)
{
  if (NodeType* pos = m_tree.search(key))
  {
    pos->m_value.second = forward<T>(obj);
    return {pos, false};
  }
  return {m_tree.insert(NodeType{ValueType{key, forward<T>(obj)}}), true};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::insert_or_assign(KeyType &&key, T &&obj)
{
  if (NodeType* pos = m_tree.search(forward<KeyType>(key)))
  {
    pos->m_value.second = forward<T>(obj);
    return {pos, false};
  }
  return {m_tree.insert(NodeType{ValueType{move(key), forward<T>(obj)}}), true};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::insert_or_assign(ConstIterator hint, const KeyType &key, T &&obj)
{
  if (NodeType* pos = m_tree.search(key))
  {
    pos->m_value.second = forward<T>(obj);
    return {pos, false};
  }
  return {m_tree.insert(NodeType{ValueType{key, forward<T>(obj)}}), true};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::insert_or_assign(ConstIterator hint, KeyType &&key, T &&obj)
{
  if (NodeType* pos = m_tree.search(forward<KeyType>(key)))
  {
    pos->m_value.second = forward<T>(obj);
    return {pos, false};
  }
  return {m_tree.insert(NodeType{ValueType{move(key), forward<T>(obj)}}), true};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename... Args>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::emplace(Args&&... args)
{
  NodeType node{ValueType(forward<Args>(args)...)};
  if (NodeType* pos = m_tree.search(node))
  {
    pos->m_value = move(node.m_value);
    return {pos, false};
  }
  return {m_tree.insert(move(node)), false};
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename... Args>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::emplace_hint(ConstIterator hint, Args&&... args)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename... Args>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::try_emplace(const KeyType &key, Args&&... args)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename... Args>
constexpr me::Pair<typename me::Map<Key, Value, Compare, Alloc>::Iterator, bool>
  me::Map<Key, Value, Compare, Alloc>::try_emplace(KeyType &&key, Args&&... args)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename... Args>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::try_emplace(ConstIterator hint, const Key &key, Args&&... args)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename... Args>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::try_emplace(ConstIterator hint, KeyType &&key, Args&&... args)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::erase(ConstIterator pos)
{
  return m_tree.make_iterator(m_tree.remove(*pos->m_pos));
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::Iterator
  me::Map<Key, Value, Compare, Alloc>::erase(ConstIterator first, ConstIterator last)
{
  // TODO: check if first and last is a valid range in *this
  for (; first < last - 1; first++)
    m_tree.remove(*first->m_pos);
  return m_tree.make_iterator(m_tree.remove(*last->m_pos));
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::SizeType
  me::Map<Key, Value, Compare, Alloc>::erase(const KeyType &key)
{
  return m_tree.remove(key) == nullptr ? 0 : 1;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr typename me::Map<Key, Value, Compare, Alloc>::SizeType
  me::Map<Key, Value, Compare, Alloc>::erase(T &&key)
{
  m_tree.remove(key);
  // TODO
  return 0;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::swap(Map &map)
{
  swap(m_tree, map.m_tree);
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::NodeType
  me::Map<Key, Value, Compare, Alloc>::extract(ConstIterator pos)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
constexpr typename me::Map<Key, Value, Compare, Alloc>::NodeType
  me::Map<Key, Value, Compare, Alloc>::extract(const KeyType &key)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr typename me::Map<Key, Value, Compare, Alloc>::NodeType
  me::Map<Key, Value, Compare, Alloc>::extract(T &&key)
{

}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::merge(Map<Key, Value, T, Alloc> &map)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::merge(Map<Key, Value, T, Alloc> &&map)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::merge(MultiMap<Key, Value, T, Alloc> &map)
{
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
constexpr void
  me::Map<Key, Value, Compare, Alloc>::merge(MultiMap<Key, Value, T, Alloc> &&map)
{
}
/* end class me::Map */

#endif
