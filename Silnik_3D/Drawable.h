#ifndef DRAWABLE_H
#define DRAWABLE_H

/**
 * @brief Interfejs dla obiektów, które mogą być rysowane.
 *
 * Klasa ta definiuje podstawowy interfejs dla wszystkich obiektów, które wymagają
 * funkcji rysującej. Każda klasa, która chce być rysowana, musi implementować
 * metodę `draw()`.
 */
class Drawable {
public:
    /**
     * @brief Funkcja rysująca obiekt.
     *
     * Wirtualna funkcja czysto wirtualna, która musi zostać zaimplementowana
     * w każdej klasie dziedziczącej. Odpowiada za rysowanie obiektu na ekranie.
     */
    virtual void draw() const = 0;

    /**
     * @brief Wirtualny destruktor.
     *
     * Wirtualny destruktor, zapewniający prawidłowe usuwanie obiektów w hierarchii
     * dziedziczenia, gdy są usuwane przez wskaźnik do klasy bazowej.
     */
    virtual ~Drawable() = default; // Wirtualny destruktor zapewniający poprawne usuwanie obiektów.
};

#endif // DRAWABLE_H
