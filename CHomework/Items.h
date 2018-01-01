#ifndef ITEMS_H
#define ITEMS_H

#pragma warning(disable : 4996)

#define CAPACITY 50
#define HEAD 0
#define FIND_ONLY 0
#define FIND_AND_PRINT 1

typedef struct ItemsInfo
{
    char Name[50];
    double Price;
}Item;

void InfoInit(Item *Items[]);
int InfoSearch(Item *Items[], const char *str, unsigned Flag);
void InfoInsert(Item *Items[], const char *str, double Price);
void InfoChange(Item *Items[], const char *str);
void InfoDelete(Item *Items[], const char *str);
void InfoFlush(Item *Items[]);
inline void StrReplace(char *Destination, const char *Source);
void OutputAll(Item *Items[]);

#endif // !ITEMS_H
