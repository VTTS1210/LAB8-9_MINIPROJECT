#include "Booth.h"


// ============================================================
// Booth
// ============================================================

const double Booth::RENT_PER_SQM = 560000;


Booth::Booth(
    const string& id,
    double area
)
{
    _id = id;
    _area = area;
}


Booth::~Booth()
{
}


string Booth::getId() const
{
    return _id;
}


double Booth::getArea() const
{
    return _area;
}


double Booth::rentPrice() const
{
    return _area * RENT_PER_SQM;
}


double Booth::totalRent() const
{
    return rentPrice() + getOtherFee();
}


// ============================================================
// Food
// ============================================================

Food::Food(
    const string& id,
    double area,
    double coldStorage
)
    : Booth(id, area)
{
    _coldStorage = coldStorage;
}


string Food::getType() const
{
    return "Thuc pham";
}


double Food::getOtherFee() const
{
    return _coldStorage;
}


// ============================================================
// Clothes
// ============================================================

Clothes::Clothes(
    const string& id,
    double area
)
    : Booth(id, area)
{
}


string Clothes::getType() const
{
    return "Quan ao";
}


double Clothes::getOtherFee() const
{
    return 0;
}


// ============================================================
// Jewelry
// ============================================================

Jewelry::Jewelry(
    const string& id,
    double area,
    double securityFee
)
    : Booth(id, area)
{
    _securityFee = securityFee;
}


string Jewelry::getType() const
{
    return "Da qui";
}


double Jewelry::getOtherFee() const
{
    return _securityFee;
}


// ============================================================
// Factory Pattern
// ============================================================

unique_ptr<Booth> BoothFactory::create(
    const string& type,
    const string& id,
    double area,
    double extraFee
)
{
    if (type == "Food")
    {
        return make_unique<Food>(
            id,
            area,
            extraFee
        );
    }

    if (type == "Clothes")
    {
        return make_unique<Clothes>(
            id,
            area
        );
    }

    if (type == "Jewelry")
    {
        return make_unique<Jewelry>(
            id,
            area,
            extraFee
        );
    }

    // If type is invalid
    return nullptr;
}