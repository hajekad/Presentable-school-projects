Realizujte funkci, která najde všechny výskyty posloupnosti reprezentované spojovým seznamem „needle“ ve spojovém seznamu „hayStack“.

Funkce bude vracet dynamicky alokované pole ukazatelů na prvky seznamu „hayStack“, kde začíná hledaná posloupnost, poslední prvek pole bude vždy NULL (pokud program nenalezne žádný výskyt, vrací NULL). FIXME

Byl k tomu obrázek, v praxi šlo o to, že třeba spoják „hayStack“ měl prvky postupně 1-2-1-2-3-4-1-2-3-8 a „needle“ byl 1-2-3, a funkce by měla vracet pole, kde bude ukazatel na třetí prvek „hayStack“, ukazatel na sedmý prvek „hayStack“ a NULL.

typedef struct TNode {
  struct TNode * p_Next;
  int m_Value;
} TNODE;
 
/* Lze připsat i další metody */
 
TNODE ** search(TNODE * hayStack, TNODE * needle) {
  /* Sem napište svůj kód */
}