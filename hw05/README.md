<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je vytvořit program, který bude zpracovávat provedené nákupy a analyzovat prodejnost zboží.</p>

<p>Předpokládáme že zaznamenáváme jednotlivé prodeje zboží. Zajímá nás zejména to zboží, které se 
prodává nejvíce. Proto program bude umět vypočítat N druhů zboží, kterého se prodalo nejvíce kusů. 
Hodnota N (počet druhů zboží, které se prodává nejvíce) bude zadán na vstupu programu jako první údaj.</p>

<p>Zboží je identifikováno svým jménem - řetězcem. Jméno musí být nejvýše 99 znaků dlouhé a neobsahuje 
bílé znaky. Na vstupu se o prodeji zboží program dozví pomocí zadání <tt class="hljs">+ jméno-zboží</tt>. Na vstupu 
dále mohou být příkazy, kterými lze zobrazit analýzu prodeje. Konkrétně:</p>

<ul>
 <li>příkaz # zobrazí přehled N druhů zboží, kterého se dosud prodalo nejvíce. Výpis bude mít podobu podle 
   ukázky níže, pro každý druh zboží bude uvedeno jméno a počet prodaných kusů. Dále bude zobrazen i celkový 
   součet (součty prodaných kusů pro zobrazené nejvíce prodávané zboží).</li>
 <li>příkaz ? zobrazí pouze celkový součet.</li>
</ul>


<p>Fungování programu se trochu komplikuje pro vstupy, kde se pro dva a více různých druhů zboží prodal 
stejný počet kusů:</p>

<ul>
 <li>jednodušší situace je vidět v první ukázce. Ve výpisu jsou 4 kusy prodaných vajíček a mouky. Proto 
   toto zboží má shodně 2. až 3. místo ve výpisu a odpovídá tomu i formát výpisu. Zároveň tím není určeno 
   přesné pořadí ve výpisu. Testovací prostředí proto akceptuje obě (všechny) možnosti, tedy zde by konkrétně 
   bylo správně jak:
   <pre class="hljs">   1. Milk, 5x
   2.-3. Eggs, 4x
   2.-3. Flour, 4x
   4. Beer, 3x
   </pre>
   tak i:
   <pre class="hljs">   1. Milk, 5x
   2.-3. Flour, 4x
   2.-3. Eggs, 4x
   4. Beer, 3x
   </pre></li>
   
 <li>Komplikovanější situace je vidět v druhé ukázce. Bylo zadáno, že se mají sledovat N=3 nejvíce prodávané 
   druhy zboží, ale je vidět, že vypsaný seznam je někdy i delší, například u výstupu:
   
   <pre class="hljs">   1.-4. Black_tea, 1x
   1.-4. Caffeine, 1x
   1.-4. C/C++_for_dummies, 1x
   1.-4. Introduction_to_Algorithms, 1x
   </pre>
   
   nebo:
   
   <pre class="hljs">   1.-2. Black_tea, 2x
   1.-2. Caffeine, 2x
   3.-5. C/C++_for_dummies, 1x
   3.-5. Energy_drink, 1x
   3.-5. Introduction_to_Algorithms, 1x
   </pre>
   
   Delší bude seznam v situaci, kdy by seznam N nejprodávanějších druhů zboží měl skončit a odříznout další druhy zboží, 
   které mají stejnou prodejnost jako jiné zboží již zobrazené.</li>
</ul>
   

<p>Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení.
Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu 
považujte:</p>

<ul>
 <li>sledovaný počet druhů zboží N je neplatný (není celé číslo, je nulový nebo záporný),</li>
 <li>není zadaný žádný známý příkaz (+, ?, #),</li>
 <li>název zboží je neplatný (chybí, má 100 nebo více znaků).</li>
</ul>

<b>Ukázka práce programu:</b><br>
<hr>
<pre class="hljs"><b>Pocet sledovanych:</b>
4
<b>Pozadavky:</b>
+ Fruits
+ Milk
+ Milk
+ Sugar
+ Butter
+ Beer
+ Vegetables
+ Milk
+ Beer
+ Milk
+ Beer
+ Sugar
+ Eggs
+ Milk
+ Eggs
+ Eggs
+ Eggs
#
<b>1. Milk, 5x</b>
<b>2. Eggs, 4x</b>
<b>3. Beer, 3x</b>
<b>4. Sugar, 2x</b>
<b>Nejprodavanejsi zbozi: prodano 14 kusu</b>
+ Flour
+ Flour
+ Flour
+ Flour
#
<b>1. Milk, 5x</b>
<b>2.-3. Eggs, 4x</b>
<b>2.-3. Flour, 4x</b>
<b>4. Beer, 3x</b>
<b>Nejprodavanejsi zbozi: prodano 16 kusu</b>
+ Flour
?
<b>Nejprodavanejsi zbozi: prodano 17 kusu</b>
+ Flour
#
<b>1. Flour, 6x</b>
<b>2. Milk, 5x</b>
<b>3. Eggs, 4x</b>
<b>4. Beer, 3x</b>
<b>Nejprodavanejsi zbozi: prodano 18 kusu</b>
</pre>
<hr>
<pre class="hljs"><b>Pocet sledovanych:</b>
3
<b>Pozadavky:</b>
+ Introduction_to_Algorithms
+ Black_tea
#
<b>1.-2. Black_tea, 1x</b>
<b>1.-2. Introduction_to_Algorithms, 1x</b>
<b>Nejprodavanejsi zbozi: prodano 2 kusu</b>
+ Caffeine
?
<b>Nejprodavanejsi zbozi: prodano 3 kusu</b>
+ C/C++_for_dummies
#
<b>1.-4. Black_tea, 1x</b>
<b>1.-4. Caffeine, 1x</b>
<b>1.-4. C/C++_for_dummies, 1x</b>
<b>1.-4. Introduction_to_Algorithms, 1x</b>
<b>Nejprodavanejsi zbozi: prodano 4 kusu</b>
+ Black_tea
#
<b>1. Black_tea, 2x</b>
<b>2.-4. Caffeine, 1x</b>
<b>2.-4. C/C++_for_dummies, 1x</b>
<b>2.-4. Introduction_to_Algorithms, 1x</b>
<b>Nejprodavanejsi zbozi: prodano 5 kusu</b>
+ Energy_drink
+ Caffeine
#
<b>1.-2. Black_tea, 2x</b>
<b>1.-2. Caffeine, 2x</b>
<b>3.-5. C/C++_for_dummies, 1x</b>
<b>3.-5. Energy_drink, 1x</b>
<b>3.-5. Introduction_to_Algorithms, 1x</b>
<b>Nejprodavanejsi zbozi: prodano 7 kusu</b>
?
<b>Nejprodavanejsi zbozi: prodano 7 kusu</b>
+ Energy_drink
?
<b>Nejprodavanejsi zbozi: prodano 6 kusu</b>
+ Energy_drink
?
<b>Nejprodavanejsi zbozi: prodano 7 kusu</b>
+ Caffeine
?
<b>Nejprodavanejsi zbozi: prodano 8 kusu</b>
+ Energy_drink
+ Energy_drink
#
<b>1. Energy_drink, 5x</b>
<b>2. Caffeine, 3x</b>
<b>3. Black_tea, 2x</b>
<b>Nejprodavanejsi zbozi: prodano 10 kusu</b>
+ C/C++_for_dummies
#
<b>1. Energy_drink, 5x</b>
<b>2. Caffeine, 3x</b>
<b>3.-4. C/C++_for_dummies, 2x</b>
<b>3.-4. Black_tea, 2x</b>
<b>Nejprodavanejsi zbozi: prodano 12 kusu</b>
</pre>
<hr>
<pre class="hljs"><b>Pocet sledovanych:</b>
3
<b>Pozadavky:</b>
* Avoiding_invalid_input_3-rd_edition
<b>Nespravny vstup.</b>
</pre>
<hr>

<b>Poznámky:</b>
<ul>
 <li>Ukázkové běhy zachycují očekávané výpisy Vašeho programu (tučné písmo) a vstupy zadané 
     uživatelem (základní písmo). Zvýraznění tučným písmem je použité pouze zde na stránce zadání, 
     aby byl výpis lépe čitelný. Váš program má za úkol pouze zobrazit text bez zvýrazňování 
     (bez HTML markupu).</li>
     
 <li>Znak odřádkování (\n) je i za poslední řádkou výstupu (i za případným chybovým hlášením).</li>

 <li>Počet druhů zboží ani délka vstupu není explicitně omezená. Pro ukládání vstupu / ukládání 
     jednotlivých druhů zboží nelze použít statickou alokaci.</li>
     
 <li>Název zboží má délku omezenou na 99 znaků. Tedy samotný název lze (a je vhodné) uložit do 
     staticky alokovaného pole znaků.</li>    

 <li>Pro reprezentaci zboží je vhodné použít struktury sdružující např. název zboží a počet prodaných kusů.</li>

 <li>Odevzdaný program je testován více testy se zvyšující se náročností. Nejprve je kontrolovaná 
     správnost řešení, dále se kontroluje správnost práce s polem a dynamická alokace paměti (test 
     paměťovým debuggerem) a nakonec efektivita řešení.</li>
 
 <li>Základní řešení nemusí být efektivní, postačuje naivní algoritmus Takové řešení projde povinnými 
     testy a některými nepovinnými testy. Bude hodnoceno maximálně 100 % bodů.</li>
     
 <li>První bonusový test kontroluje efektivitu odevzdaného programu. Jsou zadávané dlouhé vstupy 
     s mnoha různými druhy zboží. Zároveň ale hodnota N bude relativně nízká. Naivní algoritmus není 
     dostatečně efektivní a nezvládne výpočet v nastaveném časovém limitu.</li>
     
 <li>Druhý bonusový test dále kontroluje efektivitu použitého algoritmu. Jsou zadávané dlouhé vstupy, 
     s mnoha různými druhy zboží. Dále je zadávaná vysoká hodnota N. Můžete předpokládat, že na vstupu bude 
     mnoho příkazů + a ?, ale významně méně příkazů # (dlouhé výpisy by výpočet hodně zdržovaly).</li>
     
 <li>Program, který projde všemi povinnými a nepovinnými testy na 100 %, může být použit pro code review. 
     (Pro code review není potřeba projít bonusovými testy).</li>
     
 <li>Pro vyřešeni používejte konstrukce jazyka C. Nepoužívejte datové struktury z C++ - jsou potlačené.</li>
</ul>

</td>