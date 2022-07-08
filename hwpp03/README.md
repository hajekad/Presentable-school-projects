<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat třídu, která bude reprezentovat datum.
Reprezentovaná data budou odpovídat pravidlům Gregoriánského kalendáře,
je požadováno, aby šlo reprezentovat data nejméně v rozmezí let 
2000 až 2030.</p>

<p>Třída <tt class="hljs">CDate</tt> musí splňovat následující rozhraní:</p>

<ul>
 <li>konstruktor s parametry (y,m,d) vytvoří novou instanci třídy s datem 
  nastaveným podle předaných hodnot. Konstruktor musí kontrolovat, zda zadané 
  datum je platné. Pokud platné není, musí vyvolat výjimku <tt class="hljs">InvalidDateException</tt>,</li>

 <li>operátorem + lze k instanci <tt class="hljs">CDate</tt> přičíst celé číslo a tím se posunout vpřed o 
  zadaný počet dní (vzad pro záporné číslo),</li>

 <li>operátorem - lze od instance <tt class="hljs">CDate</tt> odečíst celé číslo a tím se posunout vzad o 
  zadaný počet dní (vpřed pro záporné číslo),</li>
      
 <li>operátorem - lze od sebe odečíst dvě instance <tt class="hljs">CDate</tt> a tím získat počet dní mezi 
  těmito dvěma daty,</li>

 <li>operátory ++ a -- v prefixové a v postfixové notaci lze zvyšovat/snižovat datum o 1 den,
  operátory mají obvyklé chování,</li>

 <li>operátory ==, !=, &gt;, &gt;=, &lt; a &lt;= lze porovnávat dvojici instancí <tt class="hljs">CDate</tt>,
  v této relaci budou data v budoucnosti větší než data v minulosti,</li>

 <li>operátorem &lt;&lt; lze zobrazit instanci <tt class="hljs">CDate</tt> v zadaném streamu. Při zobrazování 
  se používá ISO formát (%Y-%m-%d, tedy např. 2000-01-31). V povinných testech bude vždy použit 
  tento implicitní formát. Bonusové testy požadují implementaci manipulátoru <tt class="hljs">date_format</tt>, 
  kterým lze formát řídit.</li>

 <li>operátorem &gt;&gt; lze přečíst instanci <tt class="hljs">CDate</tt> ze zadaného streamu. V povinných testech 
  je na vstupu očekáváno datum v ISO formátu %Y-%m-%d. Pokud se nepodaří datum načíst (formát, 
  neplatné datum, ...), operátor zajistí nastavení fail bitu a ponechá původní obsah instance <tt class="hljs">CDate</tt>. 
  Stejně jako výstupní operátor, i vstup lze řídit pomocí manipulátoru <tt class="hljs">date_format</tt>, 
  tato možnost je požadovaná v bonusovém testu.</li>
</ul>
    
<hr>

<p>Odevzdávejte soubor, který obsahuje implementovanou třídu <tt class="hljs">CDate</tt> 
a případné další podpůrné třídy a funkce. Třída musí splňovat popsané veřejné rozhraní 
- pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. 
Do třídy si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. 
Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice 
metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline 
nebo odděleně. Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a 
funkci <tt class="hljs">main</tt> (funkce <tt class="hljs">main</tt> a vkládání hlavičkových souborů může zůstat, 
ale pouze obalené direktivami podmíněného překladu jako v ukázce níže).</p>


<p>Tato úloha není zaměřená na rychlost. Vzhledem k rozsahu testovaných hodnot lze při 
troše obezřetnosti použít knihovní volání pro konverze data (<tt class="hljs">ctime</tt>).</p>

<p>Úloha má povinnou a bonusovou část. V povinné části není použit manipulátor 
<tt class="hljs">date_format</tt>, tedy je testovaný pouze výchozí formát data (%Y-%m-%d). 
V bonusové části je navíc požadováno, aby tento manipulátor správně fungoval.
Pokud se rozhodnete bonusovou část vynechat, ponechte ve Vašem zdrojovém kódu 
dodanou "dummy" implementaci manipulátoru (jinak kód nepůjde přeložit).</p>


<p>Bonusové testy používají Vámi dodaný manipulátor <tt class="hljs">date_format</tt>, který pomocí řetězce 
popisuje požadované konverze. Formát může obsahovat:
</p><ul>
 <li>znaky kromě znaků procento - na vstupu je takový znak na daném místě očekáván a je přeskočen. 
    Není-li na vstupu znak nalezen, je to považováno za chybu. U výstupní konverze je takový znak 
    přidán k výstupu. V ISO formátu %Y-%m-%d jsou takovým znakem pomlčky.</li>
 <li>Znak procento uvozuje den (%d), měsíc (%m) nebo rok (%Y), který se na daném místě vyskytuje 
    v řetězci data. Pro vstup se očekává celé číslo určující den/měsíc/rok, pro výstupní konverzi 
    to znamená, že se k výstupu připojí desítková hodnota dne/měsíce/roku, zleva doplněná nulami.</li>
 <li>Znak procento následovaný znakem jiným než Y, m nebo d, (např. %x, %%, ...) udává, 
    že na daném místě řetězce data se vyskytuje/má zobrazit takový znak (tedy v příkladu x, %, 
    ...). Tedy ISO formát data by šel s takovou konvencí ekvivalentně přepsat jako %Y%-%m%-%d.</li>
</ul><p></p>

<p>Je-li manipulátor <tt class="hljs">date_format</tt> jednou zaslaný do streamu, platí tento formát pro všechny 
další konverze až do případné další změny formátu (tedy chová se podobně jako manipulátory <tt class="hljs">hex</tt>,
...). Při implementaci mějte na paměti, že v každém streamu může být nastaven jiný manipulátor.</p>

<p>Formát na výstupu může být libovolný (extrém je formát "hello kitty" v ukázce). Vstupní formát má 
omezení, aby šlo vstup jednoznačně zpracovat: den, měsíc a rok (%d, %m a %Y) musí být ve formátu uveden a 
to právě jednou. V ukázce je vidět, že vstupní formáty s chybějící či nadbytečnou konverzí vedou k chybě 
při následném načítání.</p>

<p>Poznámky:</p>

<ul>
 <li>V příloze naleznete základ implementace, ukázky běhu a ukázky běhu pro bonusový test.</li>
 <li>Podle zvolené implementace může hrát roli, že některé dny nemají 24 hodin.</li>
 <li>Pokud budete implementovat manipulátor, nastudujte si metody <tt class="hljs">xalloc</tt>, 
   <tt class="hljs">register_callback</tt>, <tt class="hljs">pword</tt> a <tt class="hljs">iword</tt> ve třídě <tt class="hljs">ios_base</tt>.</li>
 <li>Při řešení úlohy narazíte na problematiku přestupných roků. Rok je považován za přestupný, 
   pokud je dělitelný 4 (např. 2020, 2024, ...). Výjimku mají roky dělitelné 100, které <b>nejsou</b> 
   přestupné (např. roky 1900 a 2100 nebyly/nebudou přestupné). Výjimku z této výjimky mají roky dělitelné 400, 
   které naopak jsou přestupné (např. rok 2000 byl přestupný). Úlohu však zjednodušuje to, že jsou 
   zadávané roky pouze z omezeného rozmezí 2000 - 2030.</li>
 <li>Při načítání dne, měsíce a roku ze streamu byste měli kontrolovat, že načtené číslo má správný počet cifer 
   (2 pro den a měsíc, 4 pro rok). V základních testech to kontrolovat nemusíte (geneované hodnoty dnů a měsíců 
   mají případné úvodní nuly). V bonusovém testu je potřeba to testovat pečlivěji, jinak nemusí fungovat načítání 
   v obecném formátu. V ukázkovém běhu je na to testovací príklad.</li>
 <li>Řešení úlohy je v základní verzi velmi krátké a přímočaré. Takové řešení úlohy proto <b>nelze</b> 
   použít pro code review. Na code review lze tentokrát odevzdat pouze řešení, které bez chyb prošlo všemi 
   testy včetně testů bonusových.</li>
</ul>
</td>