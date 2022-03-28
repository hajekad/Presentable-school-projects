<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je vytvořit program, který bude vyhledávat zkratky (a tím vzdá hold nesmrtelné 
písni <a href="https://lyricstranslate.com/en/ivan-ml%C3%A1dek-zkratky-lyrics.html">Ivana Mládka</a>
- nebo snad <a href="https://www.youtube.com/watch?v=HRG-05mnwjg">Zdeňka Svěráka</a>).</p>

<p>Program dostane hledanou zkratku -- např. <tt class="hljs">FIT</tt>. Zkratka je tvořena 
písmeny velké abecedy (A-Z). Po zadání zkratky následují zadání problémů 
s vyhledáním této zkratky. Zadání problému má dvě podoby:</p>
<pre class="hljs cpp">? N <span class="hljs-string">"text"</span>
nebo 
# N <span class="hljs-string">"text"</span>
</pre>

<p>V uvozovkách může být zadaný libovolný text (neobsahuje odřádkování a uvozovky) a 
<tt class="hljs">N</tt> je celé číslo. Program se pokusí vyhledat zadanou zkratku v textu. Při 
vyhledávání musí v textu identifikovat písmena zkratky (nerozlišujeme malá/velká písmena), 
pořadí písmen v textu musí odpovídat pořadí písmen ve zkratce a do každého slova v 
textu lze umístit nejvýše <tt class="hljs">N</tt> písmen zkratky. Tedy například pro zkratku 
<tt class="hljs">FIT</tt> a vstup:</p>

<pre class="hljs cpp"># <span class="hljs-number">1</span> <span class="hljs-string">"Faculty of Information Technology"</span>
</pre>
lze vybrat zkratku např. těmito způsoby:
<pre class="hljs cpp"><span class="hljs-string">"</span><span style="color: red"><span class="hljs-string">F</span></span><span class="hljs-string">aculty of </span><span style="color: red"><span class="hljs-string">I</span></span><span class="hljs-string">nformation </span><span style="color: red"><span class="hljs-string">T</span></span><span class="hljs-string">echnology"</span>
<span class="hljs-string">"faculty o</span><span style="color: red"><span class="hljs-string">F</span></span><span class="hljs-string"> </span><span style="color: red"><span class="hljs-string">I</span></span><span class="hljs-string">nformation </span><span style="color: red"><span class="hljs-string">T</span></span><span class="hljs-string">echnology"</span>
<span class="hljs-string">"</span><span style="color: red"><span class="hljs-string">F</span></span><span class="hljs-string">aculty of informat</span><span style="color: red"><span class="hljs-string">I</span></span><span class="hljs-string">on </span><span style="color: red"><span class="hljs-string">T</span></span><span class="hljs-string">echnology"</span>
...
</pre>
ale ne například takto:
<pre class="hljs cpp"><span class="hljs-string">"facul</span><span style="color: red"><span class="hljs-string">T</span></span><span class="hljs-string">y o</span><span style="color: red"><span class="hljs-string">F</span></span><span class="hljs-string"> </span><span style="color: red"><span class="hljs-string">I</span></span><span class="hljs-string">nformation technology"</span>
<span class="hljs-string">"</span><span style="color: red"><span class="hljs-string">F</span></span><span class="hljs-string">aculty of </span><span style="color: red"><span class="hljs-string">I</span></span><span class="hljs-string">nforma</span><span style="color: red"><span class="hljs-string">T</span></span><span class="hljs-string">ion technology"</span>
</pre>
<p>v prvním případě není zachované pořadí písmen, ve druhém pak vybíráme 2 písmena ze slova <tt class="hljs">Information</tt>, ale limit 
je <tt class="hljs">N=1</tt> písmeno.</p>

<p>Obecně lze zadanou zkratku nalézt v zadaném textu několika různými způsoby. Úkolem programu je vypočítat, kolika různými způsoby 
lze zkratku nalézt. Pokud je zadán problém ve tvaru:
</p><pre class="hljs cpp">? N <span class="hljs-string">"text"</span>
</pre>
očekává se, že program vyhledá zkratky podle popsaných pravidel a vypíše všechny nalezené možnosti. Ve výpisu program 
zdůrazní písmena ze zkratky (zobrazí je jako velká) a ostatní písmena z textu zobrazí jako malá. Nakonec připojí informaci 
o počtu nalezených možností.<p></p>

<p>Pokud je zadán problém ve tvaru:
</p><pre class="hljs cpp"># N <span class="hljs-string">"text"</span>
</pre>
pak program opět spočte možnosti, ale nevypisuje pozice jednotlivých nalezených zkratek. Pouze vypíše 
počet nalezených možností, jak lze zkratky do textu umístit. Navíc tyto počty určí pro limit 1, 2, 3, 
..., N písmen zkratky maximálně umístěných do jednoho slova textu.<p></p>

<p>Vstup je zpracováván po řádkách. Na první řádce je zadaná hledaná zkratka, řádka nesmí obsahovat žádné 
další znaky navíc. Zkratka musí být zadaná velkými písmeny. Její délka není obecně omezená. Po zadání zkratky 
následuje zadání jednotlivých problémů -- textů k hledání. Formát problému je popsaný výše. Každý problém musí být 
zadán na jedné řádce. Program zpracovává problémy ze vstupu, dokud nedosáhne konce vstupu (EOF).</p>

<p>Výstupem programu je text s nalezenými pozicemi písmen zkratky a informace o počtu možností, kterými lze 
zkratku to textu umístit. Při výpisu textu s pozicemi písmen zkratky nezáleží na pořadí vypisovaných řádek. 
Formátování výstupu je zřejmé z ukázky níže.</p>

<p>Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení.
Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu 
považujte:</p>

<ul>
 <li>první řádka neobsahovala zkratku, zkratka byla prázdná (nulové délky) nebo se ve zkratce objevily jiné znaky než velká písmena,</li>
 <li>nebyl rozpoznán problém k vyřešení (# a ?),</li>
 <li>číslo <tt class="hljs">N</tt> v zadání problému chybí, není platné, je nulové nebo záporné,</li>
 <li>prohledávaný text není umístěn do uvozovek nebo nějaká uvozovka chybí.</li>
</ul>

<b>Ukázka práce programu:</b><br>
<hr>
<pre class="hljs cpp"><b>Zkratka:</b>
FIT
<b>Problemy:</b>
? <span class="hljs-number">1</span> <span class="hljs-string">"Faculty of Information Technology"</span>
<b><span class="hljs-string">"Faculty of Information Technology"</span></b>
<b><span class="hljs-string">"Faculty of informatIon Technology"</span></b>
<b><span class="hljs-string">"faculty oF Information Technology"</span></b>
<b><span class="hljs-string">"faculty oF informatIon Technology"</span></b>
<b>&gt; <span class="hljs-number">4</span></b>
? <span class="hljs-number">2</span> <span class="hljs-string">"Faculty of Information Technology"</span>
<b><span class="hljs-string">"Faculty of InformaTion technology"</span></b>
<b><span class="hljs-string">"Faculty of Information Technology"</span></b>
<b><span class="hljs-string">"Faculty of informatIon Technology"</span></b>
<b><span class="hljs-string">"faculty oF InformaTion technology"</span></b>
<b><span class="hljs-string">"faculty oF Information Technology"</span></b>
<b><span class="hljs-string">"faculty oF informatIon Technology"</span></b>
<b><span class="hljs-string">"faculty of inFormatIon Technology"</span></b>
<b>&gt; <span class="hljs-number">7</span></b>
? <span class="hljs-number">2</span> <span class="hljs-string">"FIT"</span>
<b>&gt; <span class="hljs-number">0</span></b>
? <span class="hljs-number">3</span> <span class="hljs-string">"FIT"</span>
<b><span class="hljs-string">"FIT"</span></b>
<b>&gt; <span class="hljs-number">1</span></b>
? <span class="hljs-number">2</span>   <span class="hljs-string">"Fibonacci   test"</span>  
<b><span class="hljs-string">"FIbonacci   Test"</span></b>
<b><span class="hljs-string">"FIbonacci   tesT"</span></b>
<b><span class="hljs-string">"FibonaccI   Test"</span></b>
<b><span class="hljs-string">"FibonaccI   tesT"</span></b>
<b>&gt; <span class="hljs-number">4</span></b>
? <span class="hljs-number">2</span>   <span class="hljs-string">"  Fibonacci   test   "</span>  
<b><span class="hljs-string">"  FIbonacci   Test   "</span></b>
<b><span class="hljs-string">"  FIbonacci   tesT   "</span></b>
<b><span class="hljs-string">"  FibonaccI   Test   "</span></b>
<b><span class="hljs-string">"  FibonaccI   tesT   "</span></b>
<b>&gt; <span class="hljs-number">4</span></b>
? <span class="hljs-number">3</span> <span class="hljs-string">"Flux field inspection and particle affiliation department"</span>
<b><span class="hljs-string">"Flux fIeld inspecTion and particle affiliation department"</span></b>
<b><span class="hljs-string">"Flux fIeld inspection and parTicle affiliation department"</span></b>
<b><span class="hljs-string">"Flux fIeld inspection and particle affiliaTion department"</span></b>
<b><span class="hljs-string">"Flux fIeld inspection and particle affiliation deparTment"</span></b>
<b><span class="hljs-string">"Flux fIeld inspection and particle affiliation departmenT"</span></b>
<b><span class="hljs-string">"Flux field InspecTion and particle affiliation department"</span></b>
<b><span class="hljs-string">"Flux field Inspection and parTicle affiliation department"</span></b>
<b><span class="hljs-string">"Flux field Inspection and particle affiliaTion department"</span></b>
<b><span class="hljs-string">"Flux field Inspection and particle affiliation deparTment"</span></b>
<b><span class="hljs-string">"Flux field Inspection and particle affiliation departmenT"</span></b>
<b><span class="hljs-string">"Flux field inspectIon and parTicle affiliation department"</span></b>
<b><span class="hljs-string">"Flux field inspectIon and particle affiliaTion department"</span></b>
<b><span class="hljs-string">"Flux field inspectIon and particle affiliation deparTment"</span></b>
<b><span class="hljs-string">"Flux field inspectIon and particle affiliation departmenT"</span></b>
<b><span class="hljs-string">"Flux field inspection and partIcle affiliaTion department"</span></b>
<b><span class="hljs-string">"Flux field inspection and partIcle affiliation deparTment"</span></b>
<b><span class="hljs-string">"Flux field inspection and partIcle affiliation departmenT"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affIliaTion department"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affIliation deparTment"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affIliation departmenT"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affilIaTion department"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affilIation deparTment"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affilIation departmenT"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affiliatIon deparTment"</span></b>
<b><span class="hljs-string">"Flux field inspection and particle affiliatIon departmenT"</span></b>
<b><span class="hljs-string">"flux FIeld inspecTion and particle affiliation department"</span></b>
<b><span class="hljs-string">"flux FIeld inspection and parTicle affiliation department"</span></b>
<b><span class="hljs-string">"flux FIeld inspection and particle affiliaTion department"</span></b>
<b><span class="hljs-string">"flux FIeld inspection and particle affiliation deparTment"</span></b>
<b><span class="hljs-string">"flux FIeld inspection and particle affiliation departmenT"</span></b>
<b><span class="hljs-string">"flux Field InspecTion and particle affiliation department"</span></b>
<b><span class="hljs-string">"flux Field Inspection and parTicle affiliation department"</span></b>
<b><span class="hljs-string">"flux Field Inspection and particle affiliaTion department"</span></b>
<b><span class="hljs-string">"flux Field Inspection and particle affiliation deparTment"</span></b>
<b><span class="hljs-string">"flux Field Inspection and particle affiliation departmenT"</span></b>
<b><span class="hljs-string">"flux Field inspectIon and parTicle affiliation department"</span></b>
<b><span class="hljs-string">"flux Field inspectIon and particle affiliaTion department"</span></b>
<b><span class="hljs-string">"flux Field inspectIon and particle affiliation deparTment"</span></b>
<b><span class="hljs-string">"flux Field inspectIon and particle affiliation departmenT"</span></b>
<b><span class="hljs-string">"flux Field inspection and partIcle affiliaTion department"</span></b>
<b><span class="hljs-string">"flux Field inspection and partIcle affiliation deparTment"</span></b>
<b><span class="hljs-string">"flux Field inspection and partIcle affiliation departmenT"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affIliaTion department"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affIliation deparTment"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affIliation departmenT"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affilIaTion department"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affilIation deparTment"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affilIation departmenT"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affiliatIon deparTment"</span></b>
<b><span class="hljs-string">"flux Field inspection and particle affiliatIon departmenT"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfIliaTion department"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfIliation deparTment"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfIliation departmenT"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfilIaTion department"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfilIation deparTment"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfilIation departmenT"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfiliatIon deparTment"</span></b>
<b><span class="hljs-string">"flux field inspection and particle aFfiliatIon departmenT"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFIliaTion department"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFIliation deparTment"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFIliation departmenT"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFilIaTion department"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFilIation deparTment"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFilIation departmenT"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFiliatIon deparTment"</span></b>
<b><span class="hljs-string">"flux field inspection and particle afFiliatIon departmenT"</span></b>
<b>&gt; <span class="hljs-number">66</span></b>
# <span class="hljs-number">4</span> <span class="hljs-string">"figure fits the first filter of floating firmware in the field width transistor to instance"</span>
<b>&gt; limit <span class="hljs-number">1</span>: <span class="hljs-number">238</span></b>
<b>&gt; limit <span class="hljs-number">2</span>: <span class="hljs-number">321</span></b>
<b>&gt; limit <span class="hljs-number">3</span>: <span class="hljs-number">324</span></b>
<b>&gt; limit <span class="hljs-number">4</span>: <span class="hljs-number">324</span></b>
# <span class="hljs-number">1</span> <span class="hljs-string">"Stay fit!"</span>
<b>&gt; limit <span class="hljs-number">1</span>: <span class="hljs-number">0</span></b>
#
<b>Nespravny vstup.</b>
</pre>
<hr>
<pre class="hljs"><b>Zkratka:</b>
Hello
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
 
 <li>Slova ve zpracovávaném textu jsou oddělena jednou nebo více mezerami. Ostatní znaky (písmena, 
     čísla, interpunkci, ...) považujte za součást slov.</li>

 <li>Pořadí vypsaných textů s vyznačením pozic písmen zkratky není určeno, může být libovolné. 
     Testovací prostředí si pořadí před porovnáním upraví. tedy například pro ukázkový běh je platné pořadí:
<pre class="hljs cpp"><span class="hljs-string">"Flux fIeld inspecTion and particle affiliation department"</span>
<span class="hljs-string">"Flux fIeld inspection and parTicle affiliation department"</span>
...
<span class="hljs-string">"flux field inspection and particle afFiliatIon deparTment"</span>
<span class="hljs-string">"flux field inspection and particle afFiliatIon departmenT"</span>
</pre>

nebo 

<pre class="hljs cpp"><span class="hljs-string">"flux field inspection and particle afFiliatIon departmenT"</span>
<span class="hljs-string">"flux field inspection and particle afFiliatIon deparTment"</span>
...
<span class="hljs-string">"Flux fIeld inspection and parTicle affiliation department"</span>
<span class="hljs-string">"Flux fIeld inspecTion and particle affiliation department"</span>
</pre>
nebo libovolné jiné ze zbývajících 544344939077443064003729240247842752644293064388798874532860126869671081148415999999999999998 možností.</li>
 
 <li>Při zpracování vstupu je vhodné načítat celé řádky funkcemi <tt class="hljs">fgets</tt> nebo <tt class="hljs">getline</tt>. 
     Následně lze přečtenou řádku problému rozdělit pomocí funkce <tt class="hljs cpp"><span class="hljs-built_in">sscanf</span></tt>. S výhodou lze 
     použít konverze <tt class="hljs">%n</tt>.</li>
     
 <li>Odevzdaný program je testován více testy se zvyšující se náročností. Nejprve je kontrolovaná 
     správnost řešení, dále se kontroluje správnost práce s polem a dynamická alokace paměti (test 
     paměťovým debuggerem) a nakonec efektivita řešení.</li>
 
 <li>Základní řešení předpokládá naivní algoritmus s exponenciální složitostí (pozor, často vykonávané 
     části programu musí byt rozumně efektivně implementované - exponenciální počet vykonání kódu s velkou 
     režií může program významně zpomalit). Řešení založené na hrubé síle projde povinnými testy a některými 
     nepovinnými testy. Bude hodnoceno maximálně 100 % bodů.</li>
     
 <li>Bonusový test kontroluje efektivitu odevzdaného programu. Jsou zadávané delší zkratky a delší prohledávané 
     texty. V bonusových testech se zadávají pouze problémy typu <tt class="hljs">#</tt>, výpisy všech nalezených možností by 
     byly nesmyslně dlouhé.</li>
 
 <li>Počty nalezených možností mohou být dost vysoké. Pro povinné a nepovinné testy postačuje datový typ <tt class="hljs cpp"><span class="hljs-keyword">int</span></tt>. 
     Snažíte-li se o zvládnutí bonusového testu, je pro reprezentaci je vhodné zvolit datový typ s 
     dostatečným rozsahem (<tt class="hljs cpp"><span class="hljs-keyword">long</span> <span class="hljs-keyword">int</span></tt> nebo <tt class="hljs cpp"><span class="hljs-keyword">long</span> <span class="hljs-keyword">long</span></tt>).</li>
     
 <li>Program, který projde všemi povinnými a nepovinnými testy na 100 %, může být použit pro code review. 
     (Pro code review není potřeba projít bonusovými testy).</li>
 
 <li>Program má pro svůj běh k dispozici relativně hodně paměti (stovky MiB pro zkratky/texty délky stovek znaků).</li>
</ul>


</td>