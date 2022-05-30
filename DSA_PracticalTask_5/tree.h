#ifndef H_TREE
#define H_TREE

#include <stdio.h>
#include <windows.h>
#include <functional>

using namespace std;

struct tree
{
   tree(ULONGLONG _elem = 0, tree *_left = NULL, tree *_right = NULL) :
      elem(_elem), left(_left), right(_right) { }

   ULONGLONG elem;
   tree *left, *right;

   void insert(tree *t, ULONGLONG &n, ULONGLONG &m);
   void for_each(const function<void(ULONGLONG e)> &f);
};
#endif