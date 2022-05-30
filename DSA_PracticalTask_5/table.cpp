#include <windows.h>
#include "vote.h"
#include "tree.h"
#include "table.h"
#include "kv_pair.h"

template <typename V>
bool table<V>::index_of(const ULONGLONG &key, ULONGLONG &i)
{
   for (i = 0; i < _size; i++)
      if (data[i]->key == key)
         return true;

   return false;
}

template <typename V>
void table<V>::swap(const ULONGLONG i, const ULONGLONG j)
{
   kv_pair<V> *t = data[i];

   data[i] = data[j];
   data[j] = t;
}

template <typename V>
ULONGLONG table<V>::size()
{
   return _size;
}

template <typename V>
bool table<V>::empty()
{
   return _size == 0;
}

template <typename V>
bool table<V>::full()
{
   return _size == Nmax;
}


template<typename V>
void table<V>::sort_tree(ULONGLONG &n, ULONGLONG &m)
{
   tree t(data[0]->key);
   for (ULONGLONG i = 1; i < _size; i++)
      t.insert(new tree(data[i]->key), n, m);

   ULONGLONG c = 0;
   const auto get = [this, &c, &m] (ULONGLONG key)
   {
      ULONGLONG j = 0;
      this->index_of(key, j);

      this->swap(c++, j);
      m++;
   };

   t.for_each(get);
}

template<typename V>
void table<V>::sort_shell(ULONGLONG & n, ULONGLONG & m)
{
   for (int s = _size / 2; s > 0; s /= 2)
      for (int i = s; i < _size; i++)
         for (int j = i - s; j >= 0 && data[j]->key > data[j + s]->key; j -= s, n++, m++)
            swap(j, j + s);
}

template<typename V>
void table<V>::sort_quick(int l, int r, ULONGLONG &n, ULONGLONG &m)
{
   ULONGLONG v = data[(l + r) / 2]->key;
   int i = l, j = r;
   while (i <= j)
   {
      for ( ; data[i]->key < v; i++, n++);
      for ( ; data[j]->key > v; j--, n++);

      if (i <= j)
      {
         swap(i++, j--);
         m++;
      }
   }
   if (l < j)
      sort_quick(l, j, n, m);
   if (r > i)
      sort_quick(j + 1, r, n, m);
}


template <typename V>
void table<V>::insert(const ULONGLONG key, const V &value)
{
   if (_size == Nmax)
      return;

   data[_size++] = new kv_pair<V>(key, value);
}

template <typename V>
V *table<V>::find(const ULONGLONG key)
{
   ULONGLONG i = 0;
   return index_of(key, i) ? &data[i]->value : NULL;
}

template <typename V>
void table<V>::for_each(const function<void(kv_pair<V>)> &f)
{
   for (UCHAR i = 0; i < _size; i++)
      f(*data[i]);
}

template struct table<vote>;