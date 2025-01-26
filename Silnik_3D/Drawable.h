#ifndef DRAWABLE_H
#define DRAWABLE_H

/**
 * @brief Interfejs dla obiektów, które mog¹ byæ rysowane.
 *
 * Klasa ta definiuje podstawowy interfejs dla wszystkich obiektów, które wymagaj¹
 * funkcji rysuj¹cej. Ka¿da klasa, która chce byæ rysowana, musi implementowaæ
 * metodê `draw()`.
 */
class Drawable {
public:
    /**
     * @brief Funkcja rysuj¹ca obiekt.
     *
     * Wirtualna funkcja czysto wirtualna, która musi zostaæ zaimplementowana
     * w ka¿dej klasie dziedzicz¹cej. Odpowiada za rysowanie obiektu na ekranie.
     */
    virtual void draw() const = 0;

    /**
     * @brief Wirtualny destruktor.
     *
     * Wirtualny destruktor, zapewniaj¹cy prawid³owe usuwanie obiektów w hierarchii
     * dziedziczenia, gdy s¹ usuwane przez wskaŸnik do klasy bazowej.
     */
    virtual ~Drawable() = default; // Wirtualny destruktor zapewniaj¹cy poprawne usuwanie obiektów.
};

#endif // DRAWABLE_H
