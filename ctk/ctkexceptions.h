#ifndef CTKEXCEPTIONS_H
#define CTKEXCEPTIONS_H

#include <exception>

namespace ctk {

class invalid_type: public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "Invalid type";
    }
};


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
        return "Value out of range\n";
    }
};

class incompatible_parameters : public std::exception
{
    virtual const char* what() const noexcept
    {
        return "Parameters incompatible\n";
    }
};

}

#endif // CTKEXCEPTIONS_H
