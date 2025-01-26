@echo off
:: Pelna sciezka do pliku Doxyfile.txt
set DOXYFILE_PATH=D:\Silnik_3D\Silnik_3D\docs\Doxyfile.txt

:: Sprawdz, czy plik Doxyfile.txt istnieje
if not exist "%DOXYFILE_PATH%" (
    echo Plik Doxyfile.txt nie zostal znaleziony w katalogu.
    pause
    exit /b
)

:: Uruchom Doxygen, aby wygenerowac dokumentacje
doxygen "%DOXYFILE_PATH%"

:: Sprawdz, czy proces zakonczyl sie sukcesem
if %errorlevel% equ 0 (
    echo Dokumentacja zostala wygenerowana pomyslnie.
) else (
    echo Wystapil blad podczas generowania dokumentacji.
)

pause
