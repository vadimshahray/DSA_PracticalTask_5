#include "tree.h"

void tree::insert(tree *t, ULONGLONG &n, ULONGLONG &m)
{
   if (!t) return;

   if (t->elem < this->elem)
      if (this->left)
         this->left->insert(t, ++n, m);
      else
         this->left = t;
   else
      if (this->right)
         this->right->insert(t, ++n, m);
      else
         this->right = t;
}

void tree::for_each(const function<void(ULONGLONG e)> &f)
{
   if (this->left)
      this->left->for_each(f);

   f(elem);

   if (this->right)
      this->right->for_each(f);
}