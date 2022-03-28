Jsou zadané 2 spojové seznamy. A a B. Oba spojové seznamy reprezentují nějaký polynom. Vaším cílem je oba spojové seznamy sečíst a z jejich součtu vytvořit nový spojový seznam. Spojový seznam obsahuje 2 prvky. Int, který reprezentuje mocninu (m_moc) a základ té mocniny (m_num) a také m_Next (Odkaz na následující prvek).

Vytvořte tedy funkci, která má za parametry 2 spojové seznamy a jejím výstupem budou sečtené polynomy jako spojový seznam. (Funkce na free a základní struct implementace byla zahrnuta v zadání (stejně tak asserty), to už nemám)

Vstupní spojové seznamy musí splnit podmínky:

- Polynomy musí být řazeny dle jejich mocnin vzestupně. Pokud toto nebude splněno vraťte NULL. (Nevracejte žádný spojový seznam)

- Pokud výsledný polynom je 0 (Všechny se odečtou např.), tak vraťte spojový seznam realizován jedním prvkem, kde m_num = 0 a m_moc = 0

- Oba spojové seznamy nesmí být prázdné, jestliže nějaký je vraťte NULL