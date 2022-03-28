<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat funkci (ne program, pouze funkci), která bude 
porovnávat dvojici řetězců, zda jsou tvořeny ze stejných slov.</p>

<p>Požadovaná funkce <tt class="hljs">sameWords</tt> má rozhraní podle ukázky níže:</p>
<pre class="hljs cpp"><span class="hljs-function"><span class="hljs-keyword">int</span> <span class="hljs-title">sameWords</span> <span class="hljs-params">( <span class="hljs-keyword">const</span> <span class="hljs-keyword">char</span> * a, <span class="hljs-keyword">const</span> <span class="hljs-keyword">char</span> * b )</span></span>;
</pre>
 
<p>Parametry jsou dva řetězce, které funkce porovná. Parametry jsou určené 
pouze pro čtení (<tt class="hljs cpp"><span class="hljs-keyword">const</span></tt>), funkce je nesmí měnit.</p>

<p>Návratovou hodnotou funkce je hodnota 1 (shoda) nebo 0 (neshoda).
Za shodu považujeme, pokud jsou oba řetězce tvořené stejnými slovy. 
Tedy pokud je každé slovo z prvního řetězce alespoň jednou obsaženo 
ve druhém řetězci a naopak. Při porovnávání slov nerozlišujeme malá 
a velká písmena.</p>

<p>Slova jsou tvořena znaky, pro které funkce <tt class="hljs cpp"><span class="hljs-built_in">isalpha</span></tt> vrací nenula. 
Ostatní znaky považujte za oddělovače slov.</p> 

<p>Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce
<tt class="hljs">sameWords</tt>. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou
z <tt class="hljs">sameWords</tt> volané. Funkce bude volaná z testovacího prostředí, je proto 
důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte 
kód z ukázky níže. V kódu chybí vyplnit funkci <tt class="hljs">sameWords</tt> (a případné další
podpůrné funkce). Ukázka obsahuje testovací funkci <tt class="hljs">main</tt>, uvedené hodnoty jsou
použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce   
<tt class="hljs">main</tt> jsou zabalené v bloku podmíněného překladu (<tt class="hljs cpp"><span class="hljs-meta">#<span class="hljs-meta-keyword">ifdef</span>/#<span class="hljs-meta-keyword">endif</span></span></tt>). Prosím, ponechte
bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad 
Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně    
spouštět a testovat. Při kompilaci na Progtestu funkce <tt class="hljs">main</tt> a vkládání  
hlavičkových souborů "zmizí", tedy nebude  kolidovat s hlavičkovými soubory a funkcí
<tt class="hljs">main</tt> testovacího prostředí.</p>

<p>Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen
dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i
velikost dostupné paměti. Časové limity jsou nastavené tak, aby rozumná
implementace naivního algoritmu prošla všemi povinnými testy. Řešení fungující
v povinných testech může získat nominálních 100% bodů. Bonusový test
vyžaduje časově efektivní výpočet i pro dlouhé řetězce obsahující mnoho slov.</p>

<p>Pro implementaci musíte použít C řetězce. C++ řetězce (<tt class="hljs cpp"><span class="hljs-built_in">std</span>::<span class="hljs-built_in">string</span></tt>) 
a STL jsou zakázané, jejich použití povede k chybě při kompilaci.</p>

<p>V přiloženém archivu naleznete základ implementace a několik ukázkových testů.</p>

<p>Program, který projde všemi povinnými a nepovinnými testy na 100 %, může být použit pro code review. 
(Pro code review není potřeba projít bonusovými testy).</p>

</td>