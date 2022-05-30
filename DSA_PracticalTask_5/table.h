#ifndef H_TABLE
#define H_TABLE

#include <windows.h>
#include <functional>
#include "kv_pair.h"

using namespace std;

const ULONGLONG Nmax = 1000;

template <typename V>
struct table
{
   private:
   ULONGLONG _size = 0;
   kv_pair<V> *data[Nmax] = { };

   bool index_of(const ULONGLONG &key, ULONGLONG &i);
   void swap(const ULONGLONG i, const ULONGLONG j);

   public:
   ULONGLONG size();
   bool empty();
   bool full();


   void sort_tree(ULONGLONG &n, ULONGLONG &m);
   void sort_shell(ULONGLONG &n, ULONGLONG &m);
   void sort_quick(int l, int j, ULONGLONG &n, ULONGLONG &m);

   V *find(const ULONGLONG key);
   void insert(const ULONGLONG key, const V &value);

   void for_each(const function<void(kv_pair<V>)> &f);
};
#endif