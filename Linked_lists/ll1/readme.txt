Vaším úkolem je realizovat funkci shiftLeft.

TNODE * shiftLeft ( TNODE * a, unsigned int shift );
Funkce shiftLeft si bere v parametru číslo v šestnáctkové soustavě reprezentované jako spojový seznam. Stejně jako v předchozích úlohách je číslo uloženo pozpátku, tudíž hlavou spojového seznamu je nejnižší řád. Např.:

3 -> 2 -> 1 -> NULL <=> 123(hex) <=> 291(dec)
Vaše funkce musí číslo bitově posunout o shift pozic doleva (parametr). Výsledek pak vrátí jako odkaz na hlavu nově vytvořeného spojového seznamu. Původní číslo se nesmí změnit. Ukázka práce programu:

123(hex) << 1 = 246(hex)
1af(hex) << 3 = d78(hex)
Funkce musí zároveň správně detekovat nesprávná čísla. Taková čísla:

- jsou NULL
- číslice není v rozmezí '0-9' nebo 'a-f'
- obsahuje přebytečné nuly

V takovém případě funkce vrací NULL.

Jednoduché asserty na procvičení:

/* Program predpoklada strukturu TNode s atributy m_Digit (char) a m_Next (struct TNode* )
 * a funkci createNode, ktera priradi novy prvek NA ZACATEK spojoveho seznamu. Prvni sada
 * createNode tedy vytvori strukturu 3 -> 2 -> 1 -> NULL. Cisla jsou opet reprezentovana 
 * pozpatku, takze tohle odpovida cislu 123. Funkce deleteList uvolni veskerou pamet, kterou
 * spojovy seznam vyuziva, na jeji realizaci tedy prilis nezalezi.
 */