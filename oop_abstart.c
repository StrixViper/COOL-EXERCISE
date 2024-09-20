#include <stdio.h>
#include <math.h>

// Abstract class (Shape)
typedef struct {
    // Function pointers to simulate abstract methods
    double (*area)(void* self);
    double (*perimeter)(void* self);
} Shape;

// Derived class (Circle)
typedef struct {
    Shape base;  // Inherit from Shape
    double radius;
} Circle;

// Derived class (Rectangle)
typedef struct {
    Shape base;  // Inherit from Shape
    double width, height;
} Rectangle;

// Implementation of Circle's area
double circle_area(void* self) {
    Circle* circle = (Circle*)self;
    return M_PI * circle->radius * circle->radius;
}

// Implementation of Circle's perimeter
double circle_perimeter(void* self) {
    Circle* circle = (Circle*)self;
    return 2 * M_PI * circle->radius;
}

// Implementation of Rectangle's area
double rectangle_area(void* self) {
    Rectangle* rect = (Rectangle*)self;
    return rect->width * rect->height;
}

// Implementation of Rectangle's perimeter
double rectangle_perimeter(void* self) {
    Rectangle* rect = (Rectangle*)self;
    return 2 * (rect->width + rect->height);
}

// Function to initialize a Circle object
void init_circle(Circle* circle, double radius) {
    circle->radius = radius;
    circle->base.area = circle_area;
    circle->base.perimeter = circle_perimeter;
}

// Function to initialize a Rectangle object
void init_rectangle(Rectangle* rect, double width, double height) {
    rect->width = width;
    rect->height = height;
    rect->base.area = rectangle_area;
    rect->base.perimeter = rectangle_perimeter;
}

// Helper function to display shape information
void display_shape_info(Shape* shape, void* object) {
    printf("Area: %f\n", shape->area(object));
    printf("Perimeter: %f\n", shape->perimeter(object));
}

int main() {
    Circle circle;
    Rectangle rectangle;

    init_circle(&circle, 5.0);
    init_rectangle(&rectangle, 4.0, 6.0);

    printf("Circle:\n");
    display_shape_info((Shape*)&circle, &circle);

    printf("\nRectangle:\n");
    display_shape_info((Shape*)&rectangle, &rectangle);

    return 0;
}
