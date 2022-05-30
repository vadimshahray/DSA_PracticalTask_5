#ifndef H_KV_PAIR
#define H_KV_PAIR

#include <windows.h>

template <typename V>
struct kv_pair
{
   kv_pair(ULONGLONG _key, V _value) : key(_key), value(_value) { }

   V value;
   const ULONGLONG key;
};
#endif