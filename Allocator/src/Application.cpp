#include <iostream>


#include "Allocator.h"
#include "Ref.h"

struct Entity
{
    ~Entity()
    {
        std::cout << "Entity destroyed!" << std::endl;
    }

    void Foo()
    {
        std::cout << "Foo" << std::endl;
    }
};

struct Student
{
    Student() : Name(""), Mark(0)
    {
    }

    Student(const std::string& name, float mark) : Name(name), Mark(mark)
    {
    }

    ~Student()
    {
        std::cout << "Student Destroyed" << std::endl;
    }

    std::string Name;
    float Mark;
};

int main()
{
    Allocator::Init();

    for (int i = 0; i < 1000000; ++i)
    {
        Allocator::New<Student>();
    }

    return 0;
}
