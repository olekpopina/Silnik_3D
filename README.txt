Chińczyk 3D – README
====================

Opis:
-----
Chińczyk 3D to komputerowa gra planszowa stworzona w języku C++ z wykorzystaniem autorskiego silnika 3D opartego na OpenGL. Gra obsługuje 2–4 graczy, zawiera interaktywne menu, animowaną kostkę, logikę gry Ludo oraz ekran zwycięzcy.

Wymagania systemowe:
---------------------
- Windows 10 lub 11 (x64)
- Visual Studio 2022 Community Edition
- Kompilator MSVC
- Obsługa OpenGL (min. 3.0)
- Zainstalowane pakiety NuGet (poniżej)

Wykorzystane biblioteki (NuGet):
---------------------------------
- AssimpCpp 5.0.1.6
- freeglut.3.2.2.v140 1.0.0
- glew.v140 1.12.0
- sfml_graphics 2.6.0
- sfml_graphics.redist 2.6.0
- sfml_system 2.6.0
- sfml_system.redist 2.6.0
- sfml_window 2.6.0
- sfml_window.redist 2.6.0
- soil 1.16.0

Struktura projektu:
-------------------
Chinczyk3D/
├── Silnik_3D.sln – plik rozwiązania Visual Studio 2022
├── README.txt – ten plik
├── Silnik_3D/ – główny katalog projektu:
│   ├── *.cpp i *.h – pliki źródłowe gry i silnika
│   ├── images/ – wszystkie tekstury, modele pionków, tła
│   ├── docs/ – dokumentacja techniczna Doxygen (html + Doxyfile.txt)
│   ├── packages.config – lista zależności NuGet
│   └── inne pliki projektu
├── packages/ – katalog zainstalowanych bibliotek NuGet
├──.gitignore
└── PGK2.POPINA.VYSHNEVSKYI.YATSENKO.Sprawozdanie.Chinczyk3D.pdf – raport końcowy

Instrukcja uruchomienia:
-------------------------
1. Otwórz plik Silnik_3D.sln w Visual Studio 2022
2. Skonfiguruj tryb kompilacji na Release lub Debug, architekturę na x64
3. Upewnij się, że wszystkie biblioteki NuGet są zainstalowane (menu: Zarządzaj pakietami NuGet)
4. Zbuduj projekt (Kompiluj → Kompiluj rozwiązanie)
5. Uruchom grę (F5 lub Ctrl + F5)

Dokumentacja techniczna:
-------------------------
W folderze docs/ znajduje się wygenerowana dokumentacja Doxygen (plik Doxyfile.txt + html/). Opisuje strukturę klas, funkcje i zależności w silniku graficznym.

Autorzy:
--------
- Oleksandr Popina
- Roman Vyshnevskyi
- Anton Yatsenko

Repozytorium:
-------------
https://github.com/olekpopina/Silnik_3D