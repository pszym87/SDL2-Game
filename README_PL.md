## Wprowadzenie

PacMario jest grą 2D inspirowaną kultowymi grami retro: Pacman i Super Mario. PacMario z pierwszej z nich czerpie ogólną logikę gry, zaś z drugiej szatę graficzną. Gra została napisana w **języku C** z użyciem biblioteki graficznej **SDL2.** Do generowania ruchów przeciwnika użyto algorytmu wyszukiwania najkrótszej drogi w grafie. 

![mario](https://user-images.githubusercontent.com/106841261/181225128-b5755c44-77e2-403f-ad82-f4cd91a61136.gif)



## Struktura

Kod został stworzony tak, aby oddzielić warstwę graficzną od logiki gry. Dzięki czemu w łatwy sposób można ją przenieść na inny silnik graficzny lub dokonywać zmian w logice nie wpływając na wygląd gry. 

Moduły:

1. moduł graficzny (gfx.c)
2. moduł logiki gry (logic.c, adj.c)
3. sterowanie - moduł pośredniczący między modułem graficznym i logiką gry (main.c i ctrl.c)

## Generowanie ruchów komputera

Komputer posiada w grze 3 graczy. 1 gracz porusza się wyszukując **najkrótszą drogę** pomiędzy swoją pozycją a pozycją gracza (robi to na grafie używając **algorytmu Dijkstry**). Aby to umożliwić wykonano kilka przekształceń, które opisano poniżej. Pozostała 2 graczy porusza się w sposób losowy. Jedynie rozpoznając czy ruch jest możliwy do wykonania na planszy (algorytm sprawdza czy pole jest drogą czy ścianą). 

### Przekształcenia mapy gry

Mapa gry jest zakodowana jako **macierz dwuwymiarowa**. Pierwszym przekształceniem jest zamiana mapy gry na **graf nieskierowany**. Każda krawędź grafu ma przypisany **jednakowy koszt**. W pamięci komputera graf zapisany jest jako macierz sąsiedztwa. Po wygenerowaniu ruchu komputera jest on przekształcany na zapis tablicowy.  

**Przykład dla mapy 4x4**

Kolejno mapa przedstawiona wizualnie >> macierz 4x4 >> graf nieskierowany


![przeksztalcenia](https://user-images.githubusercontent.com/106841261/181225276-f597e357-9eca-4d4b-bff2-bbd0e0c18e1b.png)


### Implementacja algorytmu Dijkstry

Do wyszukania optymalnego ruchu komputera użyto jednego z algorytmów zachłannych do wyszukiwania najkrótszej drogi pomiędzy węzłem wejściowym, a dowolnym węzłem grafu. W obecnej implementacji jest to algorytm Dijkstry. 

Przy wyszukiwaniu najkrótszej drogi między węzłami grafu do tablicy pomocniczej odkładany jest dla każdego węzła jego węzeł poprzedzający na najkrótszej ścieżce grafu. Komputer czerpie z tej tablicy swój najbliższy ruch.

## Konfiguracja i kompilacja

Gra korzysta z biblioteki graficznej SDL2.

Strona projektu: [https://www.libsdl.org/](https://www.libsdl.org/)

### Źródła bibliotek

Do prawidłowej programu niezbędne są biblioteki: 

SDL2 ([https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php))

SDL2 Image ([https://github.com/libsdl-org/SDL_image](https://github.com/libsdl-org/SDL_image))

SDL2 TTF ([https://github.com/libsdl-org/SDL_ttf](https://github.com/libsdl-org/SDL_ttf))

### Kompilacja

Przy kompilacji programu trzeba podlinkować odpowiednie biblioteki SDL2, SDL2 Image i SDL2 TTF. W zależności od systemu w deklaracjach #include może być konieczna zmiana ścieżki na SDL/SDL.h i SDL/SDL_image.h
