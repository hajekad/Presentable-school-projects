<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat třídu <tt class="hljs">CVATRegister</tt>, která bude implementovat
databázi kontrolních hlášení DPH.</p>

<p>Pro plánované důslednější potírání daňových úniků je zaveden systém kontrolních 
hlášení. V databázi jsou zavedené jednotlivé firmy, a do databáze jsou zaznamenávané 
jednotlivé vydané faktury, které daná firma vydala. Firmy lze do databáze zadávat a 
lze je rušit. Firma je identifikována svým jménem, adresou a daňovým identifikátorem 
(id). Daňový identifikátor je unikátní přes celou databázi. Jména a adresy se mohou 
opakovat, ale dvojice (jméno, adresa) je opět v databázi unikátní. Tedy v databázi 
může být mnoho firem <tt class="hljs">ACME</tt>, mnoho firem může mít adresu <tt class="hljs">Praha</tt>,
ale firma <tt class="hljs">ACME</tt> bydlící sídlící ve městě <tt class="hljs">Praha</tt> může být v databázi 
pouze jedna. Při porovnávání daňových identifikátorů <b>rozlišujeme</b> malá a velká písmena, 
u jmen a adres naopak <b>nerozlišujeme</b> malá a velká písmena.</p>  


<p>Veřejné rozhraní je uvedeno níže. Obsahuje následující:</p>
<ul>
 <li>Konstruktor bez parametrů. Tento konstruktor inicializuje instanci třídy 
  tak, že vzniklá instance je zatím prázdná (neobsahuje žádné záznamy).</li>
 <li>Destruktor. Uvolňuje prostředky, které instance alokovala.</li>
 <li>Metoda <tt class="hljs">newCompany(name, addr, id)</tt> přidá do existující
  databáze další záznam. Parametry <tt class="hljs">name</tt> a <tt class="hljs">addr</tt> reprezentují 
  jméno a adresu, parametr <tt class="hljs">id</tt> udává daňový identifikátor.  Metoda 
  vrací hodnotu <tt class="hljs cpp"><span class="hljs-literal">true</span></tt>, pokud byl  záznam přidán, nebo hodnotu <tt class="hljs cpp"><span class="hljs-literal">false</span></tt>, 
  pokud přidán nebyl (protože již  v databázi existoval záznam se stejným 
  jménem a adresou,  nebo záznam se stejným id).</li>
 <li>Metody <tt class="hljs">cancelCompany (name, addr) / cancelCompany (id)</tt> odstraní záznam 
  z databáze. Parametrem je jednoznačná identifikace pomocí jména a adresy (první varianta) 
  nebo pomocí daňového identifikátoru (druhá varianta). Pokud byl záznam skutečně odstraněn, 
  vrátí metoda hodnotu <tt class="hljs cpp"><span class="hljs-literal">true</span></tt>. Pokud záznam neodstraní (protože neexistovala firma
  s touto identifikací), vrátí metoda hodnotu <tt class="hljs cpp"><span class="hljs-literal">false</span></tt>.</li>
  
 <li>Metody <tt class="hljs">invoice (name, addr, amount) / invoice (id, amount)</tt> zaznamenají 
  příjem ve výši <tt class="hljs">amount</tt>. Varianty jsou dvě - firma je buď identifikována svým jménem a adresou, 
  nebo daňovým identifikátorem. Pokud metoda uspěje, vrací <tt class="hljs cpp"><span class="hljs-literal">true</span></tt>, pro neúspěch vrací 
  <tt class="hljs cpp"><span class="hljs-literal">false</span></tt> (neexistující firma).</li>

 <li>Metoda <tt class="hljs">audit ( name, addr, sum ) / audit ( id, sum )</tt> vyhledá součet příjmů pro 
  firmu se zadaným jménem a adresou nebo firmu zadanou daňovým identifikátorem. Nalezený součet 
  uloží do výstupního parametru <tt class="hljs">sum</tt>. Metoda vrátí <tt class="hljs cpp"><span class="hljs-literal">true</span></tt> pro úspěch, 
  <tt class="hljs cpp"><span class="hljs-literal">false</span></tt> pro selhání (neexistující firma).</li>
  
 <li>Metoda <tt class="hljs">medianInvoice ()</tt> vyhledá medián hodnoty faktury. Do vypočteného mediánu 
   se započtou všechny úspěšně zpracované faktury zadané voláním <tt class="hljs">invoice</tt>. Tedy 
   <b>nezapočítávají</b> se faktury, které nešlo přiřadit (volání <tt class="hljs">invoice</tt> selhalo),
   ale započítávají se všechny dosud registrované faktury, tedy při výmazu firmy se <b>neodstraňují</b> 
   její faktury z výpočtu mediánu. Pokud je v systému zadaný sudý počet faktur, vezme se 
   vyšší ze dvou prostředních hodnot. Pokud systém zatím nezpracoval žádnou fakturu, bude 
   vrácena hodnota 0.</li>
   
 <li>Metody <tt class="hljs">firstCompany ( name, addr ) / nextCompany ( name, addr )</tt> slouží k procházení existujícího seznamu 
   firem v naší databázi. Firmy jsou procházené v abecedním pořadí podle jejich jména. Pokud mají 
   dvě firmy stejná jména, rozhoduje o pořadí jejich adresa. Metoda <tt class="hljs">firstCompany</tt> nalezne 
   první firmu. Pokud je seznam firem prázdný, vrátí metoda hodnotu <tt class="hljs cpp"><span class="hljs-literal">false</span></tt>. V opačném případě 
   vrátí metoda hodnotu <tt class="hljs cpp"><span class="hljs-literal">true</span></tt> a vyplní výstupní parametry <tt class="hljs">name</tt> a <tt class="hljs">addr</tt>. Metoda 
   <tt class="hljs">nextCompany</tt> funguje obdobně, nalezne další firmu, která v seznamu následuje za firmou 
   určenou parametry. Pokud za <tt class="hljs">name</tt> a <tt class="hljs">addr</tt> již v seznamu není další firma, metoda 
   vrací hodnotu <tt class="hljs cpp"><span class="hljs-literal">false</span></tt>. V opačném případě metoda vrátí <tt class="hljs cpp"><span class="hljs-literal">true</span></tt> a přepíše parametry <tt class="hljs">name</tt> 
   a <tt class="hljs">addr</tt> jménem a adresou následující firmy.</li>
</ul>

<p>Odevzdávejte soubor, který obsahuje implementovanou třídu
<tt class="hljs">CVATRegister</tt>. Třída musí splňovat veřejné rozhraní podle ukázky - pokud Vámi 
odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy 
si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. 
Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice 
metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline 
nebo odděleně. Odevzdávaný soubor nesmí kromě implementace třídy
<tt class="hljs">CVATRegister</tt> obsahovat nic jiného, zejména ne vkládání hlavičkových souborů a 
funkci <tt class="hljs">main</tt> (funkce <tt class="hljs">main</tt> a vkládání hlavičkových souborů může zůstat, 
ale pouze obalené direktivami podmíněného překladu). Za základ implementace použijte 
přiložený zdrojový soubor.</p>

<p>Třída je testovaná v omezeném prostředí, kde je limitovaná dostupná paměť (dostačuje 
k uložení seznamu) a je omezena dobou běhu. Implementovaná třída se nemusí zabývat 
kopírujícím konstruktorem ani přetěžováním operátoru =. V této úloze ProgTest neprovádí 
testy této funkčnosti.</p>

<p>Implementace třídy musí být efektivní z hlediska nároků na čas i nároků na paměť. 
Jednoduché lineární řešení nestačí (pro testovací data vyžaduje čas přes 5 minut). 
Předpokládejte, že vytvoření a likvidace firmy jsou řádově méně časté než ostatní 
operace, tedy zde je lineární složitost akceptovatelná. Častá jsou volání 
<tt class="hljs">invoice</tt> a <tt class="hljs">audit</tt>, jejich časová složitost musí být lepší než lineární 
(např. logaritmická nebo amortizovaná konstantní). Dále, v povinných testech se metoda 
<tt class="hljs">medianInvoice</tt> volá málo často, tedy nemusí být příliš efektivní (pro úspěch 
v povinných testech stačí složitost lineární nebo <tt class="hljs cpp">n <span class="hljs-built_in">log</span> n</tt>, pro bonusový test 
je potřeba složitost lepší než lineární).</p>

<p>Pro uložení hodnot alokujte pole dynamicky případně použijte STL. Pozor 
Pokud budete pole alokovat ve vlastní režii, zvolte počáteční velikost malou 
(např. tisíc prvků) a velikost zvětšujte/zmenšujte podle potřeby. Při zaplnění 
pole není vhodné alokovat nové pole větší pouze o jednu hodnotu, takový postup 
má obrovskou režii na kopírování obsahu. Je rozumné pole rozšiřovat s krokem 
řádově tisíců prvků, nebo geometrickou řadou s kvocientem ~1.5 až 2.</p>

<p>Pokud budete používat STL, nemusíte se starat o problémy s alokací. Pozor -
k dispozici máte pouze část STL (viz hlavičkové soubory v přiložené ukázce). Tedy 
například kontejnery <tt class="hljs cpp"><span class="hljs-built_in">map</span></tt> / <tt class="hljs cpp"><span class="hljs-built_in">unordered_map</span></tt> / <tt class="hljs cpp"><span class="hljs-built_in">set</span></tt> / 
<tt class="hljs cpp"><span class="hljs-built_in">unordered_set</span></tt> / ... nejsou k dispozici.</p>

<p>V přiloženém zdrojovém kódu jsou obsažené základní testy. Tyto testy zdaleka
nepokrývají všechny situace, pro odladění třídy je budete muset rozšířit. Upozorňujeme, 
že testy obsažené v odevzdaných zdrojových kódech považujeme za nedílnou součást 
Vašeho řešení. Pokud v odevzdaném řešení necháte cizí testy, může být práce 
vyhodnocena jako opsaná.</p>

<b>Poznámky:</b>
<ul>
  <li>Pokud Vaše řešení projde všemi povinnými a nepovinnými testy na 100%, lze 
   jej použít pro code review (tedy pro code review není nutné zvládnout poslední 
   bonusový test). Protože se ale jedná o úlohu snazší a kratší, počítejte v případném 
   code review s přísnějším hodnocením.</li>
</ul>
</td>