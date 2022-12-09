#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "hash.hpp"

#include <string>

// Double hashing to avoid collisions
struct HashFunction1 {
  int operator()(const std::string_view &s, int table_size) const {
    return cool_hash(s) % (table_size - 1);
  }
};
struct HashFunction2 {
  int operator()(const std::string_view &s, int table_size) const {
    return cool_hash(s) % (table_size + 1);
  }
};

template <class T, class THash1 = HashFunction1, class THash2 = HashFunction2>
class HashTable {
  static const int _default_size = 8;
  constexpr static const double _rehash_size = 0.75;
  struct Node {
    std::string_view key;
    T value;
    bool state;
    Node(const std::string_view &key_, const T &value_)
        : key{key_}, value{value_}, state{true} {}
  };
  Node **_arr;
  int _size;
  int _buffer_size;
  int _size_all_non_nullptr;

  void resize();
  void rehash();

public:
  HashTable();
  ~HashTable();

  bool insert(const std::string_view &key, const T &value,
              const THash1 &hash1 = THash1(), const THash2 &hash2 = THash2());

  bool remove(const std::string_view &key, const THash1 &hash1 = THash1(),
              const THash2 &hash2 = THash2());

  bool find(const T &value, const THash1 &hash1 = THash1(),
            const THash2 &hash2 = THash2());

  T get(const std::string_view &key, const THash1 &hash1 = THash1(),
        const THash2 &hash2 = THash2());

  std::size_t size() { return _size; }
};

template <class T, class THash1, class THash2>
void HashTable<T, THash1, THash2>::resize() {
  int past_buffer_size = _buffer_size;
  _buffer_size *= 2;
  _size_all_non_nullptr = 0;
  _size = 0;
  Node **arr2 = new Node *[_buffer_size];
  for (int i = 0; i < _buffer_size; ++i)
    arr2[i] = nullptr;
  std::swap(_arr, arr2);
  for (int i = 0; i < past_buffer_size; ++i) {
    if (arr2[i] && arr2[i]->state)
      insert(arr2[i]->key, arr2[i]->value);
  }
  for (int i = 0; i < past_buffer_size; ++i)
    if (arr2[i])
      delete arr2[i];
  delete[] arr2;
}

template <class T, class THash1, class THash2>
void HashTable<T, THash1, THash2>::rehash() {
  _size_all_non_nullptr = 0;
  _size = 0;
  Node **arr2 = new Node *[_buffer_size];
  for (int i = 0; i < _buffer_size; ++i)
    arr2[i] = nullptr;
  std::swap(_arr, arr2);
  for (int i = 0; i < _buffer_size; ++i) {
    if (arr2[i] && arr2[i]->state)
      insert(arr2[i]->key, arr2[i]->value);
  }
  for (int i = 0; i < _buffer_size; ++i)
    if (arr2[i])
      delete arr2[i];
  delete[] arr2;
}

template <class T, class THash1, class THash2>
HashTable<T, THash1, THash2>::HashTable() {
  _buffer_size = _default_size;
  _size = 0;
  _size_all_non_nullptr = 0;
  _arr = new Node *[_buffer_size];
  for (int i = 0; i < _buffer_size; ++i)
    _arr[i] = nullptr;
}

template <class T, class THash1, class THash2>
HashTable<T, THash1, THash2>::~HashTable() {
  for (int i = 0; i < _buffer_size; ++i)
    if (_arr[i])
      delete _arr[i];
  delete[] _arr;
}

template <class T, class THash1, class THash2>
bool HashTable<T, THash1, THash2>::insert(const std::string_view &key,
                                          const T &value, const THash1 &hash1,
                                          const THash2 &hash2) {
  if (_size + 1 > int(_rehash_size * _buffer_size))
    resize();
  else if (_size_all_non_nullptr > 2 * _size)
    rehash();
  int h1 = hash1(key, _buffer_size);
  int h2 = hash2(key, _buffer_size);
  int i = 0;
  int first_deleted = -1;
  while (_arr[h1] != nullptr && i < _buffer_size) {
    if (_arr[h1]->key == key && _arr[h1]->state)
      return false;
    if (!_arr[h1]->state && first_deleted == -1)
      first_deleted = h1;
    h1 = (h1 + h2) % _buffer_size;
    ++i;
  }
  if (first_deleted == -1) {
    _arr[h1] = new Node(key, value);
    ++_size_all_non_nullptr;
  } else {
    _arr[first_deleted]->value = value;
    _arr[first_deleted]->state = true;
  }
  ++_size;
  return true;
}

template <class T, class THash1, class THash2>
bool HashTable<T, THash1, THash2>::remove(const std::string_view &key,
                                          const THash1 &hash1,
                                          const THash2 &hash2) {
  int h1 = hash1(key, _buffer_size);
  int h2 = hash2(key, _buffer_size);
  int i = 0;
  while (_arr[h1] != nullptr && i < _buffer_size) {
    if (_arr[h1]->key == key && _arr[h1]->state) {
      _arr[h1]->state = false;
      --_size;
      return true;
    }
    h1 = (h1 + h2) % _buffer_size;
    ++i;
  }
  return false;
}

template <class T, class THash1, class THash2>
bool HashTable<T, THash1, THash2>::find(const T &value, const THash1 &hash1,
                                        const THash2 &hash2) {
  int h1 = hash1(value, _buffer_size);
  int h2 = hash2(value, _buffer_size);
  int i = 0;
  while (_arr[h1] != nullptr && i < _buffer_size) {
    if (_arr[h1]->value == value && _arr[h1]->state)
      return true;
    h1 = (h1 + h2) % _buffer_size;
    ++i;
  }
  return false;
}

template <class T, class THash1, class THash2>
T HashTable<T, THash1, THash2>::get(const std::string_view &key,
                                    const THash1 &hash1, const THash2 &hash2) {
  int h1 = hash1(key, _buffer_size);
  int h2 = hash2(key, _buffer_size);
  int i = 0;
  while (_arr[h1] != nullptr && i < _buffer_size) {
    if (_arr[h1]->key == key && _arr[h1]->state)
      return _arr[h1]->value;
    h1 = (h1 + h2) % _buffer_size;
    ++i;
  }
  return nullptr;
};

#endif
