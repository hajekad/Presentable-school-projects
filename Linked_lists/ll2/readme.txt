Úkolem je implementovat 2 funkce, TITEM * StringToList ( const char* ) a void FreeList ( TITEM * ).

Je zadaná struktura

typedef struct TItem {
 struct TItem * m_Next;
  char *m_Word;
}TITEM;
 
TITEM* StringToList( const char* string )
{
/* TO DO */
}
 
void FreeList ( TITEM* List )
{
/* TO DO */
}
Funkce StringToList dostane parametrem string, který rozdělí na jednotlivá slova, která uloží do spojového seznamu struktur TITEM. Vrací tento spojový seznam, je potřeba alokovat pamět a zkopirovat data. V nápovědě bylo ještě, že máme pro odhalení bílých znaků mezi slovy použít funkci isspace.

Funkce FreeList uvolní paměť alokovanou funkcí StringToList.

Vzorová data byl zdrojový soubor s asserty a podmíněným spouštěním.