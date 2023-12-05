#include <iostream>
#include <memory>
// Abstract class for the shape

class Shape
{
public:
    virtual void draw() = 0;
    virtual float getArea()=0;
    virtual ~Shape() = default; 
};

// Concrete class for the shape
class Circle : public Shape
{       
    float radius;
public:
    Circle(float radius):radius(radius)
    {
    }
    virtual void draw() override
    {
        std::cout << "This is circle" << std::endl;
    }
    float getArea() override
    {
        return 3.14*radius*radius;
    }
};

// Concrete class for the shape
class Rectangle : public Shape
{
    float length;
    float breadth;
public:
    Rectangle(float length, float breadth):length(length), breadth(breadth)
    {
    }
    
    virtual void draw() override
    {
        std::cout << "This is rectangle" << std::endl;
    }
    float getArea() override
    {
        return length*breadth;
    }
};

// Factory class for the shape
class ShapeFactory
{
public:
    std::unique_ptr<Shape> getShape(std::string shapeType)
    {
        if(shapeType == "Circle")
        {
            return std::make_unique<Circle>(10);
        }
        else if(shapeType == "Rectangle")
        {
            return std::make_unique<Rectangle>(10, 20);
        }
        else
        {
            throw std::invalid_argument("Unsupported shape type");
        }
    }
};

int main()
{
    ShapeFactory shapeFactory;
    auto shape = shapeFactory.getShape("Circle");
    shape->draw();
    std::cout << "Area of circle is " << shape->getArea() << std::endl;
    shape = shapeFactory.getShape("Rectangle");
    shape->draw();
    std::cout << "Area of rectangle is " << shape->getArea() << std::endl;
    return 0;
}
