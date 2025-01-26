#ifndef SHADING_MODE_H
#define SHADING_MODE_H

/**
 * @enum ShadingMode
 * @brief Typ wyliczeniowy reprezentujący dostępne tryby cieniowania.
 *
 * `ShadingMode` jest wyliczeniem używanym do przechowywania i reprezentowania trybów cieniowania,
 * które można zastosować w grafice 3D.
 */
enum class ShadingMode {
    /** Tryb cieniowania płaskiego */
    FLAT, /**< W tym trybie cała ściana obiektu jest oświetlana jednolicie, bez uwzględniania jej kształtu. */

    /** Tryb cieniowania gładkiego */
    SMOOTH /**< W tym trybie obiekt jest oświetlany na podstawie jego powierzchni, co daje efekt gładkiego przejścia między ścianami. */
};

#endif // SHADING_MODE_H
