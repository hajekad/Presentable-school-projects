Úkolem bylo realizovat funkci getSeed(), která najde vzor (seed), opakováním kterého lze vytvořit celou vstupní posloupnost, která je uložena v jednosměrném spojovém seznamu. Vstupní parametr byl spojový seznam, který bylo možno číst, nikoliv však měnit a výstupem funkce má být nový spojový seznam s nejkratším takovým vzorem.

abcabdabcabd - vzor abcabd
123456789 - vzor 123456789
(1→2→3→4→1→2→3→4) - vzor (1→2→3→4)
(a→b→c→d→e→f→g→a→b→c→d→e→f→G) - vzor (a→b→c→d→e→f→g→a→b→c→d→e→f→G)
(a→a→a→a→a→a→a→a) - vzor (a)
typedef struct TItem {
    struct TItem * m_Next;
    char m_Val;
} TITEM;
 
TITEM * createItem (char val, TITEM * next) {
    TITEM * n = malloc(sizeof (*n));
    n->m_Val = val;
    n->m_Next = next;
    return n;
}
 
void deleteList (TITEM * list) {
    while (list) {
        TITEM * tmp = list->m_Next;
        free(list);
        list = tmp;
    }
}
 
TITEM * getSeed (TITEM * x) {
// TODO
}