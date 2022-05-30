#include <conio.h>
#include <stdio.h>
#include "vote.h"
#include "table.h"

enum COMMANDS
{
   TREE = 1,
   SHELL,
   QUICK
};

void print(table<vote> &t, ULONGLONG v_count);
void generate(FILE *f, ULONGLONG n);
ULONGLONG input(FILE *f, table<vote> &t);

int main()
{
   UINT inCp = GetConsoleCP(), outCp = GetConsoleOutputCP();
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);


   FILE *f = NULL;
   fopen_s(&f, "SPORT.txt", "w");

   generate(f, 120);
   fclose(f);

   table<vote> t;
   fopen_s(&f, "SPORT.txt", "r");

   ULONGLONG v_count = input(f, t);
   fclose(f);

   print(t, v_count);

   ULONGLONG n = 0, m = 0;

   bool repeat = true;
   char c = 0;
   do
   {
      repeat = false;
      printf_s("\nДоступные методы сортировки:\n"
               "[%d] Сортировка с использованием бинарного дерева;\n"
               "[%d] Сортировка методом Шелла;\n"
               "[%d] Быстрая сортровка.\n"
               "Укажите метод: ", TREE, SHELL, QUICK);

      scanf_s("\n%c", &c, (UINT) sizeof c);
      printf_s("\n");

      switch (atoi(&c))
      {
         case TREE:
            t.sort_tree(n, m);
            printf_s("Сортировка с использованием бинарного дерева:\n"); break;
         case SHELL:
            t.sort_shell(n, m);
            printf_s("Сортировка методом Шелла:\n"); break;
         case QUICK:
            t.sort_quick(0, t.size() - 1, n, m);
            printf_s("Быстрая сортровка:\n"); break;
         default:
            printf_s("Некорректный ввод.");
            repeat = true;
      }
   } while (repeat);

   print(t, v_count);

   printf_s("\nКол-во сравнений ключей элементов: %lli\n"
            "Кол-во перемещений элементов: %lli", n, m);

   SetConsoleCP(inCp);
   SetConsoleOutputCP(outCp);

   return 0 * _getch();
}

ULONGLONG input(FILE *f, table<vote> &t)
{
   char c = 0;
   ULONGLONG v_count = 0;

   while (fscanf_s(f, "%c", &c, (UINT)sizeof c) != EOF)
   {
      for (UCHAR i = 0; i < 4; i++)
      {
         vote v;
         fscanf_s(f, "%lli", &v.team);

         if (i == 1) v.last++;
         else
         {
            v.top++;
            if (i == 0) v.first++;
         }

         vote *fv = t.find(v.team);
         if (fv != NULL)
         {
            fv->top += v.top;
            fv->last += v.last;
            fv->first += v.first;
         }
         else t.insert(v.team, v);
      }
      v_count++;
   }
   return v_count;
}

void generate(FILE *f, ULONGLONG n)
{
   /*for (ULONGLONG i = n; i > 1; i--)
      fprintf_s(f, "\n%lli\t%lli\t%lli\t%lli", n, n - 1, i--, i);*/
   for (ULONGLONG i = 0; i < n; i++)
      fprintf_s(f, "\n%lli\t%lli\t%lli\t%lli", 0, 1, i++, i);

   /*if (n % 2 == 1)
      fprintf_s(f, "\n%lli\t%lli\t%lli\t%lli", n, n - 1, 1ull, n);*/
}

void print(table<vote> &t, ULONGLONG v_count)
{
   auto print_team_percents = [v_count] (kv_pair<vote> item)
   {
      float k = (float)100 / v_count; // Коэффициент, рассчитывающий процентное соотношение голосов за команду

      printf_s("%3lli | %7.2f %7.2f %7.2f\n", item.key, item.value.first * k,
               item.value.last * k,
               item.value.top * k);
   };

   printf_s("%2c %9s %7s %7s\n"
            "-----------------------------\n", '#', "First", "Last", "Top 3");
   t.for_each(print_team_percents);
}