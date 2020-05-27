#ifndef CTKEXCEPTIONS_H
#define CTKEXCEPTIONS_H

#include <exception>

namespace ctk {

class division_per_zero : public std::exception
{
    virtual const char* what() const noexcept
    {
        return "Division by zero\n";
    }
};

class value_out_of_range : public std::exception
{
    virtual const char* what() const noexcept
    {
        return "Division by zero\n";
    }
};

}

#endif // CTKEXCEPTIONS_H
