#ifndef DRAWABLE_H
#define DRAWABLE_H

/**
 * @brief Interfejs dla obiekt�w, kt�re mog� by� rysowane.
 *
 * Klasa ta definiuje podstawowy interfejs dla wszystkich obiekt�w, kt�re wymagaj�
 * funkcji rysuj�cej. Ka�da klasa, kt�ra chce by� rysowana, musi implementowa�
 * metod� `draw()`.
 */
class Drawable {
public:
    /**
     * @brief Funkcja rysuj�ca obiekt.
     *
     * Wirtualna funkcja czysto wirtualna, kt�ra musi zosta� zaimplementowana
     * w ka�dej klasie dziedzicz�cej. Odpowiada za rysowanie obiektu na ekranie.
     */
    virtual void draw() const = 0;

    /**
     * @brief Wirtualny destruktor.
     *
     * Wirtualny destruktor, zapewniaj�cy prawid�owe usuwanie obiekt�w w hierarchii
     * dziedziczenia, gdy s� usuwane przez wska�nik do klasy bazowej.
     */
    virtual ~Drawable() = default; // Wirtualny destruktor zapewniaj�cy poprawne usuwanie obiekt�w.
};

#endif // DRAWABLE_H
