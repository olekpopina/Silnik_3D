#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
public:
    virtual void draw() const = 0; // Interfejs dla rysowania obiektu
    virtual ~Drawable() = default; // Wirtualny destruktor
};

#endif // DRAWABLE_H
