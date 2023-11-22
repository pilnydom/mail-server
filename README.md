# Poštovní server

## O projektu

Poštovní server je jednou z individuálních domácích úloh zadaných k vypracování v rámci předmětu, který je zaměřen na procvičení programování a algoritmizace v jazyku C++.

Úkolem je realizovat třídu `CMailServer`, která bude simulovat činnost jednoduchého poštovního serveru.

## Zadání a požadavky

Předpokládáme, že server zprostředkovává zasílání e-mailu uvnitř nějaké organizace. Každý e-mail je reprezentován instancí třídy `CMail`, obsahuje adresu odesílatele, adresu příjemce a tělo zprávy (vše jsou to řetězce). Mail server umí zprávu odeslat a umí zjišťovat obsah odeslané a přijaté pošty (outbox a inbox) pro jednotlivé e-mailové adresy. Seznam odeslané a přijaté pošty je poskytnut pro jednotlivé e-mailové adresy v podobě iterátoru, instance iterátoru nabízí metody, kterými se lze pohybovat v seznamu mailů a lze se dostat k obsahu jednotlivých mailů. Vlastní třída `CMailServer` musí správně zvládat kopírování, její kopie slouží pro archivační a auditní účely.

> [!IMPORTANT]
> Úloha je směřována k procvičení pochopení mělké a hluboké kopie objektu. Z tohoto důvodu jsou v úloze potlačené části standardní C++ knihovny, zejména STL a datový typ C++ `std::string`. K dispozici je pouze rozhraní knihovny C řetězců (`cstring`). Pro implementaci může být vhodné si vytvořit vlastní jednoduchou náhradu `std::string`.

### Požadované rozhraní

#### Třída `CMail`

Požadovaná třída `CMail` má následující rozhraní:

| Metoda/Operátor | Očekávané chování |
| --------------- | ----------------- |
| konstruktor (`from`, `to`, `body`) | Vytvoří instanci e-mailu se složkami `from`/`to`/`body` vyplněnými podle parametrů. Předpokládá se, že e-mailové adresy jsou relativně krátké (desítky až stovky znaků) a že tělo zprávy může být relativně dlouhé (i několik megabyte). |
| `operator==` | Porovná obsah dvou instancí `CMail`, metoda vrací `true`, pokud jsou instance identické (shodují se všechny složky `from`, `to` i obsah e-mailu). |
| `operator<<` | Zobrazí informace o mailu do zadaného streamu. Formát je zřejmý z ukázky. |

#### Třída `CMailServer`

Požadovaná třída `CMailServer` má následující rozhraní:

| Metoda/Operátor | Očekávané chování |
| --------------- | ----------------- |
| implicitní konstruktor | Vytvoří prázdnou instanci. |
| destruktor | Uvolní prostředky alokované instancí. |
| kopírující konstruktor, `operator=` | Vytvoří identické kopie instance podle standardních pravidel. |
| `sendMail(mail)` | Zašle e-mail předaný v parametrech, efektivně jej zařadí do odpovídajících schránek odesílatele a příjemce. E-mail je vždy zařazen na konec existujícího seznamu. Příjemce ani odesílatele není potřeba zakládat, schránka se automaticky vytvoří po zpracování prvního e-mailu, který obsahuje danou e-mailovou adresu. |
| `outbox(email)` | Zpřístupní poštu odeslanou ze zadané adresy. Návratovou hodnotou je instance `CMailIterator`, která umožňuje procházet emaily odeslané z adresy `email`. Pokud je zadaná neznámá e-mailová adresa, je výsledkem iterátor pro prázdný seznam e-mailů. Pokud je zadaná neznámá e-mailová adresa, je výsledkem iterátor pro prázdný seznam e-mailů. Vrácený iterátor musí zachycovat stav mailové schránky v okamžiku, kdy byl vytvořen. Tedy pokud během používání iterátoru dojde ke změně obsahu procházené schránky, tato změna se do hodnot vracených iterátorem nijak nepromítne. Toto chování je demonstrované v ukázkovém běhu např. pro iterátor `i5`. |
| `inbox(email)` | Zpřístupní poštu přijatou na zadanou adresu. Jinak metoda pracuje stejně jako metoda `outbox`. |

> [!IMPORTANT]
> Emailové adresy v úloze mohou být libovolné řetězce, při jejich porovnávání rozlišujeme malá a velká písmena (case sensitive) - v tomto se úloha liší od reálného světa, kde e-mailové adresy mají předepsaný formální tvar a kde se malá a velká písmena zpravidla nerozlišují.

#### Třída `CMailIterator`

Požadovaná třída `CMailIterator` má následující rozhraní:

| Metoda/Operátor | Očekávané chování |
| --------------- | ----------------- |
| `operator bool` | Zjistí, zda iterátor odkazuje na platný e-mail (vrací `true`), nebo zda dosáhl za poslední e-mail v seznamu (tedy e-mail už nelze číst, vrátí `false`). |
| `operator!` | Funguje stejně jako předešlý operátor, pouze vrací opačnou návratovou hodnotu. |
| `operator*` | Unární operátor \* zpřístupní e-mail na aktuální pozici. Návratovou hodnotou je instance `CMail` (případně konstantní reference na `CMail`). Nemusíte řešit situaci, že by se zpřístupnil e-mail za koncem seznamu - testovací prostředí vždy nejprve kontroluje platnost iterátoru a teprve pak případně zpřístupní odkazovaný e-mail. |
| `operator++` | Prefixový operátor ++ zajistí přesun iterátoru na další e-mail v seznamu. E-maily jsou iterátorem procházené v pořadí, ve kterém byly odeslané/přijaté. Opakovaným voláním tohoto iterátoru se lze přesunout od prvního e-mailu přijatého/odeslaného zadanou e-mailovou adresou až k poslednímu (pak musí operátor přetypování na bool vracet `false`). |
| kopírující konstruktor, `operator=`, destruktor | Podle způsobu implementace možná nebude postačovat automaticky generovaná varianta. Testovací prostředí iterátory nikde explicitně nekopíruje, ale ke kopírování dochází v okamžiku předávání návratové hodnoty metodami `inbox` a `outbox`. |

## Instalace

1. Stáhněte tento projekt jako ZIP a extrahujte ho
2. Otevřete složku s tímto projektem v konzoli
3. Proveďte kompilaci a následné spuštění pomocí příkazu `make run`

## Příklad použití

```cpp
#include <sstream>

#include "CMailServer.h"

int main()
{
    CMailServer mailServer;

    // Send some emails
    mailServer.sendMail(CMail("alice@example.com", "bob@example.com", "Hello Bob!"));
    mailServer.sendMail(CMail("bob@example.com", "alice@example.com", "Hi Alice!"));
    mailServer.sendMail(CMail("charlie@example.com", "bob@example.com", "Hey Bob, how's it going?"));

    // Print out the outbox for Alice
    CMailIterator aliceOutbox = mailServer.outbox("alice@example.com");
    while (aliceOutbox)
    {
        std::cout << *aliceOutbox << std::endl;
        ++aliceOutbox;
    }

    // Print out the inbox for Bob
    CMailIterator bobInbox = mailServer.inbox("bob@example.com");
    while (bobInbox)
    {
        std::cout << *bobInbox << std::endl;
        ++bobInbox;
    }

    return EXIT_SUCCESS;
}
```

```console
From: alice@example.com, To: bob@example.com, Body: Hello Bob!
From: alice@example.com, To: bob@example.com, Body: Hello Bob!
From: charlie@example.com, To: bob@example.com, Body: Hey Bob, how's it going?
```